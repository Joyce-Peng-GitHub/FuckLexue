#include "vector.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

DECLARE_VECTOR(int64_t)

int main(void) {
	vector_int64_t_t arr;
	vector_int64_t_construct_void(&arr);
	char op[10];
	while (scanf("%s", op) != EOF) {
		if (!strcmp(op, "push")) {
			int64_t val;
			scanf("%lld", &val);
			vector_int64_t_push_back(&arr, &val);
		} else if (!strcmp(op, "pop")) {
			vector_int64_t_pop_back(&arr);
		} else if (!strcmp(op, "resize")) {
			size_t n;
			scanf("%zu", &n);
			vector_int64_t_resize(&arr, n);
		} else if (!strcmp(op, "reserve")) {
			size_t n;
			scanf("%zu", &n);
			vector_int64_t_reserve(&arr, n);
		} else if (!strcmp(op, "size")) {
			printf("%" PRId64 "\n", arr.size);
		} else if (!strcmp(op, "capacity")) {
			printf("%" PRId64 "\n", arr.capacity);
		} else if (!strcmp(op, "at")) {
			size_t pos;
			scanf("%zu", &pos);
			printf("%" PRId64 "\n", arr.data[pos]);
		}
	}
	return 0;
}