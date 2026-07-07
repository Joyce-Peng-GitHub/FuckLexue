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

struct Rational {
	int num, den;

	Rational(int num = 0, int den = 1) : num(num), den(den) { m_normalize(); }

	Rational operator-() const { return Rational(-num, den); }

	Rational operator+(const Rational &other) const {
		Rational res(num * other.den + other.num * den, den * other.den);
		res.m_normalize();
		return res;
	}
	Rational operator-(const Rational &other) const { return (*this + (-other)); }
	Rational operator*(const Rational &other) const {
		Rational res(num * other.num, den * other.den);
		res.m_normalize();
		return res;
	}
	Rational operator/(const Rational &other) const {
		Rational res(num * other.den, den * other.num);
		res.m_normalize();
		return res;
	}

	Rational &operator+=(const Rational &other) { return (*this = *this + other); }
	Rational &operator-=(const Rational &other) { return (*this = *this - other); }
	Rational &operator*=(const Rational &other) { return (*this = *this * other); }
	Rational &operator/=(const Rational &other) { return (*this = *this / other); }

	bool operator==(const Rational &other) const { return (num == other.num && den == other.den); }

protected:
	void m_normalize() {
		if (!den) {
			if (num < 0) {
				num = -1; // -inf
			} else if (num > 0) {
				num = 1; // inf
			}
			return;
		} // +-inf or nan

		if (!num) {
			den = 1;
			return;
		} // 0

		auto gcd = std::__gcd(num, den);
		num /= gcd;
		den /= gcd;

		if (den < 0) {
			num = -num;
			den = -den;
		}
	}
};

constexpr unsigned N = 4;
constexpr int TARGET = 24;

inline void preprocess() {}

bool dfs(const std::vector<Rational> &nums) {
	if (nums.size() == 1) {
		return (nums[0] == TARGET);
	}

	for (size_t i = 0; i < nums.size(); ++i) {
		for (size_t j = 0; j < nums.size(); ++j) {
			if (j == i) continue;
			std::array<Rational, 4> vals{nums[i] + nums[j],
										 nums[i] - nums[j],
										 nums[i] * nums[j],
										 nums[i] / nums[j]};
			std::vector<Rational> nxts;
			nxts.reserve(nums.size() - 1);
			for (size_t k = 0; k < nums.size(); ++k) {
				if (k == i || k == j) continue;
				nxts.push_back(nums[k]);
			}
			for (const auto &val : vals) {
				if (val.den == 0) continue;
				nxts.push_back(val);
				if (dfs(nxts)) return true;
				nxts.pop_back();
			}
		}
	}

	return false;
}

inline bool solve() {
	std::vector<Rational> arr(N);
	for (auto &e : arr) {
		int val;
		if (!(std::cin >> val)) {
			return false;
		}
		e = val;
	}
	if (dfs(arr)) {
		std::cout << "yes\n";
	} else {
		std::cout << "no\n";
	}
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