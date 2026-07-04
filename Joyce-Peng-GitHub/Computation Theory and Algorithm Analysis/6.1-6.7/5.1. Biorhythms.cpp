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

/**
 * @brief solve the system of equations x % mod == rem for each (mod, rem), the
 * solution expressed as x = period * n + ans for any integer n. This is an online
 * algorithm. Each call to this function adds a new equation to the system. You
 * should initialize period = 1, ans = 0 before any equation is added.
 * @return true if a solution exists, false otherwise
 */
inline bool exCrt(
	int64_t mod, int64_t rem,
	int64_t &period, int64_t &ans
) {
	if (mod == 0) return false;
	if (mod < 0) mod = -mod;
	rem = (rem % mod + mod) % mod;

	int64_t x, y, g = exGcd(period, mod, x, y);
	if ((rem - ans) % g != 0) return false;
	auto q = mod / g;
	x = (((rem - ans) / g * static_cast<__int128_t>(x)) % q + q) % q;

	auto new_period = period * (mod / g);
	ans = (ans + period * x) % new_period;
	period = new_period;
	return true;
}

inline bool solve(uint64_t tc) {
	constexpr size_t N = 3;
	constexpr std::array<int64_t, N> MODS{23, 28, 33};
	std::array<int64_t, N> rems;
	for (auto &rem : rems) std::cin >> rem;
	if (std::all_of(
			rems.begin(), rems.end(),
			[](int64_t rem) { return (rem == -1); }
		)) {
		return false;
	}
	int64_t period = 1, base = 0;
	for (size_t i = 0; i < N; ++i) {
		if (!exCrt(MODS[i], rems[i], period, base)) {
			std::exit(-1);
		}
	}
	int64_t cur;
	std::cin >> cur;
	int64_t nxt = 1 + (period - (cur - base) % period - 1) % period;
	// if (!nxt) nxt = period;
	std::cout << "Case " << (tc + 1) << ": the next triple peak occurs in " << nxt << " days.\n";
	return true;
}

inline int mainLoop() {
	for (uint64_t tc = 0; solve(tc); ++tc);
	return 0;
}

int main() {
	redirectIo();
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	preprocess();
	return mainLoop();
}