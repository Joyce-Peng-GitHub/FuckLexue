#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

int main(void) {
	// freopen("A.in", "r", stdin);
#define ALPHABET 26
	int cnt_words = 0, cnt_chars[ALPHABET] = {0};
	bool is_word = false, appears[ALPHABET] = {false};
	for (int ch = getchar(); ~ch; ch = getchar()) {
		if (isalpha(ch)) {
			appears[tolower(ch) - 'a'] = true;
			is_word = true;
		} else if (ch != '\'' && is_word) { // 牛逼爆了这个引号
			++cnt_words;
			for (int i = 0; i != ALPHABET; ++i) {
				if (appears[i]) {
					++cnt_chars[i];
				}
				appears[i] = false;
			}
			is_word = false;
		}
	}
	if (is_word) {
		++cnt_words;
		for (int i = 0; i != ALPHABET; ++i) {
			if (appears[i]) {
				++cnt_chars[i];
			}
		}
	}
	int i_fewest = 0;
	for (int i = 0; i != ALPHABET; ++i) {
		if (cnt_chars[i] < cnt_chars[i_fewest]) {
			i_fewest = i;
		}
		printf("%c occurs in %.2Lf percent of words\n",
			   ('A' + i), cnt_chars[i] * 100 / (long double)cnt_words);
	}
	printf("\nThe letter that is easiest to avoid is '%c'\n", ('A' + i_fewest));
	return 0;
}