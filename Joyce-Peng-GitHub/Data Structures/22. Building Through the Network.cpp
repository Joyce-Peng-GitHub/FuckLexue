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

struct Edge {
	size_t u, v;
	uint64_t w;
};

class Dsu {
public:
	Dsu(size_t n = 0) : m_fa_or_sz(n, -1) {}

	void assign(size_t n) { m_fa_or_sz.assign(n, -1); }
	void clear() { m_fa_or_sz.clear(); }
	void resize(size_t n) { m_fa_or_sz.resize(n, -1); }

	size_t size() const noexcept { return m_fa_or_sz.size(); }
	bool empty() const noexcept { return m_fa_or_sz.empty(); }

	size_t leader(size_t x) {
		if (m_fa_or_sz[x] < 0) return x;
		return (m_fa_or_sz[x] = leader(m_fa_or_sz[x]));
	}
	bool same(size_t x, size_t y) { return (leader(x) == leader(y)); }

	size_t size(size_t x) { return -m_fa_or_sz[leader(x)]; }

	size_t merge(size_t x, size_t y) {
		x = leader(x);
		y = leader(y);
		if (x == y) return x;
		if (-m_fa_or_sz[x] < -m_fa_or_sz[y]) std::swap(x, y);
		m_fa_or_sz[x] += m_fa_or_sz[y];
		m_fa_or_sz[y] = x;
		return x;
	}

	std::vector<std::vector<size_t>> groups() {
		std::vector<size_t> leader_of(size()), sz(size());
		for (size_t i = 0; i != size(); ++i) ++sz[leader_of[i] = leader(i)];
		std::vector<std::vector<size_t>> grps(size());
		for (size_t i = 0; i != size(); ++i) {
			grps[leader_of[i]].reserve(sz[leader_of[i]]);
		}
		for (size_t i = 0; i != size(); ++i) {
			grps[leader_of[i]].emplace_back(i);
		}
		grps.erase(std::remove_if(grps.begin(), grps.end(),
								  [](const std::vector<size_t> &grp) {
									  return grp.empty();
								  }),
				   grps.end());
		return grps;
	}

protected:
	std::vector<ssize_t> m_fa_or_sz; // if root, stores -size; else stores fa

private:
};

size_t m,
	n;
std::vector<Edge> edges;

inline void preprocess() {
	std::cin >> n >> m;
	edges.resize(m);
	for (auto &edge : edges) {
		std::cin >> edge.u >> edge.v >> edge.w;
		--edge.u;
		--edge.v;
	}
}

inline void solve() {
	std::sort(edges.begin(), edges.end(),
			  [](const Edge &a, const Edge &b) { return a.w < b.w; });
	Dsu dsu(n);
	uint64_t mst = 0;
	for (const auto &edge : edges) {
		if (!dsu.same(edge.u, edge.v)) {
			dsu.merge(edge.u, edge.v);
			mst += edge.w;
		}
	}
	for (size_t i = 0; i != n; ++i) {
		if (dsu.leader(i) != dsu.leader(0)) {
			std::cout << "-1\n";
			return;
		}
	}
	std::cout << mst << std::endl;
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