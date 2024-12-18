#include <ctype.h>
#include <memory.h>
#include <stddef.h>
#include <stdio.h>

#define N 100000

char s[N], t[N];
size_t cnt[2][26];

void count_chars(const char *s, const char *t) {
	for (; *s; ++s) {
		if (isalpha(*s)) {
			++cnt[0][tolower(*s) - 'a'];
		}
	}
	for (; *t; ++t) {
		if (isalpha(*t)) {
			++cnt[1][tolower(*t) - 'a'];
		}
	}
}

int main(void) {
	gets(s);
	gets(t);
	count_chars(s, t);
	printf("Those phrases are ");
	if (memcmp(cnt[0], cnt[1], 26 * sizeof(size_t))) {
		printf("not ");
	}
	puts("anagrams.");
	return 0;
}