
#include <stdio.h>
#include <stdbool.h>

int main(void)
{
	int i = 9411;
	short s = 22;
	bool b = false;
	char c = 'H';
	double d = 255.35;
	float f = 99.9;

	printf("------------------------\n");
	printf("Implicit type conversion\n");
	printf("------------------------\n");
	printf("data: %d, %d, %d, %c, %f, %f\n", i, s, b, c, d, f);
	printf("boolean + character : %c\n", b + c);
	printf("double + char :       %f\n", d + c);
	printf("float + char :        %f\n", f + c);
	printf("short + int :         %d\n", s + i);

	i = i + b;
	f = f + i;
	d = d + f;
	b = -d;

	printf("Calculation result\n");
	printf("i: %d\n", i);
	printf("f: %f\n", f);
	printf("d: %f\n", d);
	printf("b: %d\n", b);

	return 0;
}


