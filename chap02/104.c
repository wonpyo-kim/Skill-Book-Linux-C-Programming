
#include <stdio.h>

int main(void)
{
	int i1 = 20;
	int i2 = 35;
	int i3 = 90;
	double d1 = 20.0;
	double d2 = 35.0;
	double dr;
	char c = 'A';

	printf("c means in number:  %d\n", c);
	printf("i1 means : %d\n", i1);
	printf("i2 means : %d\n", i2);
	printf("i3 means : %d\n", i3);
	printf("d1 means : %.2f\n", d1);
	printf("d2 means : %.3f\n\n", d2);

	dr = (double)(i3 / i2);
	printf("(double)(i3 / i2) : %.3f\n", dr);

	c = (char)(i3 - d1);
	printf("(char)(i3 - d1) : %c\n", c);

	return 0;
}


