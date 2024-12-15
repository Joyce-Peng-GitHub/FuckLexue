#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void *p, const void *q) {
	return (*(const char *)q - *(const char *)p);
}

int main(void) {
#define N 1000000
	char num[N];
	fgets(num, sizeof(num), stdin);
	size_t n = strlen(num);
	while (n && (num[n - 1] == '\n' || num[n - 1] == '\r')) {
		--n;
	}
	num[n] = '\0';
	qsort(num, n, sizeof(char), cmp);
	puts(num);
	return 0;
}