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
 * @brief behaves as if it generates func[beg, end) and
 * 	performs std::lower_bound on it
 */
template <typename T, typename Ret, typename Func,
		  typename Cmp = std::less<Ret>>
inline T lowerBound(T beg, T end, const Ret &val,
					Func func = Func(), Cmp cmp = Cmp()) {
	while (beg < end) {
		T mid = beg + (end - beg) / 2;
		if (cmp(func(mid), val)) {
			beg = mid + 1;
		} else {
			end = mid;
		}
	}
	return beg;
}

inline void solve() {
	size_t m, n;
	std::scanf("%zu%zu", &n, &m);
	std::vector<uint64_t> arr(n);
	for (auto &e : arr) {
		uint64_t integer, decimal;
		std::scanf("%" SCNu64 ".%" SCNu64, &integer, &decimal);
		e = integer * 100 + decimal;
		// std::fprintf(stderr, "%" PRIu64 "\n", e);
	}
	auto check = [&, m](uint64_t len) -> uint64_t {
		if (len == 0) return true;
		uint64_t num = 0;
		for (auto e : arr) {
			num += e / len;
		}
		return (num >= m);
	};
	uint64_t beg = 0, end = *std::max_element(arr.begin(), arr.end()) + 1;
	auto ans = lowerBound(beg, end, false, check, std::greater<bool>()) - 1;
	std::printf("%" PRIu64 ".%02" PRIu64 "\n", ans / 100, ans % 100);
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