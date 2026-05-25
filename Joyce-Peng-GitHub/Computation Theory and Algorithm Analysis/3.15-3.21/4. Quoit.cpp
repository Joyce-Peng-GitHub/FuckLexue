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

	bool operator==(const Point &other) const {
		return (this->x == other.x && this->y == other.y);
	}
};

constexpr size_t N = 1e5;
size_t n;
std::array<Point, N> points;
double ans; // square of the minimum distance between two points

inline void preprocess() {}

inline double square(double x) { return x * x; }

inline bool solve() {
	constexpr double EPS = 1e-6;

	std::cin >> n;
	if (!n) return false;
	for (size_t i = 0; i < n; ++i) {
		std::cin >> points[i].x >> points[i].y;
	}
	std::sort(points.begin(), points.begin() + n,
			  [](const Point &lhs, const Point &rhs) {
				  return (lhs.x < rhs.x);
			  });
	if (std::unique(points.begin(), points.begin() + n) != points.begin() + n) {
		std::cout << "0.00\n";
		return true;
	}

	double ans = INFINITY;
	std::set<std::pair<double, size_t>> st;
	for (size_t i = 0, j = 0; i < n; ++i) {
		for (; j < i && square(points[i].x - points[j].x) >= ans; ++j) {
			st.erase(std::make_pair(points[j].y, j));
		}
		for (auto iter = st.lower_bound(std::make_pair(points[i].y - std::sqrt(ans) - EPS, size_t(0)));
			 iter != st.end() && square(iter->first - points[i].y) <= ans + EPS;
			 ++iter) {
			auto dist = square(points[iter->second].x - points[i].x) +
						square(points[iter->second].y - points[i].y);
			if (dist < ans) ans = dist;
		}
		st.insert({points[i].y, i});
	}

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