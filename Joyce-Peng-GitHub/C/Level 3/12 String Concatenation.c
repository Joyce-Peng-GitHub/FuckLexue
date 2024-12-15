#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

int main(void) {
#define N 100000
	char s[N];
	scanf("%s", s);
	bool bucket[256] = {0};
	for (char *p = s; *p; p++) {
		if (!isalnum(*p)) {
			puts("Wrong Input!");
			return 0;
		}
		bucket[*p] = true;
	}
	scanf("%s", s);
	for (char *p = s; *p; p++) {
		if (!isalnum(*p)) {
			puts("Wrong Input!");
			return 0;
		}
		bucket[*p] = true;
	}
	for (char c = '0'; c <= '9'; c++) {
		if (bucket[c]) {
			putchar(c);
		}
	}
	for (char c = 'A'; c <= 'Z'; c++) {
		if (bucket[c]) {
			putchar(c);
		}
	}
	for (char c = 'a'; c <= 'z'; c++) {
		if (bucket[c]) {
			putchar(c);
		}
	}
	putchar('\n');
	return 0;
}