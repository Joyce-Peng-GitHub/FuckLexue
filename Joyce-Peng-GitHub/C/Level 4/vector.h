#ifndef _VECTOR_H
#define _VECTOR_H

#include <memory.h>
#include <stddef.h>
#include <stdlib.h>

#define DECLARE_VECTOR(TYPE)                                                                          \
	typedef struct {                                                                                  \
		size_t size, capacity;                                                                        \
		TYPE *data;                                                                                   \
	} vector_##TYPE##_t;                                                                              \
                                                                                                      \
	void vector_##TYPE##_construct_void(vector_##TYPE##_t *this) {                                    \
		this->size = 0;                                                                               \
		this->capacity = 0;                                                                           \
		this->data = NULL;                                                                            \
	}                                                                                                 \
	void vector_##TYPE##_construct_size(vector_##TYPE##_t *this, size_t n) {                          \
		this->size = n;                                                                               \
		this->capacity = n;                                                                           \
		this->data = calloc(n, sizeof(TYPE));                                                         \
	}                                                                                                 \
	void vector_##TYPE##_construct_size_pinit(vector_##TYPE##_t *this, size_t n, const TYPE *pinit) { \
		this->size = n;                                                                               \
		this->capacity = n;                                                                           \
		this->data = malloc(n * sizeof(TYPE));                                                        \
		for (size_t i = 0; i != n; ++i) {                                                             \
			this->data[i] = *pinit;                                                                   \
		}                                                                                             \
	}                                                                                                 \
	void vector_##TYPE##_construct_copy(vector_##TYPE##_t *this, const vector_##TYPE##_t *source) {   \
		this->size = source->size;                                                                    \
		this->data = realloc(this->data, (this->capacity = this->size) * sizeof(vector_##TYPE##_t));  \
	}                                                                                                 \
	void vector_##TYPE##_reserve(vector_##TYPE##_t *this, size_t cap) {                               \
		if (cap > this->capacity) {                                                                   \
			this->data = realloc(this->data, (this->capacity = cap) * sizeof(TYPE));                  \
		}                                                                                             \
	}                                                                                                 \
	void vector_##TYPE##_resize(vector_##TYPE##_t *this, size_t n) {                                  \
		if (n <= this->capacity) {                                                                    \
			this->size = n;                                                                           \
		} else {                                                                                      \
			this->capacity = n;                                                                       \
			this->data = realloc(this->data, (this->size = n) * sizeof(TYPE));                        \
		}                                                                                             \
	}                                                                                                 \
	void vector_##TYPE##_resize_init(vector_##TYPE##_t *this, size_t n, const TYPE *pinit) {          \
		if (n <= this->capacity) {                                                                    \
			this->size = n;                                                                           \
		} else {                                                                                      \
			this->capacity = n;                                                                       \
			this->data = realloc(this->data, n * sizeof(TYPE));                                       \
			for (size_t i = this->size; i != n; ++i) {                                                \
				this->data[i] = *pinit;                                                               \
			}                                                                                         \
			this->size = n;                                                                           \
		}                                                                                             \
	}                                                                                                 \
	void vector_##TYPE##_shrink_to_fit(vector_##TYPE##_t *this) {                                     \
		if (this->capacity > this->size) {                                                            \
			this->capacity = this->size;                                                              \
			this->data = realloc(this->data, this->capacity * sizeof(TYPE));                          \
		}                                                                                             \
	}                                                                                                 \
	void vector_##TYPE##_push_back(vector_##TYPE##_t *this, const TYPE *pval) {                       \
		if (this->size == this->capacity) {                                                           \
			if (this->capacity) {                                                                     \
				this->data = realloc(this->data, (this->capacity <<= 1) * sizeof(TYPE));              \
				this->data[this->size++] = *pval;                                                     \
			} else {                                                                                  \
				this->capacity = 1;                                                                   \
				this->size = 1;                                                                       \
				this->data = malloc(sizeof(TYPE));                                                    \
				*(this->data) = *pval;                                                                \
			}                                                                                         \
		} else {                                                                                      \
			this->data[this->size++] = *pval;                                                         \
		}                                                                                             \
	}                                                                                                 \
	void vector_##TYPE##_pop_back(vector_##TYPE##_t *this) {                                          \
		--this->size;                                                                                 \
	}                                                                                                 \
	void vector_##TYPE##_destruct(vector_##TYPE##_t *this) {                                          \
		this->size = 0;                                                                               \
		this->capacity = 0;                                                                           \
		free(this->data);                                                                             \
		this->data = NULL;                                                                            \
	}

#endif