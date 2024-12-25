#include <stdint.h>
#include <stdio.h>

int main(void) {
	const size_t N = 1024;
	char s[N];
	gets(s);
	printf("Hi,there,%s!\n", s);
	return 0;
}