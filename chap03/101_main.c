
#include <stdio.h>
#include "101.h"

int main(void)
{
	int number;

	printf("This program converts DEC to reversed BINARY.\n");
	printf("Enter the number: ");
	scanf("%d", &number);

	print_reversed_binary(number);

	return 0;
}


