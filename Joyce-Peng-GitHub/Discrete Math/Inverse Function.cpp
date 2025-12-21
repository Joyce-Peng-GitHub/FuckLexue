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

/**
 * 1. f1(x)=x is equivalent to x=f1(x), i.e. f1^{-1}(x)=x=f1(x).
 * 2. f2(x)=1/x (x,f2(x)!=0) is equivalent to x=1/f2(x) (x,f2(x)!=0),
 * 	i.e. f2^{-1}=f2.
 * 3. f3(x)=1-x is equivalent to x=1-f3(x), i.e. f3^{-1}=f3.
 * 4. f4(x)=1/(1-x) (x!=1, f4(x)!=0). The equation is equivalent to 1-x=1/f4(x),
 * 	i.e. x=1-1/f4(x)=f5(f4(x)) (f4(x)!=0). Thus f4^{-1}=f5.
 * 5. The deduction above also indicates that f5^{-1}=f4.
 * 6. f6(x)=x/(x-1) (x!=1, f6(x)!=0). The equation is equivalent to
 * 	x=f6(x)/(f6(x)-1)=f6(f6(x)), i.e. f6^{-1}=f6.
 */
inline void solve() {
	std::cin.get();
	char ch = std::cin.get();

	std::cout << 'f';
	if (ch == '4' || ch == '5') {
		std::cout << SC<char>(ch ^ 1);
	} else {
		std::cout << ch;
	}
	std::cout << std::endl;
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