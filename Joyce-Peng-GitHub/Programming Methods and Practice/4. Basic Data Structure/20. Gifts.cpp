#include <bits/stdc++.h>

inline void redirectIO() {
#ifndef ONLINE_JUDGE
	char filename[] = __FILE__;
	filename[sizeof(filename) - 4] = 'i';
	filename[sizeof(filename) - 3] = 'n';
	filename[sizeof(filename) - 2] = '\0';
	std::freopen(filename, "r", stdin);
	filename[sizeof(filename) - 4] = 'o';
	filename[sizeof(filename) - 3] = 'u';
	filename[sizeof(filename) - 2] = 't';
	std::freopen(filename, "w", stdout);
#endif
}

inline void preprocess() {}

inline void solve() {
	size_t n;
	std::cin >> n;
	std::multimap<uint32_t, size_t> sz_to_id;
	for (size_t i = 0; i < n; ++i) {
		uint32_t sz;
		std::cin >> sz;
		sz_to_id.emplace(sz, i + 1);
	}
	std::vector<std::vector<size_t>> groups;
	while (sz_to_id.size()) {
		std::vector<size_t> group;
		for (auto cur = sz_to_id.begin(); cur != sz_to_id.end();) {
			group.emplace_back(cur->second);

			auto sz = cur->first;
			sz_to_id.erase(cur);
			cur = sz_to_id.lower_bound(sz << 1);
		}
		groups.emplace_back(std::move(group));
	}
	std::cout << groups.size() << '\n';
	for (const auto &group : groups) {
		std::cout << group.size();
		for (auto mem : group) {
			std::cout << ' ' << mem;
		}
		std::cout << '\n';
	}
}

int mainLoop() {
	solve();
	return 0;
}

int main() {
	redirectIO();
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	preprocess();
	return mainLoop();
}