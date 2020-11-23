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
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 5

void proc_sum(int *data);
void proc_deviation(int *data);
void proc_stddev(int *data);

void
main(int argc, char *argv[])
{
	int i;
	int n_proc;
	int data[SIZE] = {20, 24, 37, 36, 31};
	pid_t *pid;

	if (argc != 2) {
		perror("Usage: ./a.out <number of processes>");
		exit(1);
	}

	n_proc = atoi(argv[1]);

	pid = (pid_t *)calloc(n_proc, sizeof(pid_t));

	for (i = 0; i < n_proc; i++) {
		pid[i] = fork();
		if (pid[i] > 0) {
			wait(NULL);
		} else if (pid[i] == 0) {
			printf("PID is %d, parent process pid is %d\n",
				getpid(), getppid());
			switch (i) {
			case 0:
				proc_sum(data);
				break;
			case 1:
				proc_deviation(data);
				break;
			case 2:
				proc_stddev(data);
				break;
			default:
				printf("I don't do anything. :)\n\n");
				break;
			}
			exit(0);
		}
	}
	
	free(pid);
	exit(0);
}

void
proc_sum(int *data)
{
	int i;
	int sum = 0;

	for (i = 0; i < SIZE; i++) {
		sum += *(data+i);
	}
	printf("[Sum]: %8d\n\n", sum);

	return;
}

void
proc_deviation(int *data)
{
	int i;
	int sum = 0;
	float avg = 0.0;
	float devi[SIZE] = {0.0};
	
	for (i = 0; i < SIZE; i++) {
		sum += *(data+i);
	}
	avg = (float)sum / (float)SIZE;

	printf("[Deviation]: ");
	for (i = 0; i < SIZE; i++) {
		devi[i] = *(data+i) - avg;
		printf(" %.2f", devi[i]);
	}
	printf("\n\n");

	return;
}

void
proc_stddev(int *data)
{
	int i;
	int sum = 0;
	float avg = 0.0;
	float devi[SIZE] = {0.0};
	float variance = 0.0;
	float stddev = 0.0;

	for (i = 0; i < SIZE; i++) {
		sum += *(data+i);
	}
	avg = (float)sum / (float)SIZE;

	for (i = 0; i < SIZE; i++) {
		devi[i] = *(data+i) - avg;
		variance += devi[i] * devi[i];
	}
	variance = variance / SIZE;

	stddev = sqrt(variance);
	printf("[Standard Deviation]: %.4f\n\n", stddev);

	return;
}

