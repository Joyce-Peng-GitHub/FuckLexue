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
	std::vector<std::vector<uint32_t>> dp(n, std::vector<uint32_t>(n));
	for (size_t len = 3; len <= n; ++len) {
		for (size_t i = 0; i + len <= n; ++i) {
			size_t j = i + len - 1;
			dp[i][j] = UINT32_MAX;
			for (size_t k = i + 1; k < j; ++k) {
				dp[i][j] = std::min(dp[i][j], dp[i][k] + dp[k][j] + arr[i] * arr[k] * arr[j]);
			}
		}
	}
	std::cout << dp[0][n - 1] << '\n';
}

std::vector<uint32_t> parseLine(const std::string &line) {
	std::istringstream iss(line);
	char ch;
	std::vector<uint32_t> res(2);
	iss >> ch >> res[0] >> ch >> res[1] >> ch;
	while (iss >> ch) {
		iss >> res.back() >> ch;
		res.emplace_back();
		iss >> res.back() >> ch;
	}
	return res;
}

int mainLoop() {
	std::string line;
	while (std::getline(std::cin, line)) {
		if (line == "end") {
			break;
		}
		solve(parseLine(line));
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