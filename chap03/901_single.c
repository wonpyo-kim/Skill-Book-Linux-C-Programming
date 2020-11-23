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

