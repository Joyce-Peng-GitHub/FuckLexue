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

/**
 * @return sorted unique elements
 */
template <typename Iter,
		  typename Cmp = std::less<typename std::iterator_traits<Iter>::value_type>,
		  typename Eq = std::equal_to<typename std::iterator_traits<Iter>::value_type>>
inline std::vector<typename std::iterator_traits<Iter>::value_type>
discretize(Iter begin, Iter end, std::vector<size_t> &res,
		   Cmp cmp = Cmp(), Eq eq = Eq()) {
	auto unq = std::vector<typename std::iterator_traits<Iter>::value_type>(begin, end);
	size_t n = unq.size();
	std::sort(unq.begin(), unq.end(), cmp);
	unq.erase(std::unique(unq.begin(), unq.end(), eq), unq.end());
	res.resize(n);
	for (size_t i = 0; i != n; ++i) {
		res[i] = std::lower_bound(unq.begin(), unq.end(), *(begin++), cmp) - unq.begin();
	}
	return unq;
}

inline void preprocess() {}

inline void solve() {
	size_t n;
	std::cin >> n;
	std::vector<uint32_t> times(n << 1);
	for (size_t i = 0; i < n; ++i) {
		std::cin >> times[i << 1] >> times[(i << 1) | 1];
		++times[(i << 1) | 1];
	}
	std::vector<size_t> rks;
	std::vector<uint32_t> unq = discretize(times.begin(), times.end(), rks);
	std::vector<size_t> cnt_cover(unq.size());
	for (size_t i = 0; i < n; ++i) {
		++cnt_cover[rks[i << 1]];
		--cnt_cover[rks[(i << 1) | 1]];
	}
	for (size_t i = 1; i < cnt_cover.size(); ++i) {
		cnt_cover[i] += cnt_cover[i - 1];
	}
	std::vector<size_t> pref_sum(cnt_cover.size() + 1);
	for (size_t i = 0; i < cnt_cover.size(); ++i) {
		pref_sum[i + 1] = pref_sum[i] + (cnt_cover[i] == 1);
	}
	for (size_t i = 0; i < n; ++i) {
		size_t b = rks[i << 1], e = rks[(i << 1) | 1];
		if (pref_sum[e] == pref_sum[b]) {
			std::cout << (i + 1) << std::endl;
			return;
		}
	}
	std::cout << "-1\n";
}

int mainLoop() {
	solve();
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