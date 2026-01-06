#include <bits/stdc++.h>

#define SC static_cast

inline void redirectIo() {
#ifndef ONLINE_JUDGE
	char filename[] = __FILE__;
	size_t len = sizeof(filename) / sizeof(filename[0]) - 1;
	filename[len - 3] = 'i';
	filename[len - 2] = 'n';
	filename[len - 1] = '\0';
	std::freopen(filename, "r", stdin);
	filename[len - 3] = 'o';
	filename[len - 2] = 'u';
	filename[len - 1] = 't';
	std::freopen(filename, "w", stdout);
#endif
}

template <typename T, typename Cmp = std::less<T>>
inline T &minEq(T &lhs, const T &rhs, Cmp cmp = Cmp()) {
	return (cmp(rhs, lhs) ? (lhs = rhs) : lhs);
}

template <typename W>
struct EdgeImpl {
	size_t u, v;
	W w;
};
template <>
struct EdgeImpl<void> {
	size_t u, v;
};

template <typename Weight = int64_t, bool is_directed = true>
class Graph {
public:
	// When Weight is void, Edge does not has member w
	using Edge = EdgeImpl<Weight>;

	Graph(size_t n = 0) : m_adj(n) {}
	Graph(size_t n, const std::vector<Edge> &edges)
		: m_adj(n), m_edges(edges) { m_insertEdgesToAdj(); }

	void assign(size_t n) {
		m_edges.clear();
		m_adj.resize(n);
		for (auto &lst : m_adj) lst.clear();
	}
	void assign(size_t n, const std::vector<Edge> &edges) {
		m_edges = edges;
		m_adj.resize(n);
		for (auto &lst : m_adj) lst.clear();
		m_insertEdgesToAdj();
	}

	template <typename W = Weight>
	typename std::enable_if<std::is_void<W>::value, void>::type
	insertEdge(size_t u, size_t v) {
		m_edges.push_back(Edge{u, v});
		m_insertToAdj(m_edges.size() - 1);
	}
	template <typename W = Weight,
			  typename = typename std::enable_if<std::is_same<W, Weight>::value>::type>
	typename std::enable_if<!std::is_void<W>::value, void>::type
	insertEdge(size_t u, size_t v, const W &w) {
		m_edges.push_back(Edge{u, v, w});
		m_insertToAdj(m_edges.size() - 1);
	}

	void reserve(size_t n, size_t m) {
		m_edges.reserve(m);
		m_adj.reserve(n);
	}

	void clear() {
		m_edges.clear();
		m_adj.clear();
	}

	std::pair<size_t, size_t> size() const {
		return std::make_pair(m_adj.size(), m_edges.size());
	}

	const std::vector<Edge> &edges() const { return m_edges; }
	const std::vector<std::vector<size_t>> &adj() const { return m_adj; }

	/* Algorithms */
	std::vector<std::vector<size_t>> tarjanSccs() const;
	bool isUnilaterallyConnected() const;
	/**
	 * @return {{cut_verts, vbccs}, {bridges, ebccs}}
	 */
	inline std::pair<std::pair<std::vector<std::vector<size_t>>,
							   std::vector<std::vector<size_t>>>,
					 std::pair<std::vector<std::vector<size_t>>,
							   std::vector<std::vector<size_t>>>>
	tarjanCutAndBccs() const;

	std::vector<size_t> toposort() const;

	std::vector<std::vector<size_t>> kruskal() const;
	std::vector<size_t> prim(size_t rt = 0) const;

	std::vector<Weight> dijkstra(size_t src) const;
	std::vector<Weight> bellmanFord(size_t src) const;
	std::vector<Weight> spfa(size_t src) const;

	std::pair<Weight, std::vector<bool>>
	dinic(size_t src, size_t dst,
		  typename std::conditional<std::is_arithmetic<Weight>::value,
									Weight, unsigned>::type
			  lim = std::numeric_limits<
				  typename std::conditional<
					  std::is_arithmetic<Weight>::value,
					  Weight, unsigned>::type>::max()) const;

protected:
	std::vector<Edge> m_edges;
	std::vector<std::vector<size_t>> m_adj;

	void m_insertToAdj(size_t idx) {
		size_t sz_requirement = std::max(m_edges[idx].u, m_edges[idx].v) + 1;
		if (sz_requirement > m_adj.size()) m_adj.resize(sz_requirement);
		m_adj[m_edges[idx].u].emplace_back(idx);
		if (m_edges[idx].u != m_edges[idx].v) {
			m_adj[m_edges[idx].v].emplace_back(idx);
		}
	}
	void m_insertEdgesToAdj() {
		for (size_t i = 0; i != m_edges.size(); ++i) {
			m_insertToAdj(i);
		}
	}

private:
};

template <typename Weight, bool is_directed>
std::vector<std::vector<size_t>>
Graph<Weight, is_directed>::tarjanSccs() const {
	static_assert(is_directed,
				  "Tarjan's algorithm for strongly connected components "
				  "is only applicable to directed graphs.");
	std::vector<size_t> stk;
	stk.reserve(m_adj.size());
	std::vector<bool> in_stk(m_adj.size());
	std::vector<size_t> dfn(m_adj.size(), size_t(-1)), low(m_adj.size());
	std::vector<std::vector<size_t>> sccs;
	size_t tm = 0;
	std::function<void(size_t)> dfs = [&](size_t cur) -> void {
		stk.emplace_back(cur);
		in_stk[cur] = true;
		low[cur] = (dfn[cur] = (tm++));
		for (auto i : m_adj[cur]) {
			auto &edge = m_edges[i];
			if (edge.u != cur) { // edges pointing to cur
				continue;
			}
			if (dfn[edge.v] == size_t(-1)) {
				dfs(edge.v);
				minEq(low[cur], low[edge.v]);
			} else if (in_stk[edge.v]) {
				minEq(low[cur], dfn[edge.v]);
			}
		}
		if (dfn[cur] == low[cur]) {
			sccs.emplace_back();
			size_t vert;
			do {
				sccs.back().emplace_back(vert = stk.back());
				stk.pop_back();
				in_stk[vert] = false;
			} while (vert != cur);
		}
	};
	for (size_t i = 0; i != m_adj.size(); ++i) {
		if (dfn[i] == size_t(-1)) dfs(i);
	}
	return sccs;
}

template <typename Weight, bool is_directed>
inline bool Graph<Weight, is_directed>::isUnilaterallyConnected() const {
	static_assert(is_directed,
				  "Unilateral connectivity is only applicable to directed graphs.");
	auto sccs = tarjanSccs();
	if (sccs.size() <= 1) return true;
	std::vector<size_t> vert_to_scc(m_adj.size());
	for (size_t i = 0; i != sccs.size(); ++i) {
		for (auto v : sccs[i]) vert_to_scc[v] = i;
	}
	for (size_t i = sccs.size() - 1; i; --i) {
		bool is_conn = false;
		for (auto frm : sccs[i]) {
			for (auto edge_idx : m_adj[frm]) {
				const auto &edge = m_edges[edge_idx];
				if (edge.u != frm) continue;
				if (vert_to_scc[edge.v] == i - 1) {
					is_conn = true;
					break;
				}
			}
			if (is_conn) break;
		}
		if (!is_conn) return false;
	}
	return true;
}

Graph<void, true> graph;

inline void preprocess() {
	size_t n;
	std::cin >> n;
	graph.assign(n);
	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < n; ++j) {
			size_t rep;
			std::cin >> rep;
			while (rep--) {
				graph.insertEdge(i, j);
			}
		}
	}
}

inline void solve() {
	auto sccs = graph.tarjanSccs();
	std::cout << ((sccs.size() == 1)
					  ? 'A'
					  : (graph.isUnilaterallyConnected()
							 ? 'B'
							 : 'C'))
			  << '\n';
}

inline int mainLoop() {
	uint64_t testcase_num = 1;
	// std::cin >> testcase_num;
	while (testcase_num--) {
		solve();
	}
	return 0;
}

int main() {
	redirectIo();
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	preprocess();
	return mainLoop();
}