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

inline void solve() {
	size_t n;
	std::cin >> n;
	std::vector<std::pair<int64_t, int64_t>> promotions, suppressions;
	promotions.reserve(n);
	suppressions.reserve(n);
	for (size_t i = 0; i < n; ++i) {
		int64_t req, acq;
		std::cin >> req >> acq;
		((acq >= 0) ? promotions : suppressions).emplace_back(req, acq);
	}
	std::sort(promotions.begin(), promotions.end(),
			  [](const std::pair<int64_t, int64_t> &lhs,
				 const std::pair<int64_t, int64_t> &rhs) {
				  return ((lhs.first == rhs.first)
							  ? (lhs.second > rhs.second)
							  : (lhs.first < rhs.first));
			  });
	std::sort(suppressions.begin(), suppressions.end(),
			  [](const std::pair<int64_t, int64_t> &lhs,
				 const std::pair<int64_t, int64_t> &rhs) {
				  return (lhs.first + lhs.second > rhs.first + rhs.second);
			  });
	int64_t atk = 0, cost = 0;
	for (const auto &promotion : promotions) {
		if (atk < promotion.first) {
			cost += promotion.first - atk;
			atk = promotion.first;
		}
		atk += promotion.second;
	}
	for (const auto &suppression : suppressions) {
		if (atk < suppression.first) {
			cost += suppression.first - atk;
			atk = suppression.first;
		}
		atk += suppression.second;
	}
	std::cout << cost << std::endl;
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