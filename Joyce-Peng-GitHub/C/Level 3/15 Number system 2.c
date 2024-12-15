#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

size_t itobase(char *buffer, size_t maxlen, uint64_t x, uint32_t base) {
	static const char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	if (maxlen <= 0 || !buffer) {
		return 0;
	}
	if (x) {
		size_t len = 0;
		if (x >= base) {
			len = itobase(buffer, maxlen - 1, x / base, base);
		}
		if (len != maxlen) {
			buffer[len] = digits[x % base];
			buffer[len + 1] = '\0';
			return (len + 1);
		} else {
			return len;
		}
	} else {
		buffer[0] = '0';
		buffer[1] = '\0';
		return 1;
	}
}
int64_t btoi(const char *num, uint32_t base) {
	static const char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	bool neg = false;
	int64_t res = 0;
	uint8_t digit;
	if (*num == '-') {
		neg = true;
		++num;
	} else if (*num == '+') {
		++num;
	}
	for (const char *p = num; isalnum(*p); ++p) {
		digit = strchr(digits, toupper(*p)) - digits;
		if (digit < base) {
			res = res * base + digit;
		} else {
			return 0;
		}
	}
	return (neg ? -res : res);
}

int main(void) {
	static const char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char s[33], t[33];
	uint8_t m = 2, n = 2;
	scanf("%s%s", s, t);
	for (char *p = s; *p; ++p) {
		if (isalnum(*p)) {
			uint8_t digit = strchr(digits, toupper(*p)) - digits;
			if (digit >= m) {
				m = digit + 1;
			}
		}
	}
	for (char *p = t; *p; ++p) {
		if (isalnum(*p)) {
			uint8_t digit = strchr(digits, toupper(*p)) - digits;
			if (digit >= n) {
				n = digit + 1;
			}
		}
	}
	for (uint32_t i = m, j; i <= 36; ++i) {
		for (j = n; j <= 36; ++j) {
			if (btoi(s, i) == btoi(t, j)) {
				printf("%s (base %" PRIu32 ") = %s (base %" PRIu32 ")\n", s, i, t, j);
				return 0;
			}
		}
	}
	printf("%s is not equal to %s in any base 2..36\n", s, t);
	return 0;
}