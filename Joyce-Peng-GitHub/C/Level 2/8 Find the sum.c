#include <stdint.h>
#include <stdio.h>

long double dfs(size_t n) {
	return ((n == 1) ? 1 : (dfs(n - 1) + ((n & 1) ? -1 : 1) / (long double)n));
}

int main(void) {
	size_t n;
	scanf("%zu", &n);
	if (n == 1) {
		puts("1");
	} else {
		printf("%.6Lf\n", dfs(n));
	}
	return 0;
}