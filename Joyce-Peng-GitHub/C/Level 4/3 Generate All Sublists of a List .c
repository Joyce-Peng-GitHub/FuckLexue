#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	size_t size, capacity;
	int64_t *data;
} vector_int64;

void vector_int64_construct_void(vector_int64 *this) {
	this->size = 0;
	this->capacity = 0;
	this->data = NULL;
}
void vector_int64_push_back(vector_int64 *this, int64_t val) {
	if (this->size == this->capacity) {
		if (this->capacity) {
			this->data = realloc(this->data, (this->capacity <<= 1) * sizeof(int64_t));
		} else {
			this->data = calloc(this->capacity = 1, sizeof(int64_t));
		}
	}
	this->data[this->size++] = val;
}
void vector_int64_destruct(vector_int64 *this) {
	free(this->data);
	this->size = 0;
	this->capacity = 0;
	this->data = NULL;
}

int main(void) {
	int64_t val;
	vector_int64 arr;
	vector_int64_construct_void(&arr);
	while (~scanf("%" SCNd64, &val)) {
		vector_int64_push_back(&arr, val);
	}
	putchar('\n');
	for (size_t i = 1, j, k; i <= arr.size; ++i) {
		for (j = 0; j + i <= arr.size; ++j) {
			for (k = j; k != j + i; ++k) {
				printf("%" PRId64 " ", arr.data[k]);
			}
			putchar('\n');
		}
	}
	vector_int64_destruct(&arr);
	return 0;
}