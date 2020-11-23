
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void    get_numbers    (double *x, double *y);
double  addition       (double x, double y);
double  substraction   (double x, double y);
double  multiplication (double x, double y);
double  division       (double x, double y);

void
main(int argc, char *argv[])
{
	int opt;
	double x, y, r;

	if (argc != 2 || argv[1][0] != '-') {
		perror("Usage: ./a.out -a -s -m -d");
		exit(1);
	}

	while ((opt = getopt(argc, argv, "asmd")) != -1) {
		if (opt != '?') {
			get_numbers(&x, &y);
		} else {
			exit(1);
		}
	}

	switch (argv[1][1]) {
	case 'a':
		r = addition(x, y);
		break;
	case 's':
		r = substraction(x, y);
		break;
	case 'm':
		r = multiplication(x, y);
		break;
	case 'd':
		r = division(x, y);
		break;
	}
	printf("Result: %.3f\n", r);

	exit(0);
}

void
get_numbers(double *x, double *y)
{
	printf("Enter the number x: ");
	scanf("%lf", x);
	printf("Enter the number y: ");
	scanf("%lf", y);
}

double
addition(double x, double y)
{
	return x + y;
}

double
substraction(double x, double y)
{
	return x - y;
}

double
multiplication(double x, double y)
{
	return x * y;
}

double
division(double x, double y)
{
	if (x == 0 || y == 0) {
		return 0.0;
	} else {
		return x / y;
	}
}

