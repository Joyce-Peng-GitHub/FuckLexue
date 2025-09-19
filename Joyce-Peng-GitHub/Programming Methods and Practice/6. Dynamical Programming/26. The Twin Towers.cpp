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

inline void solve(size_t i_case, size_t m, size_t n) {
	std::vector<uint32_t> a(m), b(n);
	for (auto &x : a) {
		std::cin >> x;
	}
	for (auto &x : b) {
		std::cin >> x;
	}
	std::vector<std::vector<size_t>> dp(m + 1, std::vector<size_t>(n + 1));
	for (size_t i = 0; i < m; ++i) {
		for (size_t j = 0; j < n; ++j) {
			dp[i + 1][j + 1] = ((a[i] == b[j]) ? (dp[i][j] + 1) : std::max(dp[i][j + 1], dp[i + 1][j]));
		}
	}
	std::cout << "Twin Towers #" << i_case << '\n'
			  << "Number of Tiles : " << dp[m][n] << "\n";
}

int mainLoop() {
	for (size_t i = 1, m, n;; ++i) {
		std::cin >> m >> n;
		if (m || n) {
			solve(i, m, n);
		} else {
			break;
		}
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