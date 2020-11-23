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
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 128
#define FIFO_FORWARD "fifo_fw.io"
#define FIFO_BACKWARD "fifo_bk.io"

void
main(int argc, char *argv[])
{
	int i;
	int n_proc = 4;
	int *fd_f, *fd_b;
	pid_t *pid;
	char buf[SIZE];

	if (argc != 2) {
		perror("Usage: ./a.out <job_name (add|sub|mul)>");
		exit(1);
	}

	fd_f = (int *)calloc(n_proc, sizeof(int));
	fd_b = (int *)calloc(n_proc, sizeof(int));
	pid = (pid_t *)calloc(n_proc, sizeof(pid_t));

	if (remove(FIFO_FORWARD) == 0 
			&& remove(FIFO_BACKWARD) == 0) {
		printf("[Parent]: Delete existing fifo file.\n");
	} else {
		printf("[Parent]: File not exist. pass.\n");
	}
		
	printf("[Parent]: Creating fifo file.\n");
	if (mkfifo(FIFO_FORWARD, 0644) == -1 
			|| mkfifo(FIFO_BACKWARD, 0644) == -1) {
		perror("mkfifo() failed");
		exit(1);
	}

	for (i = 0; i < n_proc; i++) {
		pid[i] = fork();
		if (pid[i] > 0) {
			if ((fd_f[i] = open(FIFO_FORWARD, O_RDWR)) == -1) {
				perror("open() failed");
				exit(1);
			}

			if ((fd_b[i] = open(FIFO_BACKWARD, O_RDONLY)) == -1) {
				perror("open() failed");
				exit(1);
			}

			if (write(fd_f[i], argv[1], sizeof(argv[1])) == -1) {
				perror("write() failed");
				exit(1);
			}

			wait(NULL);

			if (read(fd_b[i], buf, SIZE) == -1) {
				perror("read() failed");
				exit(1);
			}

			if (strcmp(buf, argv[1])) {
				printf("[Parent]: received [%s]\n", buf);
			}
		} else if (pid[i] == 0) {
			if ((fd_f[i] = open(FIFO_FORWARD, O_RDONLY)) == -1) {
				perror("open() failed");
				exit(1);
			}

			if ((fd_b[i] = open(FIFO_BACKWARD, O_RDWR)) == -1) {
				perror("open() failed");
				exit(1);
			}

			if (read(fd_f[i], buf, SIZE) == -1) {
				perror("read() failed");
				exit(1);
			}

			switch (i) {
			case 0:
				if (!strcmp(buf, "add")) {
					printf("[Child 1]: Addition is my job.\n");
					strcpy(buf, "child 1: job complete");
				}
				break;
			case 1:
				if (!strcmp(buf, "sub")) {
					printf("[Child 2]: Subtraction is my job.\n");
					strcpy(buf, "child 2: job complete");
				} 
				break;
			case 2:
				if (!strcmp(buf, "mul")) {
					printf("[Child 3]: Multiplication is my job.\n");
					strcpy(buf, "child 3: job complete");
				}
				break;
			case 3:
				printf("[Child 4]: I'm echo process.\n");
				break;
			}

			write(fd_b[i], buf, sizeof(buf));

			exit(0);
		}
	}

	free(fd_f);
	free(fd_b);
	free(pid);

	exit(0);
}

