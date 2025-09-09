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

struct Task {
	uint32_t beg, end;
};

inline void preprocess() {}

inline void solve() {
	size_t n;
	std::cin >> n;
	std::vector<Task> tasks(n);
	for (auto &task : tasks) {
		std::cin >> task.beg >> task.end;
	}
	std::sort(tasks.begin(), tasks.end(),
			  [](const Task &lhs, const Task &rhs) {
				  return (lhs.end < rhs.end);
			  });
	size_t cnt = 0;
	uint32_t cur = 0;
	for (auto &task : tasks) {
		if (task.beg >= cur) {
			++cnt;
			cur = task.end;
		}
	}
	std::cout << cnt << std::endl;
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