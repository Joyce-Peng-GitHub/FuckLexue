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
	std::vector<uint32_t> arr(n);
	for (auto &x : arr) {
		std::cin >> x;
	}
	std::vector<std::vector<uint32_t>> dp(n, std::vector<uint32_t>(n));
	for (size_t i = 0; i < n; ++i) {
		dp[i][i] = n * arr[i];
	}
	for (size_t len = 2; len <= n; ++len) {
		for (size_t i = 0; i + len <= n; ++i) {
			size_t j = i + len - 1;
			dp[i][j] = std::max(dp[i + 1][j] + arr[i] * (n - len + 1),
								dp[i][j - 1] + arr[j] * (n - len + 1));
		}
	}
	std::cout << dp[0][n - 1] << '\n';
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