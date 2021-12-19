#include "../inc/libmx.h"

char *mx_itoa(int number) {
	int num_length = 0;
	bool negative = false;

	if (number < 0) {
		number *= -1;
		num_length = 1;
		negative = true;
	}

	int input = number;

	while (input) {
		input /= 10;
		num_length++;
	}

	input = number;
	int num_len_copy = num_length;
	char* result = (char*)malloc((num_length + 1) * sizeof(char));

	if (input == 0) {
		return mx_strcpy(result, "0");
	}
	if (input == -2147483647 - 1) {
		return mx_strcpy(result, "-2147483648");
	}
	else {
		while (input) {
			int temp = input % 10;

			num_length--;
			result[num_length] = temp + '0';
	
			input /= 10;
		}
	}

	if (negative) {
		result[--num_length] = '-';
	}

	result[num_len_copy] = '\0';
	return result;
}

