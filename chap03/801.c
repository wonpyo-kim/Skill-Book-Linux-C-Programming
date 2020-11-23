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
#include <sys/un.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 256
#define MSG_SIZE 128

int
main(int argc, char *argv[])
{
	pid_t pid;
	int j, sockfd, read_bytes;
	int msglen;
	struct sockaddr_un server_addr, client_addr;
	socklen_t socklen;
	char sock_name[MAX_NAME];
	char buffer[MSG_SIZE];

	if (argc != 3 || argv[1][0] != '-') {
		perror("Usage: ./a.out -f <socket filename>");
		exit(1);
	}
	getopt(argc, argv, "f");

	strcpy(sock_name, argv[2]);

	if ((sockfd = socket(AF_UNIX, SOCK_DGRAM, 0)) == -1) {
		perror("socket() failed");
		exit(1);
	}

	pid = fork();
	if (pid == -1) {
		perror("fork() failed");
		exit(1);
	} else if (pid != 0) {
		memset(&server_addr, 0, sizeof(struct sockaddr_un));
		server_addr.sun_family = AF_UNIX;
		strncpy(server_addr.sun_path, sock_name, 
			sizeof(sock_name)-1);

		while (!0) {
			printf("[Parent]: Message to child: ");
			fgets(buffer, sizeof(buffer), stdin);

			msglen = strlen(buffer);
			if (sendto(sockfd, buffer, msglen, 0, 
					(struct sockaddr *)&server_addr, 
					sizeof(struct sockaddr_un)) != msglen) {
				perror("sendto() failed");
				exit(1);
			}

			if (!strncmp(buffer, "quit", 4)) {
				printf("[Parent]: Wait for child...\n");
				wait(NULL);

				remove(client_addr.sun_path);

				printf("[Parent]: Done. Exit.\n");
				break;
			}

			sleep(1);
		}
	} else {
		memset(&server_addr, 0, sizeof(struct sockaddr_un));
		server_addr.sun_family = AF_UNIX;
		strncpy(server_addr.sun_path, sock_name, 
			sizeof(sock_name)-1);

		if (bind(sockfd, (struct sockaddr *)&server_addr, 
				sizeof(struct sockaddr_un)) == -1) {
			perror("bind() failed");
			exit(1);
		} 

		while (!0) {
			socklen = sizeof(struct sockaddr_un);
			if ((read_bytes = recvfrom(sockfd, buffer, MSG_SIZE, 0, 
					(struct sockaddr *)&client_addr, &socklen)) == -1) {
				perror("recvfrom() failed");
				exit(1);
			}

			printf("[Child1]: [%ld bytes]: %s\n", 
				(long)read_bytes, strtok(buffer, "\n"));

			if (!strncmp(buffer, "quit", 4)) {
				printf("[Child1]: Exit program.\n");
				break;
			}
		}
	}

	exit(0);
}

