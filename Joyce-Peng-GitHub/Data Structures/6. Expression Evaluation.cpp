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

class DividedByZero : public std::invalid_argument {
public:
	DividedByZero() : std::invalid_argument("Divide 0.") {}
};

const std::array<char, 6> OPERATORS = {'+', '-', '*', '/', '%', '^'};

inline void preprocess() {}

inline int64_t qPow(int64_t base, uint64_t exp) {
	int64_t res = 1;
	while (exp) {
		if (exp & 1) res *= base;
		base *= base;
		exp >>= 1;
	}
	return res;
}

inline unsigned priorityOf(char ch) noexcept {
	switch (ch) {
	case '^':
		return 3;
	case '*':
	case '/':
	case '%':
		return 2;
	case '+':
	case '-':
		return 1;
	default:
		return 0;
	}
}

inline int64_t parse(const std::string &s) {
	if (s.empty()) return 0;
	std::stack<int64_t> operand_stk;
	std::stack<char> operator_stk;
	auto calc = [&]() {
		if (operand_stk.size() < 2) throw std::invalid_argument("Insufficient operands");
		int64_t rhs = operand_stk.top();
		operand_stk.pop();
		int64_t lhs = operand_stk.top();
		operand_stk.pop();
		char op = operator_stk.top();
		operator_stk.pop();
		if (op == '+') {
			lhs += rhs;
		} else if (op == '-') {
			lhs -= rhs;
		} else if (op == '*') {
			lhs *= rhs;
		} else if (op == '/') {
			if (!rhs) throw DividedByZero();
			lhs /= rhs;
		} else if (op == '%') {
			if (!rhs) throw DividedByZero();
			lhs %= rhs;
		} else if (op == '^') {
			if (rhs < 0) {
				throw std::invalid_argument("Negative exponent");
			}
			lhs = qPow(lhs, rhs);
		} else {
			throw std::invalid_argument(std::string("Unknown operator ") + op);
		}
		operand_stk.emplace(lhs);
	};
	auto pushOperator = [&](char op) {
		if (op != '^') {
			while (operator_stk.size() && priorityOf(operator_stk.top()) >= priorityOf(op)) {
				calc();
			}
		}
		operator_stk.emplace(op);
	};
	char last_char = '\0';
	for (size_t i = 0; i < s.size(); ++i) {
		if (std::isblank(s[i])) continue;
		bool is_unary_op = ((s[i] == '-' || s[i] == '+') &&
							(!last_char || last_char == '(' ||
							 std::find(OPERATORS.begin(), OPERATORS.end(), last_char) != OPERATORS.end()));
		if (std::isdigit(s[i]) || is_unary_op) {
			bool is_neg = false;
			size_t j = i;
			int64_t operand = 0;
			if (is_unary_op) {
				if (s[j++] == '-') is_neg = true;
				while (j < s.size() && std::isblank(s[j])) ++j;
			}
			if (j >= s.size() || !std::isdigit(s[j])) {
				throw std::invalid_argument("A sign not followed by a number");
			}
			for (; j < s.size() && std::isdigit(s[j]); ++j) {
				operand = (operand << 1) + (operand << 3) + (s[j] ^ '0');
			}
			operand_stk.emplace(is_neg ? -operand : operand);
			i = j - 1;
			last_char = s[i];
			continue;
		}
		if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '%' || s[i] == '^') {
			pushOperator(s[i]);
		} else if (s[i] == '(') {
			if (std::isdigit(last_char)) {
				throw std::invalid_argument("Missing operator before a parenthesis");
			}
			operator_stk.emplace(s[i]);
		} else if (s[i] == ')') {
			while (operator_stk.size() && operator_stk.top() != '(') {
				calc();
			}
			if (operator_stk.empty()) {
				throw std::invalid_argument("Mismatched parentheses");
			}
			operator_stk.pop();
		} else {
			throw std::invalid_argument(std::string("Unknown character ") + s[i]);
		}
		last_char = s[i];
	}
	while (operator_stk.size()) {
		if (operator_stk.top() == '(') {
			throw std::invalid_argument("Mismatched parentheses");
		}
		calc();
	}
	if (operand_stk.size() != 1) {
		throw std::invalid_argument("Invalid expression");
	}
	return operand_stk.top();
}

inline void solve() {
	std::string line;
	std::getline(std::cin, line);
	try {
		std::cout << parse(line) << '\n';
	} catch (const DividedByZero &e) {
		std::cout << e.what() << '\n';
	} catch (const std::invalid_argument &e) {
		std::cout << "error.\n";
	}
}

int mainLoop() {
	uint64_t cnt_testcases;
	std::cin >> cnt_testcases;
	std::cin.get();
	while (cnt_testcases--) solve();
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