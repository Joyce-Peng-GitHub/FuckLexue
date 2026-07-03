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

inline bool solve() {
	size_t n;
	std::cin >> n;
	if (!n) return false;

	std::vector<uint64_t> nums(n << 1), coords(n << 1);
	{
		int x;
		std::cin >> x;
		assert(x == 0);
	}
	for (size_t i = 1; i < n; ++i) {
		std::cin >> coords[i] >> nums[i];
		nums[n + i] = nums[i];
		coords[n + i] = coords[i];
	}
	std::cin >> coords[n];
	for (size_t i = 2; i < (n << 1); ++i) {
		coords[i] += coords[i - 1];
	}

	std::vector<uint64_t> sum((n << 1) | 1);
	for (size_t i = 0; i < (n << 1); ++i) {
		sum[i + 1] = sum[i] + nums[i];
	}

	std::array<std::vector<std::vector<uint64_t>>, 2> dp;
	for (unsigned b = 0; b < 2; ++b) {
		dp[b].assign(n << 1, std::vector<uint64_t>(n + 1, UINT32_MAX));
		dp[b][0][1] = dp[b][n][1] = 0;
	}

	for (size_t len = 2; len <= n; ++len) {
		for (size_t i = 0; i + len <= (n << 1); ++i) {
			if (i + 1 < (n << 1)) {
				dp[0][i][len] = std::min(
					dp[0][i + 1][len - 1] + (sum[n] - (sum[i + len] - sum[i + 1])) * (coords[i + 1] - coords[i]),
					dp[1][i + 1][len - 1] + (sum[n] - (sum[i + len] - sum[i + 1])) * (coords[i + len - 1] - coords[i])
				);
			}
			if (i + len > 1) {
				dp[1][i][len] = std::min(
					dp[0][i][len - 1] + (sum[n] - (sum[i + len - 1] - sum[i])) * (coords[i + len - 1] - coords[i]),
					dp[1][i][len - 1] + (sum[n] - (sum[i + len - 1] - sum[i])) * (coords[i + len - 1] - coords[i + len - 2])
				);
			}
		}
	}

	uint64_t ans = UINT64_MAX;
	for (size_t i = 0; i < n; ++i) {
		ans = std::min(ans, std::min(dp[0][i][n], dp[1][i][n]));
	}
	std::cout << ans << '\n';

	return true;
}

inline int mainLoop() {
	while (solve());
	return 0;
}

int main() {
	redirectIo();
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	preprocess();
	return mainLoop();
}