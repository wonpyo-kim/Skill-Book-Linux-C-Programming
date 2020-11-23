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

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 2048

int **array_allocation(int value);
static void *matmul_thread(void *arg);

struct thread_parameter {
	int n_threads;
	int position;
};

int **A, **B, **Y;

void
main(int argc, char *argv[])
{
	int i, j;
	int n_threads;
	pthread_t *tid;
	pthread_attr_t attr;
	struct thread_parameter *t_param;
	double sum;

	if (argc != 3 || argv[1][0] != '-') {
		perror("Usage: ./a.out -n <number of threads>");
		exit(1);
	}
	getopt(argc, argv, "n");

	n_threads = atoi(argv[2]);
	if ((n_threads % 2) != 0 || n_threads == 0) {
		perror("Number of threads must be multiple of 2");
		exit(1);
	}

	A = array_allocation(1);
	B = array_allocation(3);
	Y = array_allocation(0);

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	tid = (pthread_t *)calloc(n_threads, sizeof(pthread_t));
	t_param = (struct thread_parameter *)calloc(n_threads, 
		sizeof(struct thread_parameter));

	for (i = 0; i < n_threads; i++) {
		t_param[i].n_threads = n_threads;
		t_param[i].position = (int)i;
		if (pthread_create(&tid[i], &attr, matmul_thread, 
				(void *)&t_param[i]) != 0) {
			perror("pthread_create() failed");
			exit(1);
		}
	}

	for (i = 0; i < n_threads; i++) {
		if (pthread_join(tid[i], NULL) != 0) {
			perror("pthread_join() failed");
			exit(1);
		}
	}

	pthread_attr_destroy(&attr);

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
	free(tid);
	free(t_param);

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

static void *
matmul_thread(void *arg)
{
	int i, j, k;
	int start, end;
	double sum;
	struct thread_parameter *t_param;

	sum = 0.0;
	t_param = (struct thread_parameter *)arg;

	start = SIZE / t_param->n_threads * t_param->position;
	end = SIZE / t_param->n_threads * (t_param->position+1);

	for (i = 0; i < SIZE; i++) {
		for (j = start; j < end; j++) {
			sum = 0.0;
			for (k = 0; k < SIZE; k++) {
				sum += A[i][k] * B[k][j];
			}
			Y[i][j] = (int)sum;
		}
	}

	pthread_exit(NULL);
}

