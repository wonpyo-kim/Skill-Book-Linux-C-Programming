/*
 * BSD-3-Clause
 *
 * Copyright (c) 2020 Wonpyo Kim, 
 * Hallym University Software Convergence School, Hongpub. 
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this 
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this 
 *    list of conditions and the following disclaimer in the documentation and/or other 
 *    materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may
 *    be used to endorse or promote products derived from this software without specific 
 *    prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY 
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED 
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 * WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>

int** make_array(int, int);
void fill_array(int **, int, int);
void print_array(int **, int, int);
void print_average(int **, int, int);

int main(void)
{
	int select;
	int rows, cols;
	int **array;

	printf("This program make a 2-dim arrays\n");

	while (!0) {
		printf("1. Make array\n");
		printf("2. Fill array\n");
		printf("3. Print array\n");
		printf("4. Print average of array\n");
		printf("5. Exit\n");
		printf("Enter the menu: ");
		scanf("%d", &select);

		if (select == 1) {
			printf("Enter the number of rows: ");
			scanf("%d", &rows);
			printf("Enter the number of cols: ");
			scanf("%d", &cols);

			array = make_array(rows, cols);
			printf("\nMake complete!\n\n");
		} else if (select == 2) {
			fill_array(array, rows, cols);
			printf("\nFill complete!\n\n");
		} else if (select == 3) {
			print_array(array, rows, cols);
			printf("\nPrint complete!\n\n");
		} else if (select == 4) {
			print_average(array, rows, cols);
			printf("\nPrint complete!\n\n");
		} else {
			break;
		}
	}

	return 0;
}

int** make_array(int rows, int cols)
{
	int i;
	int **array;

	array = (int **)calloc(rows, sizeof(int *));

	for (i = 0; i < rows; i++) {
		array[i] = (int *)calloc(cols, sizeof(int));
	}

	return array;
}

void fill_array(int **array, int rows, int cols)
{
	int i, j;

	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			printf("Enter the number in array[%d][%d]: ", i, j);
			scanf("%d", array[i]+j);
		}
	}

	return;
}

void print_array(int **array, int rows, int cols)
{
	int i, j;

	printf("\n");
	for (i = 0; i < rows; i++) {
		printf("[%d]: ", i);
		for (j = 0; j < cols; j++) {
			printf("%d ", *(array[i]+j));
		}
		printf("\n");
	}

	return;
}

void print_average(int **array, int rows, int cols)
{
	int i, j;
	int sum;
	float avg;

	sum = 0;
	avg = 0.0;

	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			sum += *(array[i]+j);
		}
	}

	avg = sum / (rows*cols);
	printf("\nAverage of array: %.2f\n", avg);

	return;
}

