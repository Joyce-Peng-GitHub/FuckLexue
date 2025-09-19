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

inline void solve(const std::vector<uint32_t> &arr) {
	size_t n = arr.size();
	if (!n) {
		std::cout << "The minimum cutting is 0.\n";
		return;
	}
	std::vector<uint32_t> pref_sum(n + 1);
	for (size_t i = 0; i < n; ++i) {
		pref_sum[i + 1] = pref_sum[i] + arr[i];
	}
	std::vector<std::vector<uint32_t>> dp(n, std::vector<uint32_t>(n));
	for (size_t len = 2; len <= n; ++len) {
		for (size_t i = 0; i + len <= n; ++i) {
			size_t j = i + len - 1;
			dp[i][j] = UINT32_MAX;
			for (size_t k = i; k < j; ++k) {
				dp[i][j] = std::min(dp[i][j],
									dp[i][k] + dp[k + 1][j] +
										pref_sum[j + 1] - pref_sum[i]);
			}
		}
	}
	std::cout << dp[0][n - 1] << '\n';
}

int mainLoop() {
	uint32_t len;
	size_t n;
	std::vector<uint32_t> arr;
	while (std::cin >> len && len) {
		std::cin >> n;
		arr.reserve(n + 1);
		arr.resize(n);
		for (auto &x : arr) {
			std::cin >> x;
		}
		if (n) {
			arr.emplace_back(len - arr.back());
			for (size_t i = n - 1; i; --i) {
				arr[i] -= arr[i - 1];
			}
		}
		solve(arr);
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