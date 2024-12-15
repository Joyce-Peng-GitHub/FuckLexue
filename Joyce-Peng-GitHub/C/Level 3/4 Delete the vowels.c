#include <stddef.h>
#include <stdio.h>

int main(void) {
	size_t n;
	scanf("%zu", &n);
	getchar();
#define N 1000000
	char s[N];
	while (n--) {
		gets(s);
		for (char *p = s; *p != '\n' && *p != '\r' && *p; p++) {
			if (*p != 'A' && *p != 'E' && *p != 'I' && *p != 'O' && *p != 'U' &&
				*p != 'a' && *p != 'e' && *p != 'i' && *p != 'o' && *p != 'u') {
				putchar(*p);
			}
		}
		putchar('\n');
	}
	return 0;
}