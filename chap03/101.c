
#include "101.h"

void print_reversed_binary(int number)
{
	int mod;

	while (!0) {
		mod = number % 2;
		printf("%d ", mod);
		if ((number / 2) == 0) {
			break;
		}
		number /= 2;
	}
	printf("\n");
	
	return;
}

