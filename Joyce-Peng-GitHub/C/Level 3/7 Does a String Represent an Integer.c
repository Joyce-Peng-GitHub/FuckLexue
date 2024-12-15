#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int main(void) {
	int ch = getchar();
	while (isblank(ch)) {
		ch = getchar();
	} // skip leading blanks
	if (!(isdigit(ch) || ((ch == '-' || ch == '+') && isdigit(ch = getchar())))) {
		puts("That string does not represent an integer.");
		return 0;
	}
	while (isdigit(ch)) {
		ch = getchar();
	}
	while (isblank(ch) || ch == '\n' || ch == '\r') {
		ch = getchar();
	} // skip trailing blanks
	if (~ch && !isdigit(ch)) {
		puts("That string does not represent an integer.");
		return 0;
	}
	puts("That string represents an integer.");
	return 0;
}