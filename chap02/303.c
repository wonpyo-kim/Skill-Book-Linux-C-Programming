
#include <stdio.h>

void print_star(int);

int main(void)
{
	int select, range;

	printf("This program prints stars\n");

	while (!0) {
		printf("1. Print stars\n");
		printf("2. Exit\n");
		printf("Choose the menu: ");
		scanf("%d", &select);

		if (select == 1) {
			printf("Range of stars: ");
			scanf("%d", &range);
			print_star(range);
		} else {
			break;
		}
	}

	return 0;
}

void print_star(int range)
{
	int i, j;

	for (i = 0; i < range; i++) {
		for (j = 0; j < i; j++) {
			printf(" ");
		}
		for (j = 1; j < range*2-(2*i); j++) {
			printf("*");
		}
		printf("\n");
	}
	for (i = range; i > 0; i--) {
		for (j = i; j > 1; j--) {
			printf(" ");
		}
		for (j = range*2-(2*i)+1; j > 0; j--) {
			printf("*");
		}
		printf("\n");
	}
}

