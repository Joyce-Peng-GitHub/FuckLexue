#include <array>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

class TruthTableGenerator {
public:
	static constexpr size_t ALPHABET = 26;
	static constexpr char BASE_CHR = 'a';
	static constexpr std::array<char, 5> OPERS{{'!', '&', '|', '-', '+'}};
	static constexpr char DISJUNCTIVE[] = " ∨ ", CONJUNCTIVE[] = " ∧ ";

	static constexpr bool isOper(char ch) noexcept {
		return (ch == '!' || ch == '&' || ch == '|' || ch == '-' || ch == '+');
	}
	static int precedenceOf(char oper) noexcept {
		switch (oper) {
		case '!':
			return 4;
		case '&':
			return 3;
		case '|':
			return 2;
		case '-':
			return 1;
		case '+':
			return 0;
		default:
			return -1;
		}
	}
	static std::vector<char> getVarsFrom(const std::string &formula) {
		std::array<bool, ALPHABET> has_char{};
		for (char ch : formula) {
			if (std::islower(ch)) has_char[ch - BASE_CHR] = true;
		}
		std::vector<char> vars;
		vars.reserve(ALPHABET);
		for (unsigned i = 0; i < ALPHABET; ++i) {
			if (has_char[i]) vars.push_back(BASE_CHR + i);
		}
		vars.shrink_to_fit();
		return vars;
	}
	static std::string convertToPostfixFrom(const std::string &infix) {
		std::vector<char> oper_stk;
		oper_stk.reserve(infix.size());
		std::string postfix;
		postfix.reserve(infix.size());

		for (char ch : infix) {
			if (std::islower(ch)) {
				postfix.push_back(ch);
			} else if (ch == '(') {
				oper_stk.push_back(ch);
			} else if (ch == ')') {
				while (oper_stk.size() && oper_stk.back() != '(') {
					postfix.push_back(oper_stk.back());
					oper_stk.pop_back();
				}
				oper_stk.pop_back(); // '('
			} else if (isOper(ch)) {
				auto cur_precedence = precedenceOf(ch);
				while (oper_stk.size() && precedenceOf(oper_stk.back()) >= cur_precedence) {
					postfix.push_back(oper_stk.back());
					oper_stk.pop_back();
				}
				oper_stk.push_back(ch);
			} else {
				constexpr char FMT[] = "TruthTableGenerator::convertToPostfixFrom: cannot identify char %c (%03d)";
				char msg[sizeof(FMT) - 2 - 4 + 1 + 3];
				std::sprintf(msg, FMT, ch, static_cast<int>(ch));
				throw std::invalid_argument(msg);
			}
		}
		while (oper_stk.size()) {
			postfix.push_back(oper_stk.back());
			oper_stk.pop_back();
		}

		postfix.shrink_to_fit();
		return postfix;
	}

	TruthTableGenerator(const std::string &formula)
		: m_formula(convertToPostfixFrom(formula)), m_vars(getVarsFrom(formula)) {
		m_genTruthTable();
		m_genTerms();
	}

	bool eval(const std::array<bool, ALPHABET> &assignments) const {
		std::vector<bool> stk;
		stk.reserve(m_formula.size());

		for (char ch : m_formula) {
			if (std::islower(ch)) {
				stk.push_back(assignments[ch - BASE_CHR]);
			} else if (isOper(ch)) {
				if (ch == '!') {
					stk.back().flip();
				} else {
					bool rhs = stk.back();
					stk.pop_back();
					bool lhs = stk.back();
					stk.pop_back();

					switch (ch) {
					case '&':
						stk.push_back(lhs & rhs);
						break;
					case '|':
						stk.push_back(lhs | rhs);
						break;
					case '-':
						stk.push_back(!lhs || rhs); // implies: A -> B == !A | B
						break;
					case '+':
						stk.push_back(lhs == rhs); // equiv : A <-> B == (A == B)
						break;
					default:
						assert(0); // this should not happen
					}
				}
			} else {
				assert(0); // this should not happen
			}
		}

		return stk.back();
	}

	std::vector<bool> truthTable() const { return m_truth_table; }
	std::vector<uint32_t> minTerms() const { return m_min_terms; }
	std::vector<uint32_t> maxTerms() const { return m_max_terms; }

	/**
	 * @brief Get the formatted principal disjunctive normal form string.
	 */
	std::string pdnf() const {
		if (m_min_terms.empty()) return "0";
		std::string res;
		res += 'm';
		res += std::to_string(m_min_terms[0]);
		for (size_t i = 1; i < m_min_terms.size(); ++i) {
			res += DISJUNCTIVE;
			res += 'm';
			res += std::to_string(m_min_terms[i]);
		}
		res.shrink_to_fit();
		return res;
	}
	/**
	 * @brief Get the formatted principal conjunctive normal form string.
	 */
	std::string pcnf() const {
		if (m_max_terms.empty()) return "1";
		std::string res;
		res += 'M';
		res += std::to_string(m_max_terms[0]);
		for (size_t i = 1; i < m_max_terms.size(); ++i) {
			res += CONJUNCTIVE;
			res += 'M';
			res += std::to_string(m_max_terms[i]);
		}
		res.shrink_to_fit();
		return res;
	}

protected:
	std::string m_formula; // postfix formula
	std::vector<char> m_vars;
	std::vector<bool> m_truth_table; // results of the truth table
	std::vector<uint32_t> m_min_terms, m_max_terms;

	void m_genTruthTable() {
		uint32_t case_num = (uint32_t(1) << m_vars.size());
		m_truth_table.resize(case_num);
		for (uint32_t i = 0; i < case_num; ++i) {
			std::array<bool, ALPHABET> assignments;
			for (size_t j = 0; j < m_vars.size(); ++j) {
				assignments[m_vars[j] - BASE_CHR] = ((i >> (m_vars.size() - 1 - j)) & 1);
			}
			m_truth_table[i] = eval(assignments);
		}
	}

	void m_genTerms() {
		m_min_terms.reserve(m_truth_table.size());
		m_max_terms.reserve(m_truth_table.size());

		for (uint32_t i = 0; i < m_truth_table.size(); ++i) {
			(m_truth_table[i] ? m_min_terms : m_max_terms).push_back(i);
		}

		m_min_terms.shrink_to_fit();
		m_max_terms.shrink_to_fit();
	}

private:
};
constexpr char TruthTableGenerator::DISJUNCTIVE[];
constexpr char TruthTableGenerator::CONJUNCTIVE[];

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

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr), std::cout.tie(nullptr);
	redirectIO();

	std::string formula;
	std::getline(std::cin, formula);
	TruthTableGenerator ttg(formula);
	std::cout << ttg.pdnf() << " ; " << ttg.pcnf() << std::endl;

	return 0;
}