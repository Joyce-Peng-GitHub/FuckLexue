#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int main(void) {
#define N 1000000
	char pswd[N];
	fgets(pswd, sizeof(pswd), stdin);
	size_t n = strlen(pswd);
	while (n && (pswd[n - 1] == '\n' || pswd[n - 1] == '\r')) {
		--n;
	}
	if (n < 8) {
		puts("Bad password!");
		return 0;
	}
	bool d = false, l = false, u = false;
	for (size_t i = 0; i != n && (!d || !l || !u); ++i) {
		if (isdigit(pswd[i])) {
			d = true;
		} else if (islower(pswd[i])) {
			l = true;
		} else if (isupper(pswd[i])) {
			u = true;
		}
	}
	if (d && l && u) {
		puts("Good password!");
	} else {
		puts("Bad password!");
	}
	return 0;
}