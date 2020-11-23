
#include <stdio.h>

#define PI 3.141592

int main(void)
{
	float h, l, r;
	float area;
	float volume;

	printf("Enter the H, L, R of cone\n");
	scanf("%f %f %f", &h, &l, &r);

	area = PI*r*r + PI*r*l;
	volume = (PI*r*r*h)/3;

	printf("Area of cone:   %6.2f\n", area);
	printf("Volume of cone: %6.2f\n", volume);

	return 0;
}


