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
#include <semaphore.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static const char *sem_file = "sem.tmp";

void
main(int argc, char *argv[])
{
	int fd, rc;
	pid_t pid;
	sem_t *sem;
	char *sem_name;
	char prev[1024], buffer[1024];

	if (argc != 3 || argv[1][0] != '-') {
		perror("Usage: ./a.out -f <semaphore name>");
		exit(1);
	}
	getopt(argc, argv, "f");

	sem_name = argv[2];

	sprintf(prev, "rm %s", sem_file);
	system(prev);
	sem_unlink(sem_name);

	pid = fork();
	if (pid == -1) {
		perror("fork() failed");
		exit(1);
	} else if (pid != 0) {
		if ((sem = sem_open(sem_name, O_CREAT, 0644, 1)) == NULL) {
			perror("sem_open() failed");
			exit(1);
		}

		if ((fd = open(sem_file, O_RDWR | O_CREAT, 0644)) == -1) {
			perror("open() failed");
			exit(1);
		}

		while (!0) {
			printf("[Parent]: Message to child: ");
			fgets(buffer, sizeof(buffer), stdin);

			sem_wait(sem);

			lseek(fd, 0, SEEK_SET);
			write(fd, buffer, sizeof(buffer));

			sem_post(sem);

			if (!strncmp(buffer, "quit", 4)) {
				printf("[Parent]: Wait for child...\n");
				wait(NULL);

				printf("[Parent]: Clearing semaphore...\n");
				if (sem_close(sem) == -1) {
					perror("sem_close() failed");
					exit(1);
				}
				if (sem_unlink(sem_name) == -1) {
					perror("sem_unlink() failed");
					exit(1);
				}

				close(fd);

				printf("[Parent]: Done. Exit.\n");
				break;
			}
			sleep(1);
		}
	} else {
		sleep(0.5);

		if ((sem = sem_open(sem_name, 0, 0644, 0)) == NULL) {
			perror("sem_open() failed");
			exit(1);
		}

		if ((fd = open(sem_file, O_RDONLY)) == -1) {
			perror("open() failed");
			exit(1);
		}

		while (!0) {
			sem_wait(sem);

			lseek(fd, 0, SEEK_SET);
			rc = read(fd, buffer, sizeof(buffer));
			if (rc == -1) {
				perror("read() failed");
				exit(1);
			} else if (rc > 0) {
				if (strcmp(buffer, prev)) {
					printf("[Child1]: GET: %s\n", buffer);
					strcpy(prev, buffer);
					if (!strncmp(buffer, "quit", 4)) {
						printf("[Child1]: Exit program.\n");
						break;
					}
				}
			} else {
				// pass
			}

			sem_post(sem);
		}

		exit(0);
	}

	exit(0);
}

