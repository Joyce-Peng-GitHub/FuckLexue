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

inline void solve() {
	constexpr size_t N = 26;
	std::bitset<N> is_vert;
	std::array<unsigned, N> in_deg{}, out_deg{};

	char ch = std::cin.get();
	is_vert[ch - 'a'] = true;
	while (std::cin.get(ch) && ch != '\n') {
		assert(ch == ',');
		std::cin.get(ch);
		assert(std::islower(ch));
		is_vert[ch - 'a'] = true;
	}

	std::cin >> ch >> ch;
	++out_deg[ch - 'a'];
	std::cin >> ch >> ch;
	++in_deg[ch - 'a'];
	while (std::cin >> ch >> ch >> ch >> ch) {
		++out_deg[ch - 'a'];
		std::cin >> ch >> ch;
		++in_deg[ch - 'a'];
	}

	bool not_first = false;
	for (size_t i = 0; i < N; ++i) {
		if (is_vert[i] && in_deg[i] == 0) {
			if (not_first) {
				std::cout << ',';
			}
			std::cout << SC<char>('a' + i);
			not_first = true;
		}
	}
	std::cout << '\n';

	not_first = false;
	for (size_t i = 0; i < N; ++i) {
		if (is_vert[i] && out_deg[i] == 0) {
			if (not_first) {
				std::cout << ',';
			}
			std::cout << SC<char>('a' + i);
			not_first = true;
		}
	}
	std::cout << '\n';
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