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
#include <sys/msg.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 256

struct msgbuf {
	long mtype;
	char mdata[MAX_SIZE];
};

void
main(int argc, char *argv[])
{
	pid_t pid;
	struct msgbuf p_msg, c_msg;
	int mid, mkey;
	char buffer[MAX_SIZE];

	if (argc != 3 || argv[1][0] != '-') {
		perror("Usage: ./a.out -k <key>");
		exit(1);
	}
	getopt(argc, argv, "k");

	mkey = atoi(argv[2]);

	if ((mid = msgget((key_t)mkey, 
			IPC_CREAT | IPC_EXCL | 0644)) == -1) {
		printf("[Parent]: Your key is conflicted. ");
		printf("Process will re-define key as [%d]\n", mkey+1);
		mkey += 1;
		if ((mid = msgget((key_t)mkey, IPC_CREAT | 0644)) == -1) {
			perror("msgget() failed");
			exit(1);
		}
	}

	pid = fork();
	if (pid == -1) {
		perror("fork() failed");
		exit(1);
	} else if (pid != 0) {  // Parent
		p_msg.mtype = 1;
		strcpy(p_msg.mdata, "Hello");
		if (msgsnd(mid, &p_msg, strlen(p_msg.mdata), 0) == -1) {
			perror("msgsnd() failed");
			exit(1);
		}

		sleep(1);

		if (msgrcv(mid, &p_msg, MAX_SIZE, 0, 0) == -1) {
			perror("msgrcv() failed");
			exit(1);
		}
		printf("[Parent]: GET: %s\n", p_msg.mdata);

		while (!0) {
			sleep(1);

			printf("[Parent]: Message to child: ");
			fgets(buffer, sizeof(buffer), stdin);

			strcpy(p_msg.mdata, buffer);
			if (msgsnd(mid, &p_msg, strlen(p_msg.mdata)+1, 0) == -1) {
				perror("msgsnd() failed");
				exit(1);
			}
			
			if (!strncmp(buffer, "quit", 4)) {
				printf("[Parent]: Wait for child...\n");
				wait(NULL);
				printf("[Parent]: Done. Exit.\n");
				break;
			}
		}
	} else {  // Child
		if (msgrcv(mid, &c_msg, MAX_SIZE, 0, 0) == -1) {
			perror("msgrcv() failed");
			exit(1);
		}
		printf("[Child1]: GET: %s\n", c_msg.mdata);

		c_msg.mtype = 1;
		strcpy(c_msg.mdata, "I'm ready");
		if (msgsnd(mid, &c_msg, strlen(c_msg.mdata), 0) == -1) {
			perror("msgsnd() failed");
			exit(1);
		}

		sleep(1);

		printf("[Child1]: Now, I'm echo server.\n");
		while (!0) {
			if (msgrcv(mid, &c_msg, MAX_SIZE, 0, 0) == -1) {
				perror("msgrcv() failed");
				exit(1);
			}

			if (!strncmp(c_msg.mdata, "quit", 4)) {
				printf("[Child1]: Exit program.\n");
				break;
			}
			printf("[Child1]: GET: %s\n", c_msg.mdata);

			sleep(1);
		}

		exit(0);
	}

	exit(0);
}

