/*
 * Helpers.c
 *
 * Created: 2/28/2024 4:59:26 AM
 *  Author: asus
 */ 
#include "Helpers.h"

int get_digit_count(int num) {
	int count = 0;

	// Handle the case when the number is zero separately
	if (num == 0) {
		return 1;
	}

	// Count digits by repeatedly dividing by 10
	while (num != 0) {
		num /= 10;
		count++;
	}

	return count;
}