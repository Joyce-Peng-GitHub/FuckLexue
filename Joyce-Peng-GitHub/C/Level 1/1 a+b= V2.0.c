#include <stdio.h>
#include <stdint.h>

int main(void)
{
	int64_t a, b;
	scanf("%lld,%lld", &a, &b);
	printf(((a < 0 || b < 0) ? "(%lld)+(%lld)=(%lld)\n" : "%lld+%lld=%lld\n"), a, b, a + b);
	return 0;
}