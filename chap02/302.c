
#include <stdio.h>
#include <math.h>

int main(void)
{
	int select;
	float a, b, c;
	float x1, x2;
	float discriminant;

	while (!0) {
		printf("This program calculates quadratic equation\n");
		printf("1. Calculates\n");
		printf("2. Exit\n");
		printf("Enter the menu: ");
		scanf("%d", &select);
	
		if (select == 1) {
			printf("Enter the a, b, c: ");
			scanf("%f %f %f", &a, &b, &c);
		
			discriminant = b * b - (4 * a * c);
		
			if (a == 0 && b == 0) {
				printf("\nThe root doesn't exist\n\n");
			} else if (a == 0 && b != 0 && c != 0) {
				x1 = (-1 * c) / b;
				printf("\nThe root is [%f]\n\n", x1);
			} else if (discriminant < 0) {
				printf("\nThe root doesn't have real values\n\n");
			} else {
				x1 = ((-1 * b) + sqrt(b * b - (4 * a * c))) / (2 * a);
				x2 = ((-1 * b) - sqrt(b * b - (4 * a * c))) / (2 * a);
				printf("\nThe root is [%f, %f]\n\n", x1, x2);
			}
		} else {
			break;
		}
	}

	return 0;
}

