#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	fputs("The lucky person is no:", stdout);
	size_t n, m;
	scanf("%zu%zu", &n, &m);
	size_t i = 0, cnt = 0, alive = n;
	bool *executed = calloc(n, sizeof(bool));
	while (true) {
		if (!executed[i] && (cnt++) == m) {
			if ((alive--) == 1) {
				printf("%zu\n", i + 1);
				break;
			}
			cnt = 0;
			executed[i] = true;
		}
		i = (i + 1) % n;
	}
	return 0;
}