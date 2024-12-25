#include <memory.h>
#include <stddef.h>
#include <stdio.h>

#define N 100000

char s[N], t[N];
size_t cnt[2][256];

void count_chars(const char *s, const char *t) {
	while (*s) {
		++cnt[0][*(s++)];
	}
	while (*t) {
		++cnt[1][*(t++)];
	}
}

int main(void) {
	gets(s);
	gets(t);
	count_chars(s, t);
	printf("Those strings are ");
	if (memcmp(cnt[0], cnt[1], 256 * sizeof(size_t))) {
		printf("not ");
	}
	puts("anagrams.");
	return 0;
}