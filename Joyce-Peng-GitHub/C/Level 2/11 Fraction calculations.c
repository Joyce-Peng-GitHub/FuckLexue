#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	bool nega;
	uint64_t numerator, denominator;
} rational_t;

uint64_t gcd(uint64_t a, uint64_t b) {
	uint64_t t = a;
	if (a < b) {
		a = b;
		b = t;
	}
	while (b) {
		t = b;
		b = a % b;
		a = t;
	}
	return a;
}
void swap_rational(rational_t *p, rational_t *q) {
	rational_t t = *q;
	*q = *p;
	*p = t;
}
bool rational_iszero(const rational_t *this) {
	return (!this->numerator);
}
bool rational_isinf(const rational_t *this) {
	return this->denominator;
}
rational_t *rational_reduce(rational_t *this) {
	if (this->numerator) {
		uint64_t d = gcd(this->numerator, this->denominator);
		this->numerator /= d;
		this->denominator /= d;
	} else {
		this->nega = false;
	}
	return this;
}
rational_t rational_reduced_form(rational_t r) {
	return *rational_reduce(&r);
}
rational_t *rational_toreciprocal(rational_t *this) {
	uint64_t t = this->numerator;
	this->numerator = this->denominator;
	this->denominator = t;
	return this;
}
rational_t rational_reciprocal_form(rational_t r) {
	return *rational_toreciprocal(&r);
}
rational_t __rational_plus(rational_t a, rational_t b);
rational_t rational_plus(rational_t a, rational_t b);
rational_t rational_minus(rational_t a, rational_t b);
rational_t __rational_minus(rational_t a, rational_t b);
rational_t rational_multiply(rational_t a, rational_t b);
rational_t rational_dividedby(rational_t a, rational_t b);

int main(void) {
	rational_t a = {false}, b = {false}, c;
	char oper;
	scanf("%llu/%llu %c %llu/%llu", &a.numerator, &a.denominator, &oper, &b.numerator, &b.denominator);
	switch (oper) {
	case '+':
		c = rational_plus(a, b);
		break;
	case '-':
		c = rational_minus(a, b);
		break;
	case '*':
		c = rational_multiply(a, b);
		break;
	case '/':
		c = rational_dividedby(a, b);
		break;
	default:
		exit(-1);
		break;
	}
	printf("%llu/%llu %c %llu/%llu = ", a.numerator, a.denominator, oper, b.numerator, b.denominator);
	if (c.nega) {
		putchar('-');
	}
	printf("%llu", c.numerator);
	if (c.denominator != 1 && !rational_iszero(&c)) {
		printf("/%llu", c.denominator);
	}
	putchar('\n');
	return 0;
}

rational_t __rational_plus(rational_t a, rational_t b) {
	uint64_t d = gcd(a.denominator, b.denominator), m = b.denominator / d;
	a.numerator = (a.numerator * m + b.numerator * (a.denominator / d));
	a.denominator *= m;
	return *rational_reduce(&a);
}
rational_t rational_plus(rational_t a, rational_t b) {
	if (a.nega != b.nega) {
		if (a.nega) {
			a.nega = false;
			return __rational_minus(b, a);
		} else {
			b.nega = false;
			return __rational_minus(a, b);
		}
	}
	return __rational_plus(a, b);
}
rational_t __rational_minus(rational_t a, rational_t b) {
	uint64_t d = gcd(a.denominator, b.denominator), m = b.denominator / d, n = a.denominator / d;
	if (a.numerator * m < b.numerator * n) {
		a.numerator = (b.numerator * n - a.numerator * m);
		a.nega = !a.nega;
	} else {
		a.numerator = (a.numerator * m - b.numerator * n);
	}
	a.denominator *= m;
	return *rational_reduce(&a);
}
rational_t rational_minus(rational_t a, rational_t b) {
	if (a.nega != b.nega) {
		b.nega = a.nega;
		return __rational_plus(a, b);
	}
	return __rational_minus(a, b);
}
rational_t rational_multiply(rational_t a, rational_t b) {
	a.nega ^= b.nega;
	a.numerator *= b.numerator;
	a.denominator *= b.denominator;
	return *rational_reduce(&a);
}
rational_t rational_dividedby(rational_t a, rational_t b) {
	return rational_multiply(a, rational_reciprocal_form(b));
}