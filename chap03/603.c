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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 64

void
main(int argc, char *argv[])
{
	int pid, status;
	int s_pipe[2];
	int m_pipe1[2], m_pipe2[2];
	int length;
	char w_buf[SIZE], r_buf[SIZE];

	if (argc != 2 || argv[1][0] != '-') {
		perror("Usage: ./a.out -[s|m]");
		exit(1);
	}

	getopt(argc, argv, "sm");

	switch (argv[1][1]) {
	case 's':
		if (pipe(s_pipe) == -1) {
			perror("pipe() failed");
			exit(1);
		}

		pid = fork();
		if (pid == -1) {
			perror("fork() failed");
			exit(1);
		} else if (pid != 0) {
			close(s_pipe[0]);  // parent will use s_pipe[1] only

			printf("[Parent]: Send message to child process.\n");
		
			strcpy(w_buf, "This message is from parent process.\n");
			write(s_pipe[1], w_buf, strlen(w_buf));

			wait(&status);
		} else {
			close(s_pipe[1]);  // child will use s_pipe[0] only

			if (read(s_pipe[0], r_buf, SIZE) == -1) {
				perror("read() failed");
				exit(1);
			}
			printf("[Child]: %s", r_buf);

			exit(0);
		}
		break;
	case 'm':
		if (pipe(m_pipe1) == -1 || pipe(m_pipe2) == -1) {
			perror("pipe() failed");
			exit(1);
		}

		pid = fork();
		if (pid == -1) {
			perror("fork() failed");
			exit(1);
		} else if (pid != 0) {
			close(m_pipe1[1]);
			close(m_pipe2[0]);

			strcpy(w_buf, "Hey child, Cheer up!\n");
			write(m_pipe2[1], w_buf, strlen(w_buf));
			printf("[Parent]: PUT: %s", w_buf);

			if (read(m_pipe1[0], r_buf, SIZE) == -1) {
				perror("read() failed");
				exit(1);
			}
			printf("[Parent]: GET: %s", r_buf);
		} else {
			close(m_pipe1[0]);
			close(m_pipe2[1]);

			if (read(m_pipe2[0], r_buf, SIZE) == -1) {
				perror("read() failed");
				exit(1);
			}
			printf("[Child]: GET: %s", r_buf);

			strcpy(w_buf, "Okay, See you later\n");
			write(m_pipe1[1], w_buf, strlen(w_buf));
			printf("[Child]: PUT: %s", w_buf);

			exit(0);
		}
		break;
	}

	exit(0);
}

