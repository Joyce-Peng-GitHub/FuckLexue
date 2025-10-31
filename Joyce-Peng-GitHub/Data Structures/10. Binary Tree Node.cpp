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

inline unsigned floorLogn2(uint64_t x) {
#if __cplusplus >= 202002L
	return (std::bit_width(x) - 1);
#else
	return (x ? (sizeof(uint64_t) * 8 - __builtin_clzll(x) - 1) : -1);
#endif
}

inline void preprocess() {}

inline uint64_t f(uint64_t m, uint64_t a) {
	uint64_t res = 0;
	while (true) {
		if (!a) return res;
		auto p = floorLogn2(a);
		if (a == (uint64_t(1) << p)) return (res + ((uint64_t(1) << (p + 1)) + m - p - 1));
		res += (uint64_t(1) << (p + 1)) + m - (p + 1);
		m = p, a -= (uint64_t(1) << p);
	}
}

/**
 * @brief behaves as if it generates func[beg, end) and
 * 	performs std::upper_bound on it
 */
template <typename T, typename Ret, typename Func,
		  typename Cmp = std::less<Ret>>
inline T upperBound(T beg, T end, const Ret &val, Func func = Func(), Cmp cmp = Cmp()) {
	while (beg < end) {
		T mid = beg + (end - beg) / 2;
		if (cmp(val, func(mid))) {
			end = mid;
		} else {
			beg = mid + 1;
		}
	}
	return beg;
}

inline void solve() {
	uint64_t n, m;
	std::cin >> n >> m;
	uint64_t mx = ((m < 64) ? std::min(n, uint64_t(1) << m) : n);
	auto res = upperBound(uint64_t(0), mx + 1, n, [=](uint64_t a) { return f(m, a); });
	if (res > mx || f(m, res) > n) --res;
	std::cout << res << '\n';
}

inline int mainLoop() {
	uint64_t testcase_num;
	std::cin >> testcase_num;
	while (testcase_num--) solve();
	return 0;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr), std::cout.tie(nullptr);
	redirectIO();
	preprocess();
	return mainLoop();
}