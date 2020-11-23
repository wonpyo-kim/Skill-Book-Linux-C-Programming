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

#define SIZE 4

static int **array_allocation(int value);
static void *matmul_thread(void *arg);
static void print_arrays(void);

struct thread_parameter {
	int n_threads;
	int position;
	int state;  // 0: lived, 1: terminated, 2: joined
};

static pthread_mutex_t t_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t t_cond = PTHREAD_COND_INITIALIZER;
static int **A, **B, **Y;
static int processing;

void
main(int argc, char *argv[])
{
	int i, j;
	int n_threads, lived;
	pthread_t *tid;
	pthread_attr_t attr;
	struct thread_parameter *t_param;
	double sum;

	n_threads = 4;
	lived = n_threads;

	A = array_allocation(1);
	B = array_allocation(1);
	Y = array_allocation(0);

	printf("[Original Arrays]\n");
	print_arrays();

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	tid = (pthread_t *)calloc(n_threads, sizeof(pthread_t));
	t_param = (struct thread_parameter *)calloc(n_threads,
		sizeof(struct thread_parameter));

	for (i = 0; i < SIZE; i++) {
		t_param[i].n_threads = n_threads;
		t_param[i].position = (int)i;
		t_param[i].state = 0;

		if (pthread_create(&tid[i], &attr, matmul_thread,
				(void *)&t_param[i]) != 0) {
			perror("pthread_create() failed");
			exit(1);
		}
	}

	while (lived > 0) {
		if (pthread_mutex_lock(&t_mutex) != 0) {
			perror("pthread_mutex_lock() failed");
			exit(1);
		}

		while (processing == 0) {
			if (pthread_cond_wait(&t_cond, &t_mutex) != 0) {
				perror("pthread_cond_wait() failed");
				exit(1);
			}
		}

		for (i = 0; i < n_threads; i++) {
			if (t_param[i].state == 1) {
				if (pthread_join(tid[i], NULL) != 0) {
					perror("pthread_join() failed");
					exit(1);
				}

				t_param[i].state = 2;
				lived--;
				processing--;

				printf("Thread %d ended. (lived: %d\n", i, lived);
			}
		}

		if (pthread_mutex_unlock(&t_mutex) != 0) {
			perror("pthread_mutex_unlock() failed");
			exit(1);
		}
	}

	pthread_attr_destroy(&attr);

	printf("\n[Result Arrays]\n");
	print_arrays();

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

	array = (int **)calloc(SIZE, sizeof(int **));
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
	int ret;
	int start, end;
	double sum;
	struct thread_parameter *t_param;

	sum = 0.0;
	t_param = (struct thread_parameter *)arg;

	start = SIZE / t_param->n_threads * t_param->position;
	end = SIZE / t_param->n_threads * (t_param->position+1);

	if (pthread_mutex_lock(&t_mutex) != 0) {
		perror("pthread_mutex_lock() failed");
		exit(1);
	}

	processing++;

	for (i = 0; i < SIZE; i++) {
		for (j = start; j < end; j++) {
			sum = 0.0;
			for (k = 0; k < SIZE; k++) {
				if (t_param->position != 0) {
					B[k][j] = B[k][j] * (2*t_param->position);
				}
				sum += A[i][k] * B[k][j];
			}
			Y[i][j] = (int)sum;
		}
	}

	t_param->state = 1;

	if (pthread_mutex_unlock(&t_mutex) != 0) {
		perror("pthread_mutex_unlock() failed");
		exit(1);
	}

	if (pthread_cond_signal(&t_cond) != 0) {
		perror("pthread_cond_signal() failed");
		exit(1);
	}

	pthread_exit(NULL);
}

void
print_arrays(void)
{
	int i, j;

	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			printf("%4d ", A[i][j]);
		}
		printf("   ");
		for (j = 0; j < SIZE; j++) {
			printf("%4d ", B[i][j]);
		}
		printf("   ");
		for (j = 0; j < SIZE; j++) {
			printf("%4d ", Y[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

