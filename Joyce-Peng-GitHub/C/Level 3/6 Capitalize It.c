#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int main(void) {
#define N 100000
	char s[N + 2];
	fgets(s, sizeof(s), stdin);
	size_t n = strlen(s);
	while (n && (s[n - 1] == '\n' || s[n - 1] == '\r')) {
		--n;
	}
	if (!n) {
		putchar('\n');
		return 0;
	}
	s[n] = '\0';
	bool new_sentence = true;
	for (const char *p = s; *p; ++p) {
		if (*p == '.' || *p == '!' || *p == '?') {
			putchar(*p);
			new_sentence = true;
		} else if (isblank(*p)) {
			putchar(*p);
		} else {
			if (islower(*p)) {
				if (new_sentence) {
					putchar(toupper(*p));
				} else if (*p == 'i' && !isalnum(*(p - 1)) && !isalnum(*(p + 1))) {
					putchar('I');
				} else {
					putchar(*p);
				}
			} else {
				putchar(*p);
			}
			new_sentence = false;
		}
	}
	putchar('\n');
	return 0;
}