#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void) {
#define N 50
	char input[(N + 1) * 2];
	gets(input);
	long double ldb, lde;
	char c;
	sscanf(input, "%Lf %c%Lf", &ldb, &c, &lde);
	if (lde <= 18) {
		printf("%.8Lf\n", ldb * pow(10, lde));
	} else {
		char sb[N + 1];
		sscanf(input, "%s", sb);
		if (sb[1] == '.') {
			strcpy(sb + 1, sb + 2);
		}
		size_t len = strlen(sb);
		size_t i = 0;
		for (; i != len && i <= lde; ++i) {
			putchar(sb[i]);
		}
		if (i <= lde) {
			for (; i <= lde; ++i) {
				putchar('0');
			}
			putchar('.');
			for (size_t cnt = 0; cnt != 8; ++cnt) {
				putchar('0');
			}
		} else {
			putchar('.');
			size_t cnt = 0;
			for (; i != len && cnt != 8; ++i) {
				putchar(sb[i]);
				++cnt;
			}
			for (; cnt != 8; ++cnt) {
				putchar('0');
			}
		}
		putchar('\n');
	}
	return 0;
}