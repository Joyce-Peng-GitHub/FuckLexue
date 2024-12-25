#include <stdint.h>
#include <stdio.h>

int main(void) {
	int64_t a, b;
	scanf("%lld,%lld", &a, &b);
	printf("%lld+%lld=%lld\n", a, b, a + b);
	return 0;
}