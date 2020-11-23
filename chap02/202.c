
#include <stdio.h>

void print_menu(void);
void get_numbers(double *, double *);
double add(double, double);
double sub(double, double);
double mul(double, double);
double div(double, double);

int main(void)
{
	int select;
	double x, y;
	double r;

	printf("This program is a calculator\n");

	while (!0) {
		print_menu();

		printf("Select: ");
		scanf("%d", &select);

		if (select >= 1 && select < 5) {
			get_numbers(&x, &y);
			if (select == 1) {
				r = add(x, y);
			} else if (select == 2) {
				r = sub(x, y);	
			} else if (select == 3) {
				r = mul(x, y);
			} else if (select == 4) {
				r = div(x, y);
			}
			printf("Result: %.3f\n", r);
		} else {
			break;
		}
	}

	return 0;
}

void print_menu(void)
{
	printf("\nPlease select menu\n");
	printf("1. Add\n");
	printf("2. Sub\n");
	printf("3. Multiply\n");
	printf("4. Divide\n");
	printf("5. Exit\n");
}

void get_numbers(double *x, double *y)
{
	printf("Enter the x: ");
	scanf("%lf", x);
	printf("Enter the y: ");
	scanf("%lf", y);
}

double add(double x, double y)
{
	return x + y;
}

double sub(double x, double y)
{
	return x - y;
}

double mul(double x, double y)
{
	return x * y;
}

double div(double x, double y)
{
	if (x == 0 || y == 0) {
		return 0.0;
	} else {
		return x / y;
	}
}

