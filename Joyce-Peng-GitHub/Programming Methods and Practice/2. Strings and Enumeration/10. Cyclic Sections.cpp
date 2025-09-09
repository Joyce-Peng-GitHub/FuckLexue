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

inline void trivial(size_t p, size_t r) {
	for (size_t i = 0; i < r; ++i) {
		std::cout << '1';
		for (size_t j = 1; j < p; ++j) {
			std::cout << '0';
		}
	}
	std::cout << std::endl;
}

inline void solve() {
	std::string s, t;
	size_t p;
	std::cin >> p >> s;
	if (s.size() % p) {
		trivial(p, s.size() / p + 1);
		return;
	}
	std::string r = s.substr(0, p);
	bool leq = true; // r * (s.size() / p) <= s
	for (size_t i = 0; i < s.size(); ++i) {
		if (s[i] == r[i % p]) {
			continue;
		}
		if (s[i] < r[i % p]) {
			leq = false;
		}
		break;
	}
	if (leq) {
		unsigned carry = 1;
		for (size_t i = r.size(); i-- && carry;) {
			carry += r[i] ^ '0';
			r[i] = '0' ^ (carry % 10);
			carry /= 10;
		}
		if (carry) {
			trivial(p, s.size() / p + 1);
			return;
		}
	}
	for (size_t i = 0; i * p < s.size(); ++i) {
		std::cout << r;
	}
	std::cout << std::endl;
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