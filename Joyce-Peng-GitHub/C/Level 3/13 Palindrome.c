#include <stdio.h>
#include <string.h>

int main(void) {
#define N 100000
	char s[N + 1];
	fgets(s, N, stdin);
	size_t n = strlen(s);
	while (n && (s[n - 1] == '\n' || s[n - 1] == '\r')) {
		--n;
	}
	for (size_t i = 0; ((i << 1) ^ 1) < n; ++i) {
		if (s[i] != s[n - i - 1]) {
			puts("No");
			return 0;
		}
	}
	puts("Yes");
	return 0;
}