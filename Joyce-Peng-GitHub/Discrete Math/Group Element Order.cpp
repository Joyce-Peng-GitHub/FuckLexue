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

/**
 * The order of an element x in group (Z, + mod 18) is the smallest positive
 * 	integer o such that o*x mod 18=0, the identity element, i.e. 18|o*x.
 * 	Since factors of 18 are 1,2,3,6,9,18, some of which are also factors of x,
 * 	we can check them one by one.
 */
inline void solve() {
	constexpr int64_t MOD = 18;
	constexpr std::array<int64_t, 6> FACTORS = {1, 2, 3, 6, 9, 18};
	int64_t x;
	std::cin >> x;
	x %= MOD;
	for (const auto &factor : FACTORS) {
		if ((factor * x) % MOD == 0) {
			std::cout << factor << std::endl;
			return;
		}
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