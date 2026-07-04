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

constexpr size_t M = 3, N = 30;
std::array<std::array<uint64_t, 1 << M>, N + 1> dp;
constexpr std::array<std::array<std::pair<unsigned, unsigned>, 3>, 1 << M> TRANSFER{
	{{{{7, 1}}},
	 {{{6, 1}}},
	 {{{5, 1}}},
	 {{{4, 1}, {7, 1}}},
	 {{{3, 1}}},
	 {{{2, 1}}},
	 {{{1, 1}, {7, 1}}},
	 {{{0, 1}, {3, 1}, {6, 1}}}}
};

inline void preprocess() {
	dp[0][7] = 1;
	for (size_t i = 0; i < N; ++i) {
		for (size_t j = 0; j < (1 << M); ++j) {
			for (const auto &pr : TRANSFER[j]) {
				dp[i + 1][pr.first] += dp[i][j] * pr.second;
			}
		}
	}
	// for (size_t i = 1; i <= N; ++i) {
	// 	for (size_t j = 0; j < (1 << M); ++j) {
	// 		std::cerr << dp[i][j] << ' ';
	// 	}
	// 	std::cerr << '\n';
	// }
}

inline void solve(size_t n) {
	std::cout << dp[n][7] << '\n';
}

inline int mainLoop() {
	ptrdiff_t n;
	while ((std::cin >> n) && n >= 0) {
		solve(n);
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