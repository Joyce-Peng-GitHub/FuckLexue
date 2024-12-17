#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int comp(const void *p, const void *q) {
	return (*(const int64_t *)q - *(const int64_t *)p);
}

int main(void) {
#define N 100000
	size_t n;
	int64_t arr[N];
	scanf("%zu", &n);
	++n;
	for (size_t i = 0; i != n; ++i) {
		scanf("%" PRId64, arr + i);
	}
	qsort(arr, n, sizeof(int64_t), comp);
	printf("%" PRId64, *arr);
	for (size_t i = 1; i != n; ++i) {
		printf(" %" PRId64, arr[i]);
	}
	putchar('\n');
	return 0;
}