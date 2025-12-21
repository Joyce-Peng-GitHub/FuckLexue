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
	std::vector<bool> mat;
	for (bool e; std::cin >> e; mat.push_back(e));
	size_t n = SC<size_t>(std::sqrt(mat.size()));
	assert(n * n == mat.size());
	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < n; ++j) {
			for (size_t k = 0; k < n; ++k) {
				mat[j * n + k] = (mat[j * n + k] | (mat[j * n + i] & mat[i * n + k]));
			}
		}
	}
	for (size_t i = 0; i < n; ++i) {
		std::cout << mat[i * n];
		for (size_t j = 1; j < n; ++j) {
			std::cout << ' ' << mat[i * n + j];
		}
		std::cout << '\n';
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