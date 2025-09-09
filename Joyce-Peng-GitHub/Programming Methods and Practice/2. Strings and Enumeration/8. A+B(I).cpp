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

inline void input(std::vector<bool> &x) {
	std::string s;
	std::cin >> s;
	x.resize(s.size());
	for (size_t i = 0; i != x.size(); ++i) {
		x[i] = s[s.size() - 1 - i] ^ '0';
	}
}

inline void repeat(uint64_t cnt, char ch) {
	while (cnt--) {
		std::cout.put(ch);
	}
}

inline void output(const std::vector<bool> &x) {
	for (size_t i = x.size(); i--;) {
		std::cout.put('0' | x[i]);
	}
}

inline void solve() {
	std::vector<bool> a, b, c;
	input(a);
	input(b);
	c.reserve(std::max(a.size(), b.size()) + 1);
	unsigned carry = 0;
	size_t i = 0;
	for (; i != a.size() && i != b.size(); ++i) {
		carry += a[i] + b[i];
		c.push_back(carry & 1);
		carry >>= 1;
	}
	for (; i != a.size(); ++i) {
		carry += a[i];
		c.push_back(carry & 1);
		carry >>= 1;
	}
	for (; i < b.size(); ++i) {
		carry += b[i];
		c.push_back(carry & 1);
		carry >>= 1;
	}
	while (carry) {
		c.push_back(carry & 1);
		carry >>= 1;
	}
	repeat(c.size() - a.size() + 2, ' ');
	output(a);
	std::cout << '\n'
			  << '+';
	repeat(c.size() - b.size() + 1, ' ');
	output(b);
	std::cout << '\n';
	repeat(c.size() + 2, '-');
	std::cout << '\n';
	repeat(2, ' ');
	output(c);
	std::cout << '\n';
}

int mainLoop() {
	uint64_t cnt_testcases;
	std::cin >> cnt_testcases;
	while (cnt_testcases--) {
		solve();
	}
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