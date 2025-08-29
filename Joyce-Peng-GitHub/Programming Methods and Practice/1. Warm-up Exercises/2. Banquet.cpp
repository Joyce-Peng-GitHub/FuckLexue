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

inline unsigned ceilLogn2(uint64_t x) {
	return (x ?
#if __cplusplus >= 202002L
			  std::bit_width(x - 1)
#else
			  ((x == 1) ? 0 : (sizeof(uint64_t) * 8 - __builtin_clzll(x - 1)))
#endif
			  : -1);
}

inline void preprocess() {}

inline void solve() {
	uint64_t n;
	std::cin >> n;
	std::cout << ceilLogn2(n) << std::endl;
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