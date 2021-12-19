#include "../inc/libmx.h"

char *mx_nbr_to_hex(unsigned long nbr) {
	unsigned long number = nbr;
	int num_length = 0;

	while (number) {
		number /= 16;
		num_length++;
	}

	number = nbr;
	char* result = (char*)malloc(num_length * sizeof(char));

	if (number == 0) {
		return mx_strcpy(result, "0");
	}
	else {
		while (number) {
			int temp = number % 16;

			if (temp >= 10) {
				num_length--;
				result[num_length] = temp + 87;
			}
			if (temp < 10) {
				num_length--;
				result[num_length] = temp + 48;
			}

			number /= 16;
		}
	}
	return result;
}

