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

inline void preprocess() {}

inline void solve() {
	size_t n;
	uint64_t storage_cost;
	std::cin >> n >> storage_cost;
	std::vector<uint64_t> produce_costs(n), requirements(n);
	for (size_t i = 0; i < n; ++i) std::cin >> produce_costs[i] >> requirements[i];

	uint64_t ans = 0;
	std::vector<uint64_t> costs;
	costs.reserve(n);
	for (size_t i = 0; i < n; ++i) {
		for (auto &cost : costs) cost += storage_cost;
		auto iter = std::upper_bound(costs.begin(), costs.end(), produce_costs[i]);
		costs.insert(iter, produce_costs[i]);
		ans += costs[0] * requirements[i];
	}

	std::cout << ans << '\n';
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