#include <assert.h>
#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define N 500
int op; // 1 for plus, -1 for minus
bool neg[3];
size_t n[3];
uint8_t digits[3][N << 1];

void init(void);
void read(void);
void reverse(size_t index);
int comp(void);
void plus(void);  // a + b
void minus(void); // a - b
void sunim(void); // b - a
void write(void);

int main(void) {
	// freopen("10.in", "r", stdin);
	// freopen("10.out", "w", stdout);
	size_t q;
	scanf("%zu\n", &q);
	while (q--) {
		init();
		read();
		if (op > 0) {
			plus();
		} else if (op < 0) {
			minus();
		} else {
			assert(0);
		}
		write();
	}
	return 0;
}

void init(void) {
	neg[0] = 0;
	neg[1] = 0;
	neg[2] = 0;
	for (size_t i = 0, j; i != 3; ++i) {
		for (size_t j = 0; j != n[i]; ++j) {
			digits[i][j] = 0;
		}
	}
	n[0] = 0;
	n[1] = 0;
	n[2] = 0;
}
void read(void) {
	int ch = getchar();
	while (isblank(ch)) {
		ch = getchar();
	}
	if (ch == '-') {
		neg[0] = true;
		ch = getchar();
	} else if (ch == '+') {
		ch = getchar();
	}
	for (; isdigit(ch); ch = getchar()) {
		digits[0][n[0]++] = (ch ^ '0');
	}
	reverse(0);
	if (ch == '+') {
		op = 1;
	} else if (ch == '-') {
		op = -1;
	} else {
		assert(0);
	}
	for (ch = getchar(); isdigit(ch); ch = getchar()) {
		digits[1][n[1]++] = (ch ^ '0');
	}
	reverse(1);
}
void reverse(size_t index) {
	for (size_t i = 0; ((i << 1) ^ 1) < n[index]; ++i) {
		digits[index][i] ^= digits[index][n[index] - 1 - i];
		digits[index][n[index] - 1 - i] ^= digits[index][i];
		digits[index][i] ^= digits[index][n[index] - 1 - i];
	}
}
int comp(void) { // abs(a) <=> abs(b)
	if (n[0] != n[1]) {
		return (n[0] - n[1]);
	}
	for (size_t i = n[0] - 1; ~i; --i) {
		if (digits[0][i] != digits[1][i]) {
			return (digits[0][i] - digits[1][i]);
		}
	}
	return 0;
}
void plus(void) {
	if (neg[0] != neg[1]) {
		if (neg[0]) {		// a < 0 <= b
			neg[0] = false; // a = -a
			sunim();		// c = b - a
		} else {			// b < 0 <= a
			neg[1] = false; // b = -b
			minus();		// c = a - b
		}
	} else { // a * b >= 0
		neg[2] = neg[0];
		size_t i = 0;
		for (uint8_t carry = digits[0][0] + digits[1][0];
			 i < n[0] || i < n[1] || carry;
			 carry = carry / 10 + digits[0][i] + digits[1][i]) {
			digits[2][i] = carry % 10;
			++i;
		}
		n[2] = i;
	}
}
void minus(void) {
	if (neg[0] != neg[1]) {
		neg[1] = neg[0];	  // b = -b
		plus();				  // c = a + b
	} else if (comp() >= 0) { // abs(a) >= abs(b)
		/* c = sgn(a) * (abs(a) - abs(b)) */
		neg[2] = neg[0];
		size_t i = 0;
		for (uint8_t borrow = 0; i < n[0] || i < n[1]; ++i) {
			digits[2][i] = digits[0][i] - borrow - digits[1][i];
			if (borrow = (digits[0][i] < (digits[1][i] + borrow))) {
				digits[2][i] += 10;
			}
		}
		for (--i; ~i && !digits[2][i]; --i) // remove the redundant prefix 0s
			;
		n[2] = i + 1;
	} else { // abs(a) < abs(b)
		/* c = (-sgn(a)) * (abs(b) - abs(a)) */
		neg[2] = !neg[0];
		size_t i = 0;
		for (uint8_t borrow = 0; i < n[1] || i < n[0]; ++i) {
			digits[2][i] = digits[1][i] - borrow - digits[0][i];
			if (borrow = (digits[1][i] < (digits[0][i] + borrow))) {
				digits[2][i] += 10;
			}
		}
		for (--i; ~i && !digits[2][i]; --i) // remove the redundant prefix 0s
			;
		n[2] = i + 1;
	}
}
void sunim(void) {
	// This function would be called only by plus(),
	// so there must be neg[0] == neg[1]
	size_t i = 0;
	if (comp() <= 0) { // abs(a) <= abs(b)
		/* c = sgn(a) * (abs(b) - abs(a)) */
		neg[2] = neg[0];
		for (uint8_t borrow = 0; i < n[1] || i < n[0]; ++i) {
			digits[2][i] = digits[1][i] - borrow - digits[0][i];
			if (borrow = (digits[1][i] < (digits[0][i] + borrow))) {
				digits[2][i] += 10;
			}
		}
	} else { // abs(a) > abs(b)
		/* c = (-sgn(a)) * (abs(a) - abs(b)) */
		neg[2] = !neg[0];
		for (uint8_t borrow = 0; i < n[0] || i < n[1]; ++i) {
			digits[2][i] = digits[0][i] - borrow - digits[1][i];
			if (borrow = (digits[0][i] < (digits[1][i] + borrow))) {
				digits[2][i] += 10;
			}
		}
	}
	for (--i; ~i && !digits[2][i]; --i) // remove the redundant prefix 0s
		;
	n[2] = i + 1;
}
void write(void) {
	if (n[2]) {
		if (neg[2]) {
			putchar('-');
		}
		for (size_t i = n[2] - 1; ~i; --i) {
			putchar(digits[2][i] ^ '0');
		}
	} else {
		putchar('0');
	}
	putchar('\n');
}