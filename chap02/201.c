
#include <stdio.h>

void print_binary(int number);

int main(void)
{
	int number;

	printf("This program converts DEC to BIN\n");
	printf("Enter the number: ");
	scanf("%d", &number);

	print_binary(number);

	return 0;
}

void print_binary(int number)
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


