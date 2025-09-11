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

inline std::vector<unsigned> parseLine(const std::string &line) {
	std::istringstream iss(line);
	std::vector<unsigned> arr;
	unsigned val;
	while (iss >> val) {
		arr.push_back(val);
	}
	return arr;
}

inline void preprocess() {}

inline void flip(std::vector<unsigned> &arr, size_t from) {
	std::cout << (from + 1) << ' ';
	std::reverse(arr.begin() + from, arr.end());
}

inline void solve(std::vector<unsigned> arr) {
	for (size_t i = 0; i < arr.size(); ++i) {
		std::cout << arr[i] << (i + 1 == arr.size() ? '\n' : ' ');
	}
	std::reverse(arr.begin(), arr.end());
	for (size_t sorted = 0; sorted < arr.size(); ++sorted) {
		size_t i_max = std::max_element(arr.begin() + sorted, arr.end()) - arr.begin();
		if (i_max == sorted) {
			continue;
		}
		if (i_max + 1 != arr.size()) {
			flip(arr, i_max);
		}
		flip(arr, sorted);
	}
	std::cout << "0\n";
}

int mainLoop() {
	std::string line;
	while (std::getline(std::cin, line)) {
		solve(parseLine(line));
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