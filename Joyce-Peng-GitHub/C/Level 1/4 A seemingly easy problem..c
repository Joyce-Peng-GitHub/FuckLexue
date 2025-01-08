#include <stdint.h>
#include <stdio.h>

int main(void) {
	int64_t m, n, s;
	while (1) {
		scanf("%lld%lld", &m, &n);
		if (!m && !n) {
			break;
		}
		s = 0;
		for (; m <= n; ++m) {
			s += m;
		}
		printf("%lld\n", s);
	}
	return 0;
}