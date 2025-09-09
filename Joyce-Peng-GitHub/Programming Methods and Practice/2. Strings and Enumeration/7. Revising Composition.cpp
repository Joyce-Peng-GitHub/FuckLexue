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
	bool new_sentence = true;
	for (char ch = std::cin.get(); ~ch; ch = std::cin.get()) {
		if (new_sentence && std::isalpha(ch)) {
			std::cout.put(std::toupper(ch));
			new_sentence = false;
		} else {
			std::cout.put(std::tolower(ch));
			if (ch == '.' || ch == '?' || ch == '!') {
				new_sentence = true;
			}
		}
	}
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