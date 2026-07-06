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

inline bool solve(bool is_first_tc) {
	size_t n;
	std::cin >> n;
	if (!n) return false;
	uint32_t cap;
	std::cin >> cap;
	cap *= 60 / 5;
	std::vector<uint32_t> biases(n), coefs(n), dists(n);
	for (auto &bias : biases) std::cin >> bias;
	for (auto &coef : coefs) std::cin >> coef;
	for (size_t i = 1; i < n; ++i) std::cin >> dists[i];

	auto gain = [&](size_t i, uint32_t t) {
		auto bias = biases[i];
		auto coef = coefs[i];
		if (coef) t = std::min(t, bias / coef + 1);
		return ((t * ((bias << 1) - coef * (t - 1))) >> 1);
	};

	std::vector<std::vector<uint32_t>> dp(n + 1, std::vector<uint32_t>(cap + 1));
	std::vector<std::vector<uint32_t>> choices(n + 1, std::vector<uint32_t>(cap + 1));
	{
		uint32_t sum = 0;
		for (size_t i = 0; i < n; ++i) {
			sum += dists[i];
			for (uint32_t j = 1; j <= cap; ++j) {
				for (uint32_t k = 0; k + sum <= j; ++k) {
					auto val = dp[i][j - k - dists[i]] + gain(i, k);
					if (val > dp[i + 1][j]) {
						dp[i + 1][j] = val;
						choices[i + 1][j] = k;
					}
				}
			}
		}
	}

	size_t best_len = 0;
	for (size_t i = 1; i <= n; ++i) {
		if (dp[i][cap] > dp[best_len][cap]) {
			best_len = i;
		}
	}
	auto ans = dp[best_len][cap];
	std::vector<uint32_t> res(n);
	for (size_t i = best_len; i--;) {
		res[i] = choices[i + 1][cap];
		cap -= res[i] + dists[i];
	}
	if (cap) res[0] += cap;

	if (!is_first_tc) std::cout << '\n';

	std::cout << (res[0] * 5);
	for (size_t i = 1; i < n; ++i) {
		std::cout << ',' << ' ' << (res[i] * 5);
	}
	std::cout << '\n';
	std::cout << "Number of fish expected: " << ans << '\n';

	return true;
}

inline int mainLoop() {
	if (solve(true)) {
		while (solve(false));
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