#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int main(void) {
	char s[10];
	fgets(s, 9, stdin);
	size_t n = strlen(s);
	while (n && (s[n - 1] == '\n' || s[n - 1] == '\r')) {
		--n;
	}
	if (n != 5) {
		puts("invalid input");
		return 0;
	}
	for (size_t i = 0; i != 5; ++i) {
		if (!isdigit(s[i])) {
			puts("invalid input");
			return 0;
		}
	}
	size_t max = 1;
	bool contains_4 = false;
	for (size_t i = 0, j; i != 5; ++i) {
		if (s[i] == '4') {
			contains_4 = true;
		}
		for (j = i + 1; j != 5 && s[j] == s[j - 1]; ++j)
			;
		if (j - i > max) {
			max = j - i;
		}
	}
	switch (max) {
	case 5:
		puts("most lucky");
		break;
	case 4:
		puts("very lucky");
		break;
	case 3:
		puts("lucky");
		break;
	default:
		puts(contains_4 ? "unlucky" : "just fine");
		break;
	}
	return 0;
}