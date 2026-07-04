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

size_t n;
std::vector<std::vector<uint64_t>> dp;
std::vector<std::vector<size_t>> choice;

inline void preprocess() {}

void print(size_t beg, size_t len) {
	if (len == 1) {
		std::cout << 'A' << (beg + 1);
		return;
	}
	std::cout << '(';
	size_t first_len = choice[beg][len] - beg;
	print(beg, first_len);
	print(choice[beg][len], len - first_len);
	std::cout << ')';
}

inline void solve() {
	std::cin >> n;
	std::vector<uint64_t> arr(n + 1);
	for (size_t i = 0; i <= n; ++i) {
		std::cin >> arr[i];
	}
	if (n == 1) {
		std::cout << "0\n(A1)\n";
		return;
	}

	dp.resize(n, std::vector<uint64_t>(n + 1, UINT64_MAX));
	choice.resize(n, std::vector<size_t>(n + 1));
	for (size_t i = 0; i < n; ++i) {
		dp[i][0] = dp[i][1] = 0;
	}
	for (size_t len = 2; len <= n; ++len) {
		for (size_t beg = 0; beg + len <= n; ++beg) {
			for (size_t mid = beg + 1, end = beg + len; mid < end; ++mid) {
				auto val = dp[beg][mid - beg] + dp[mid][end - mid] + arr[beg] * arr[mid] * arr[end];
				if (val < dp[beg][len]) {
					dp[beg][len] = val;
					choice[beg][len] = mid;
				}
			}
		}
	}

	std::cout << dp[0][n] << '\n';
	print(0, n);
	std::cout << '\n';
}

inline int mainLoop() {
	uint64_t tc_num = 1;
	// std::cin >> tc_num;
	for (uint64_t tc = 0; tc < tc_num; ++tc) {
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