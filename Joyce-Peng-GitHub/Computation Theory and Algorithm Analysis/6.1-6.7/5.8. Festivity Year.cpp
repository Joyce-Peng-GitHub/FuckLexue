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

inline void solve() {
	constexpr int64_t LIMIT = 1e9;

	size_t m, n;
	std::cin >> n >> m;
	assert(m && n);

	std::vector<std::vector<size_t>> perms(m, std::vector<size_t>(n));
	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < m; ++j) {
			std::cin >> perms[j][i];
			--perms[j][i];
		}
	}

	std::vector<std::vector<size_t>> composed_perms(m + 1, std::vector<size_t>(n));
	for (size_t i = 0; i < n; ++i) {
		composed_perms[0][i] = i;
	}
	for (size_t i = 0; i < m; ++i) {
		for (size_t j = 0; j < n; ++j) {
			composed_perms[i + 1][j] = perms[i][composed_perms[i][j]];
		}
	}

	std::vector<size_t> cycle_id(n, size_t(-1)), pos_in_cycle(n, size_t(-1)), cycle_lens;
	for (size_t i = 0; i < n; ++i) {
		if (~cycle_id[i]) continue;
		size_t cycle_len = 0;
		for (size_t j = i; cycle_id[j] == size_t(-1); j = composed_perms[m][j]) {
			cycle_id[j] = cycle_lens.size();
			pos_in_cycle[j] = (cycle_len++);
		}
		cycle_lens.emplace_back(cycle_len);
	}

	int64_t ans = LIMIT;
	std::vector<size_t> inv(n);
	for (size_t r = 1; r <= m; ++r) {
		for (size_t i = 0; i < n; ++i) {
			inv[composed_perms[r][i]] = i;
		}

		bool not_valid = false;
		int64_t period = 1, base = 0;
		for (size_t i = 0; i < n; ++i) {
			if (cycle_id[i] != cycle_id[inv[i]]) {
				not_valid = true;
				break;
			}

			auto cycle_len = cycle_lens[cycle_id[i]];
			size_t dist = (cycle_len - pos_in_cycle[i] + pos_in_cycle[inv[i]]) % cycle_len;
			if (!exCrt(cycle_len, dist, period, base)) {
				not_valid = true;
				break;
			}
		}
		if (not_valid) continue;

		ans = std::min(ans, std::min<int64_t>(LIMIT, base * m + r));
	}

	if (ans < LIMIT) {
		std::cout << ans << '\n';
	} else {
		std::cout << "No one knows.\n";
	}
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