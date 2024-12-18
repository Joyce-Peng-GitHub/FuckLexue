#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#define N 1000
#define M 1000
#define MINE '*'

size_t n, m;
char map[N][M];

void convert(void) {
	static const int8_t dx[] = {-1, 0, 1}, dy[] = {-1, 0, 1};
	for (size_t i = 0, j, k, l, x, y; i != n; ++i) {
		for (j = 0; j != m; ++j) {
			if (map[i][j] != MINE) {
				map[i][j] = '0';
				for (k = 0; k != 3; ++k) {
					for (l = 0; l != 3; ++l) {
						x = i + dx[k];
						y = j + dy[l];
						if (~x && ~y && x != n && y != m) {
							map[i][j] += (map[x][y] == MINE);
						}
					}
				}
			}
		}
	}
}

int main(void) {
	// freopen("2.in", "r", stdin);
	// freopen("2.out", "w", stdout);
	size_t cnt = 1;
	while (scanf("%zu%zu", &n, &m) && (n || m)) {
		if (cnt != 1) {
			putchar('\n');
		}
		printf("Field #%zu:\n", (cnt++));
		for (size_t i = 0; i != n; ++i) {
			scanf("%s", map[i]);
		}
		convert();
		for (size_t i = 0; i != n; ++i) {
			puts(map[i]);
		}
	}
	return 0;
}