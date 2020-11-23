
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

