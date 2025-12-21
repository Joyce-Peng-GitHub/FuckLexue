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

constexpr size_t N = 26;
size_t m, n, src;
std::array<std::vector<std::pair<size_t, uint64_t>>, N> adj;

inline void preprocess() {
	char ch;
	std::cin >> n >> ch >> m >> ch >> ch;
	src = ch - 'a';
	for (size_t i = 0; i < m; ++i) {
		std::cin >> ch >> ch;
		size_t u = ch - 'a';
		std::cin >> ch >> ch;
		size_t v = ch - 'a';
		uint64_t w;
		std::cin >> ch >> w >> ch;
		adj[u].push_back({v, w});
	}
}

inline void solve() {
	std::bitset<N> vis;
	std::array<uint64_t, N> dist;
	std::fill(dist.begin(), dist.begin() + n, UINT64_MAX);
	using Pr = std::pair<uint64_t, size_t>; // (dist, vertex)
	std::priority_queue<Pr, std::vector<Pr>, std::greater<Pr>> pq;
	dist[src] = 0;
	pq.push({0, src});
	while (pq.size()) {
		auto cur = pq.top().second;
		pq.pop();
		if (vis[cur]) {
			continue;
		}
		vis[cur] = true;
		for (const auto &edge : adj[cur]) {
			auto nxt = edge.first;
			auto w = edge.second;
			if (dist[nxt] > dist[cur] + w) {
				dist[nxt] = dist[cur] + w;
				pq.push({dist[nxt], nxt});
			}
		}
	}
	for (size_t i = 0; i < n; ++i) {
		std::cout << SC<char>(i + 'a') << ':' << dist[i] << '\n';
	}
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