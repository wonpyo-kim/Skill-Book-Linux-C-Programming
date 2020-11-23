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

#define SIZE 5

void proc_sum(int *data);

void
main(int argc, char *argv[])
{
	int pid, c_pid, status;
	int data[SIZE] = {20, 24, 37, 36, 31};

	if (argc != 2 || argv[1][0] != '-') {
		perror("Usage: ./a.out -[w|p]");
		exit(1);
	}

	getopt(argc, argv, "wp");

	switch (argv[1][1]) {
	case 'w':
		pid = fork();
		if (pid == -1) {
			perror("fork() failed");
			exit(1);
		} else if (pid != 0) {
			printf("[Parent]: Waiting for child process...\n");
			c_pid = wait(&status);
			if (WIFEXITED(status)) {
				printf("[Parent]: child process %d exited: %x\n", 
					c_pid, status);
			} else {
				printf("[Parent]: child process exited abnormally\n");
			}
		} else {
			printf("[Child]: Processing...\n");
			proc_sum(data);
			exit(5);
		}
		break;
	case 'p':
		pid = fork();
		if (pid == -1) {
			perror("fork() failed");
			exit(1);
		} else if (pid != 0) {
			while (waitpid(pid, &status, WNOHANG) == 0) {
				printf("[Parent]: Waiting for child process...\n");
				sleep(1);
			}
			printf("[Parent]: child process %d exited: %x\n", 
				pid, status);
		} else {
			printf("[Child]: Processing...\n");
			proc_sum(data);
			sleep(5);
			exit(0);
		}
		break;
	}

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
	printf("[Child]: %d\n", sum);
	
	return;
}

