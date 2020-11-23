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

#include <fcntl.h>
#include <unistd.h>
#include <mqueue.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_SIZE 256
#define MAX_SIZE 2048

mqd_t mqd;

void
main(int argc, char *argv[])
{
	pid_t pid;
	int ret;
	char s_buf[MIN_SIZE], r_buf[MAX_SIZE];
	char *mq_name;
	mqd_t mqd_snd;
	struct mq_attr mattr;

	if (argc != 3 || argv[1][0] != '-') {
		perror("Usage: ./a.out -f <message queue name>");
		exit(1);
	}
	getopt(argc, argv, "f");

	mq_name = argv[2];

	mattr.mq_maxmsg = 10;
	mattr.mq_msgsize = 1024;

	pid = fork();
	if (pid == -1) {
		perror("fork() failed");
		exit(1);
	} else if (pid != 0) {
		if ((mqd = mq_open(mq_name, O_RDWR | O_CREAT, 
				0644, &mattr)) == -1) {
			perror("mq_open() failed");
			exit(1);
		}

		while (!0) {
			printf("[Parent]: Message to child: ");
			fgets(s_buf, sizeof(s_buf), stdin);

			if ((mqd_snd = mq_open(mq_name, O_RDWR)) == -1) {
				perror("mq_open() failed");
				exit(1);
			}
			if (mq_send(mqd_snd, s_buf, sizeof(s_buf), 1) == -1) {
				perror("mq_send() failed");
				exit(1);
			}
			mq_close(mqd_snd);
			
			if (!strncmp(s_buf, "quit", 4)) {
				printf("[Parent]: Wait for child...\n");
				wait(NULL);

				printf("[Parent]: Clearing message queue...\n");
				if (mq_close(mqd) == -1) {
					perror("mq_close() failed");
					exit(1);
				}
				if (mq_unlink(mq_name) == -1) {
					perror("mq_unlink() failed");
					exit(1);
				}

				printf("[Parent]: Done. Exit.\n");
				break;
			}

			sleep(0.5);
		}
	} else {
		if ((mqd = mq_open(mq_name, O_RDONLY)) == -1) {
			perror("mq_open() failed");
			exit(1);
		}

		while (!0) {
			ret = mq_receive(mqd, r_buf, sizeof(r_buf), NULL);
			if (ret == -1) {
				perror("mq_receive() failed");
				exit(1);
			} else if (ret > 0) {
				if (!strncmp(r_buf, "quit", 4)) {
					printf("[Child1]: Exit program.\n");
					break;
				}
				printf("[Child1]: GET: %s\n", r_buf);
			} else {
				// pass
			}
		}

		exit(0);
	}

	exit(0);
}

