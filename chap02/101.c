
#include <stdio.h>

int main(void)
{
	int a, b, c;
	int x;
	float y;

	printf("ax^2 + bx + c = y\n");

	printf("Enter a, b, c\n");
	scanf("%d %d %d", &a, &b, &c);

	printf("Enter x\n");
	scanf("%d", &x);

	y = a * x * x + b * x + c;

	printf("The answer is %5.3f\n", y);

	return 0;
}


