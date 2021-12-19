#include "../inc/libmx.h"

unsigned long mx_hex_to_nbr(const char *hex) {
	int length = 0;
	unsigned long num = 0;
	unsigned long base = 1;

	if (hex != NULL) {
		while (hex[length]) {
			length++;
		}
	}
	else {
		return num;
	}

	for (int i = 0; i <= length; i++) {
		if (hex[length - i] >= '0' && hex[length - i] <= '9') {
			num = num + (hex[length - i] - 48) * base;
			base = base * 16;
		}
		if (hex[length - i] >= 'A' && hex[length - i] <= 'F') {
			num = num + (hex[length - i] - 55) * base;
			base = base * 16;
		}
		if (hex[length - i] >= 'a' && hex[length - i] <= 'f') {
			num = num + (hex[length - i] - 87) * base;
			base = base * 16;
		}
	}
	return num;
}

