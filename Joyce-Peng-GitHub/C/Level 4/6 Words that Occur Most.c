#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define N 1000
#define M 100

size_t n;
char words[N][M + 1];
size_t cnt[N];

void push(const char *s) {
	for (size_t i = 0; i != n; ++i) {
		if (!strcmp(words[i], s)) {
			++cnt[i];
			return;
		}
	}
	strcpy(words[n], s);
	cnt[n++] = 1;
}

int main(void) {
	// freopen("6.in", "r", stdin);
	char cur[M + 1];
	size_t len = 0;
	for (int ch = getchar(); ~ch; ch = getchar()) {
		if (isalnum(ch)) {
			cur[len++] = tolower(ch);
		} else if (len) {
			cur[len] = '\0';
			push(cur);
			len = 0;
		}
	}
	size_t cnt_most = 0;
	for (size_t i = 0; i != n; ++i) {
		if (cnt[i] > cnt_most) {
			cnt_most = cnt[i];
		}
	}
	for (size_t i = 0; i != n; ++i) {
		if (cnt[i] == cnt_most) {
			puts(words[i]);
		}
	}
	return 0;
}