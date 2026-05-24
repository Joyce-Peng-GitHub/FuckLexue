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

struct Point {
	double x, y;
};

constexpr size_t N = 1e5;
size_t n;
std::array<Point, N> points;
double ans; // square of the minimum distance between two points

inline void preprocess() {}

inline double square(double x) { return x * x; }

void divideAndConquer(size_t beg, size_t end) {
	if (beg == end || beg + 1 == end) return;
	assert(beg < end);

	size_t mid = beg + ((end - beg) >> 1);
	auto mid_x = points[mid].x;
	divideAndConquer(beg, mid);
	divideAndConquer(mid, end);

	std::inplace_merge(points.begin() + beg, points.begin() + mid, points.begin() + end,
					   [](const Point &lhs, const Point &rhs) { return (lhs.y < rhs.y); });

	std::vector<Point> cands;
	for (size_t i = beg; i < end; ++i) {
		if (square(points[i].x - mid_x) < ans) {
			cands.push_back(points[i]);
		}
	}
	for (size_t i = 0; i < cands.size(); ++i) {
		for (size_t j = i + 1;
			 j < cands.size() && square(cands[j].y - cands[i].y) < ans;
			 ++j) {
			auto dist = square(cands[j].x - cands[i].x) + square(cands[j].y - cands[i].y);
			if (dist < ans) ans = dist;
		}
	}
}

inline bool solve() {
	std::cin >> n;
	if (!n) return false;
	for (size_t i = 0; i < n; ++i) {
		std::cin >> points[i].x >> points[i].y;
	}
	std::sort(points.begin(), points.begin() + n,
			  [](const Point &lhs, const Point &rhs) { return (lhs.x < rhs.x); });
	ans = INFINITY;
	divideAndConquer(0, n);
	std::cout << std::fixed << std::setprecision(2) << (std::sqrt(ans) / 2) << '\n';
	return true;
}

inline int mainLoop() {
	while (solve());
	return 0;
}

int main() {
	redirectIo();
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	preprocess();
	return mainLoop();
}