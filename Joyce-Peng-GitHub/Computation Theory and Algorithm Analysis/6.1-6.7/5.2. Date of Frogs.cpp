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
 * @brief solve the equation a * x + b * y == gcd(a, b)
 * @return gcd(a, b)
 */
inline int64_t exGcd(int64_t a, int64_t b, int64_t &x, int64_t &y) {
	x = 1, y = 0;
	int64_t u = 0, v = 1;
	while (b) {
		int64_t q = a / b;
		std::tie(a, b, x, y, u, v) =
			std::make_tuple(b, a - q * b, u, v, x - q * u, y - q * v);
	}
	return a;
}

inline void solve() {
	int64_t x0, y0, m, n, l;
	std::cin >> x0 >> y0 >> m >> n >> l;
	assert(x0 != y0 && x0 > 0 && y0 > 0 && m > 0 && n > 0 && l > 0);

	auto a = ((m - n) % l + l) % l, b = ((y0 - x0) % l + l) % l;
	int64_t inv, tmp, gcd = exGcd(a, l, inv, tmp);

	if (a % gcd == 0) {
		if (b % gcd) {
			std::cout << "Impossible\n";
			return;
		}
		a /= gcd, b /= gcd, l /= gcd;
		gcd = exGcd(a, l, inv, tmp);
	}

	inv = (inv % l + l) % l;
	std::cout << ((inv * b) % l) << '\n';
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