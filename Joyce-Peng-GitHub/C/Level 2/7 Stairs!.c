#include <stdint.h>
#include <stdio.h>

size_t dfs(size_t stair) {
#define N 100000
	static size_t mem[N] = {1, 1};
	return (mem[stair] ?: (mem[stair] = dfs(stair - 1) + dfs(stair - 2)));
}

int main(void) {
	size_t n;
	scanf("%zu", &n);
	printf("There %s %zu %s of climbing the stairs!\n",
		   ((dfs(n) == 1) ? "is" : "are"),
		   dfs(n),
		   ((dfs(n) == 1) ? "way" : "ways"));
	return 0;
}