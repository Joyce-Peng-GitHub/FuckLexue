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

uint64_t dfs(uint64_t num, uint64_t denom, uint64_t min_unit, size_t max_cnt, uint64_t max_prod) {
	if (!max_cnt || min_unit > max_prod) {
		return 0;
	}
	auto g = std::__gcd(num, denom);
	num /= g, denom /= g;
	uint64_t res = (num == 1 && denom >= min_unit && denom <= max_prod);
	min_unit = std::max(min_unit, denom / num + 1);
	uint64_t max_unit = std::min<uint64_t>(std::sqrt(max_prod), (max_cnt--) * denom / num);
	for (uint64_t unit = min_unit; unit <= max_unit; ++unit) {
		res += dfs(num * unit - denom, denom * unit, unit, max_cnt, max_prod / unit);
	}
	return res;
}

inline void solve(uint64_t num, uint64_t denom, size_t max_cnt, uint64_t max_prod) {
	std::cout << dfs(num, denom, 1, max_cnt, max_prod) << '\n';
}

int mainLoop() {
	uint64_t num, denom;
	size_t max_cnt;
	uint64_t max_prod;
	while ((std::cin >> num >> denom >> max_prod >> max_cnt) && (num || denom || max_prod || max_cnt)) {
		solve(num, denom, max_cnt, max_prod);
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