#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	size_t size, capacity;
	int64_t *data;
} vector_int64;

void vector_int64_construct_void(vector_int64 *tthis) {
	tthis->size = 0;
	tthis->capacity = 0;
	tthis->data = NULL;
}
void vector_int64_push_back(vector_int64 *tthis, int64_t val) {
	if (tthis->size == tthis->capacity) {
		if (tthis->capacity) {
			tthis->data = (int64_t *)realloc(tthis->data, (tthis->capacity <<= 1));
		} else {
			tthis->data = (int64_t *)calloc(tthis->capacity = 1, sizeof(int64_t));
		}
	}
	tthis->data[tthis->size++] = val;
}
void vector_int64_destruct(vector_int64 *tthis) {
	free(tthis->data);
	tthis->size = 0;
	tthis->capacity = 0;
	tthis->data = NULL;
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