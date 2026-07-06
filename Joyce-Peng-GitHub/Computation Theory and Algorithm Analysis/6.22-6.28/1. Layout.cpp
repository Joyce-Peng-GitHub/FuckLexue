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

template <typename W>
struct EdgeImpl {
	size_t u, v;
	W w;
};

template <typename Weight = int64_t, bool is_directed = true>
class Graph {
public:
	// When Weight is void, Edge does not has member w
	using Edge = EdgeImpl<Weight>;

	Graph(size_t n = 0) : m_adj(n) {}
	Graph(size_t n, const std::vector<Edge> &edges)
		: m_edges(edges), m_adj(n) { m_insertEdgesToAdj(); }

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
			  typename = typename std::enable_if<
				  std::is_same<W, Weight>::value>::type>
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

	std::tuple<Weight, std::vector<bool>, std::vector<Weight>>
	dinic(size_t src, size_t dst,
		  Weight lim = std::numeric_limits<Weight>::max()) const;

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
inline std::vector<Weight>
Graph<Weight, is_directed>::spfa(size_t src) const {
	std::vector<Weight> dist(m_adj.size(), std::numeric_limits<Weight>::max());
	std::vector<bool> inq(m_adj.size());
	std::vector<size_t> cnt(m_adj.size());
	std::queue<size_t> q;

	dist[src] = 0;
	q.emplace(src);
	while (q.size()) {
		auto frm = q.front();
		inq[frm] = false;
		q.pop();
		for (auto i : m_adj[frm]) {
			auto to = (is_directed
						   ? m_edges[i].v
						   : ((m_edges[i].u == frm) ? m_edges[i].v : m_edges[i].u));
			if (is_directed &&
				frm == m_edges[i].v && m_edges[i].u != m_edges[i].v) continue;
			auto w = m_edges[i].w;
			if (dist[to] > dist[frm] + w) {
				dist[to] = dist[frm] + w;
				/**
				 * the shortest path between 2 vertices consists of at most
				 * (n - 1) edgess
				 */
				if ((cnt[to] = cnt[frm] + 1) >= m_adj.size()) return {};
				if (!inq[to]) {
					inq[to] = true;
					q.emplace(to);
				}
			}
		}
	}
	return dist;
}

inline void preprocess() {}

inline void solve() {
	size_t n;
	std::array<size_t, 2> m;
	std::cin >> n >> m[0] >> m[1];
	std::vector<EdgeImpl<int32_t>> edges(m[0] + m[1]);
	for (unsigned i = 0; i < m.size(); ++i) {
		for (size_t j = 0; j < m[i]; ++j) {
			size_t u, v;
			int32_t w;
			std::cin >> u >> v >> w;
			--u, --v;
			assert(u < v);
			if (i) {
				edges.push_back(EdgeImpl<int32_t>{v, u, -w});
			} else {
				edges.push_back(EdgeImpl<int32_t>{u, v, w});
			}
		}
	}
	for (size_t i = 0; i + 1 < n; ++i) {
		edges.push_back(EdgeImpl<int32_t>{i + 1, i, 0});
	}

	Graph<int32_t> graph(n + 1, edges);
	for (size_t i = 0; i < n; ++i) {
		graph.insertEdge(n, i, 0);
	}
	if (graph.spfa(n).empty()) {
		std::cout << "-1\n";
		return;
	}

	graph.assign(n, edges);
	auto dist = graph.spfa(0);
	assert(dist.size());
	if (dist[n - 1] == INT32_MAX) {
		std::cout << "-2\n";
		return;
	}
	std::cout << (dist[n - 1] - dist[0]) << '\n';
}

inline int mainLoop() {
	uint64_t tc_num = 1;
	// std::cin >> tc_num;
	for (uint64_t tc = 0; tc < tc_num; ++tc) {
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