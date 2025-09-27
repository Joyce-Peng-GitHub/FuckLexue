#ifndef _VEC_H
#define _VEC_H

#include <assert.h>
#include <memory.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct {
	void *data;
	size_t unit, sz, cap;
} Vec;

void vecConstruct(Vec *vec, size_t unit, size_t sz) {
	vec->data = malloc(unit * sz);
	assert(vec->data);
	vec->unit = unit;
	vec->sz = sz;
	vec->cap = sz;
}

void vecDestruct(Vec *vec) {
	free(vec->data);
	vec->data = NULL;
	vec->unit = vec->sz = vec->cap = 0;
}

void vecReserve(Vec *vec, size_t new_cap) {
	if (new_cap > vec->cap) {
		vec->data = realloc(vec->data, vec->unit * new_cap);
		assert(vec->data);
		vec->cap = new_cap;
	}
}

void vecResize(Vec *vec, size_t new_sz) {
	vecReserve(vec, new_sz);
	vec->sz = new_sz;
}

void vecShrink(Vec *vec) {
	vec->data = realloc(vec->data, vec->unit * vec->sz);
	assert(vec->data);
	vec->cap = vec->sz;
}

void *vecAt(Vec *vec, size_t n) {
	assert(n < vec->sz);
	return ((char *)vec->data + n * vec->unit);
}

const void *vecAtConst(const Vec *vec, size_t n) {
	assert(n < vec->sz);
	return ((const char *)vec->data + n * vec->unit);
}

void vecPushBack(Vec *vec, const void *elem) {
	if (vec->sz == vec->cap) {
		vecReserve(vec, vec->cap ? (vec->cap << 1) : 1);
	}
	memcpy((char *)vec->data + vec->unit * vec->sz, elem, vec->unit);
	++vec->sz;
}

void vecPopBack(Vec *vec) {
	assert(vec->sz);
	--vec->sz;
}

void vecClear(Vec *vec) {
	vec->sz = 0;
}

void vecInsert(Vec *vec, size_t pos, const void *elem, size_t cnt) {
	assert(pos <= vec->sz);
	if (vec->sz + cnt > vec->cap) {
		vecReserve(vec, vec->sz + cnt);
	}
	memmove((char *)vec->data + vec->unit * (pos + cnt),
			(char *)vec->data + vec->unit * pos,
			vec->unit * (vec->sz - pos));
	memcpy((char *)vec->data + vec->unit * pos, elem, vec->unit * cnt);
	vec->sz += cnt;
}

void vecErase(Vec *vec, size_t pos, size_t cnt) {
	assert(pos + cnt <= vec->sz);
	memmove((char *)vec->data + vec->unit * pos,
			(char *)vec->data + vec->unit * (pos + cnt),
			vec->unit * (vec->sz - pos - cnt));
	vec->sz -= cnt;
}

#endif