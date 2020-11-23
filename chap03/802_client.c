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
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IPV4_ADDRESS "127.0.0.1"
#define MAX_MSGLEN 1024

void
main(int argc, char *argv[])
{
	int ports;
	int sockfd;
	int sd_len, rv_len;
	char sd_buffer[MAX_MSGLEN], rv_buffer[MAX_MSGLEN];
	struct sockaddr_in sv_addr;

	if (argc != 3 || argv[1][0] != '-') {
		perror("Usage: ./a.out -p <portnum>");
		exit(1);
	}

	getopt(argc, argv, "p");

	ports = atoi(argv[2]);
	if (ports < 1024 || ports > 65535) {
		perror("portnum must be (1023 < portnum < 65536)");
		exit(1);
	}

	memset(&sv_addr, 0, sizeof(sv_addr));
	sv_addr.sin_family = AF_INET;
	sv_addr.sin_port = htons(ports);
	sv_addr.sin_addr.s_addr = inet_addr(IPV4_ADDRESS);

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket() failed");
		exit(1);
	}

	if (connect(sockfd, (struct sockaddr *)&sv_addr, 
			sizeof(sv_addr)) == -1) {
		perror("connect() failed");
		exit(1);
	}

	while (!0) {
		printf("[Client]: Send message to server: ");
		fgets(sd_buffer, MAX_MSGLEN, stdin);

		sd_len = strlen(sd_buffer);
		if (send(sockfd, sd_buffer, sd_len, 0) != sd_len) {
			perror("send() failed");
			exit(1);
		}

		if (!strncmp(sd_buffer, "quit", 4)) {
			printf("[Client]: Terminate.\n");
			break;
		}

		if ((rv_len = recv(sockfd, rv_buffer, 
				MAX_MSGLEN-1, 0)) <= 0) {
			perror("recv() failed");
			exit(1);
		}

		rv_buffer[rv_len] = '\0';
		printf("[Server]: %s", rv_buffer);
	}

	close(sockfd);

	exit(0);
}

