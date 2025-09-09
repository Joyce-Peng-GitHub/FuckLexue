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
 * @return the number of inversions
 */
template <typename OutputIter, typename AuxIter>
size_t mergeSort(OutputIter first, OutputIter last,
				 AuxIter aux) {
	size_t n = std::distance(first, last);
	if (n <= 1) {
		return 0;
	}
	auto mid = std::next(first, n >> 1);
	size_t inv = mergeSort(first, mid, aux) + mergeSort(mid, last, aux);
	auto i = first, j = mid, k = aux;
	size_t cnt = (n >> 1);
	while (i != mid && j != last) {
		if (*i > *j) {
			*(k++) = *(j++);
			inv += cnt;
		} else {
			*(k++) = *(i++);
			--cnt;
		}
	}
	while (i != mid) {
		*(k++) = *(i++);
	}
	while (j != last) {
		*(k++) = *(j++);
	}
	std::copy(aux, k, first);
	return inv;
}
template <typename OutputIter,
		  typename Container =
			  std::vector<typename std::iterator_traits<OutputIter>::value_type>>
inline size_t mergeSort(OutputIter first, OutputIter last) {
	auto aux = Container(std::distance(first, last));
	return mergeSort(first, last, aux.begin());
}

inline void preprocess() {}

inline void solve() {
	size_t n;
	std::cin >> n;
	std::vector<int32_t> arr(n);
	for (auto &x : arr) {
		std::cin >> x;
	}
	std::cout << mergeSort(arr.begin(), arr.end()) << std::endl;
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