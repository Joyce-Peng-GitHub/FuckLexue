#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

uint64_t roman_char_to_arabic(char ch) {
	switch (ch) {
	case 'M':
		return 1000;
	case 'D':
		return 500;
	case 'C':
		return 100;
	case 'L':
		return 50;
	case 'X':
		return 10;
	case 'V':
		return 5;
	case 'I':
		return 1;
	default:
		return -1;
	}
}
uint64_t roman_to_arabiic(const char *s, size_t len) {
	if (len == 0) {
		return 0;
	}
	if (len == 1) {
		return roman_char_to_arabic(*s);
	}
	size_t i = len - 1, j = len - 1;
	// (j, i]
	uint64_t res = 0;
	for (; ~i; i = j) {
		for (--j;
			 ~j &&
			 roman_char_to_arabic(s[j]) < roman_char_to_arabic(s[i]);
			 --j)
			;
		res += roman_to_arabiic(s + i, 1) -
			   roman_to_arabiic(s + j + 1, i - j - 1);
	}
	return res;
}

int main(void) {
#define N 100
	char s[N + 1];
	fgets(s, N, stdin);
	size_t n = strlen(s);
	while (n && (s[n - 1] == '\n' || s[n - 1] == '\r')) {
		--n;
	}
	s[n] = '\0';
	printf("%" PRIu64 "\n", roman_to_arabiic(s, n));
	return 0;
}