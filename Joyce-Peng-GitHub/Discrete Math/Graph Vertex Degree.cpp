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
	std::cin >> n;
	std::vector<size_t> in_degs(n), out_degs(n);
	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < n; ++j) {
			size_t rep;
			std::cin >> rep;
			in_degs[j] += rep;
			out_degs[i] += rep;
		}
	}
	for (size_t i = 0; i < n; ++i) {
		std::cout << out_degs[i] << ' ' << in_degs[i] << '\n';
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