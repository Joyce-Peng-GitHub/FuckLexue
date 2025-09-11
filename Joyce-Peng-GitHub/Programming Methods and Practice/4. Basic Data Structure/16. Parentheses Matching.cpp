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

inline std::pair<size_t, size_t> unmatchedParenthesesOf(const std::string &s) {
	size_t open = 0, close = 0;
	for (char c : s) {
		if (c == '(') {
			++open;
		} else if (c == ')') {
			if (open > 0) {
				--open;
			} else {
				++close;
			}
		}
	}
	return {open, close};
}

inline void solve() {
	size_t n;
	std::cin >> n;
	std::vector<size_t> opens, closes;
	opens.reserve(n);
	closes.reserve(n);
	size_t cnt_matched = 0;
	for (size_t i = 0; i < n; ++i) {
		std::string s;
		std::cin >> s;
		auto unmatched = unmatchedParenthesesOf(s);
		if (static_cast<bool>(unmatched.first) == static_cast<bool>(unmatched.second)) {
			if (!unmatched.first && !unmatched.second) {
				++cnt_matched;
			}
			continue;
		}
		if (unmatched.first) {
			opens.emplace_back(unmatched.first);
		} else {
			closes.emplace_back(unmatched.second);
		}
	}
	cnt_matched >>= 1;
	std::sort(opens.begin(), opens.end());
	std::sort(closes.begin(), closes.end());
	size_t i_opens = 0, i_closes = 0;
	while (i_opens < opens.size() && i_closes < closes.size()) {
		if (opens[i_opens] == closes[i_closes]) {
			++i_opens, ++i_closes, ++cnt_matched;
			continue;
		}
		++((opens[i_opens] < closes[i_closes]) ? i_opens : i_closes);
	}
	std::cout << cnt_matched << std::endl;
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