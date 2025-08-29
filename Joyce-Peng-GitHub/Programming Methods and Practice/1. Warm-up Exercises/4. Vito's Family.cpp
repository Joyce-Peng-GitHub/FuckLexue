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

constexpr uint32_t P = 3e4;

inline void preprocess() {}

inline void solve() {
	size_t n;
	std::cin >> n;
	std::vector<int32_t> arr(n);
	for (auto &x : arr) {
		std::cin >> x;
	}
	int32_t min = INT32_MAX;
	for (int32_t p = 1; p < P; ++p) {
		int32_t sum = 0;
		for (auto x : arr) {
			sum += std::abs(x - p);
		}
		min = std::min(min, sum);
	}
	std::cout << min << std::endl;
}

int mainLoop() {
	uint64_t cnt_testcases;
	std::cin >> cnt_testcases;
	while (cnt_testcases--) {
		solve();
	}
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