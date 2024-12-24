#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int comp(const void *p, const void *q) {
	return (*(const uint64_t *)p - *(const uint64_t *)q);
}

int main(void) {
#define N 100
#define M 100
	size_t n, m;
	uint64_t heads[N], warriors[M];
	scanf("%zu%zu", &n, &m);
	for (size_t i = 0; i != n; ++i) {
		scanf("%" SCNu64, heads + i);
	}
	for (size_t i = 0; i != m; ++i) {
		scanf("%" SCNu64, warriors + i);
	}
	qsort(heads, n, sizeof(uint64_t), comp);
	qsort(warriors, m, sizeof(uint64_t), comp);
	uint64_t cost = 0;
	size_t i = 0, j = 0;
	for (; i != n; ++i) {
		while (j != m && warriors[j] < heads[i]) {
			++j;
		}
		if (j == m) {
			puts("bit is doomed!");
			return 0;
		}
		cost += warriors[j++];
	}
	printf("%" PRIu64 "\n", cost);
	return 0;
}