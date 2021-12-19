#include "../inc/libmx.h"

void* mx_memmem(const void* big, size_t big_len, const void* little, size_t little_len) {
	unsigned char* temp_big = NULL;
	unsigned char* temp_little = NULL;

	if (big_len >= little_len && big_len > 0 && little_len > 0) {
		temp_big = (unsigned char*)big;
		temp_little = (unsigned char*)little;
		while (*temp_big) {
			if (mx_memcmp(temp_big, temp_little, little_len - 1) == 0) {
				return temp_big;
			}
			temp_big++;
		}
	}
	return NULL;
}

