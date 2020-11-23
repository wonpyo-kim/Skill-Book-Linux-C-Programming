
#include <stdio.h>
#include <stdlib.h>

#define SIZE 2048

int **array_allocation(int value);

void
main(int argc, char *argv[])
{
	int i, j, k;
	int **A, **B, **Y;
	double sum;

	A = array_allocation(1);
	B = array_allocation(3);
	Y = array_allocation(0);

	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			sum = 0.0;
			for (k = 0; k < SIZE; k++) {
				sum += A[i][k] * B[k][j];
			}
			Y[i][j] = (int)sum;
		}
	}

	sum = 0.0;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			sum += (double)Y[i][j];
		}
	}
	printf("Sum of result array: %.2lf\n", sum);

	free(A);
	free(B);
	free(Y);

	exit(0);
}

int **
array_allocation(int value)
{
	int i, j;
	int **array;

	array = (int **)calloc(SIZE, sizeof(int *));
	for (i = 0; i < SIZE; i++) {
		array[i] = (int *)calloc(SIZE, sizeof(int));

		for (j = 0; j < SIZE; j++) {
			array[i][j] = value;
		}
	}

	return array;
}

