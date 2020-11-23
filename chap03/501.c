
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void
main(int argc, char *argv[])
{
	sigset_t mask;

	if (argc != 3 || argv[1][0] != '-') {
		perror("Usage: ./a.out -[a|d] <signal number>");
		exit(1);
	}

	getopt(argc, argv, "ad");

	switch (argv[1][1]) {
	case 'a':
		if (sigemptyset(&mask) == -1) {
			perror("sigemptyset() failed");
			exit(1);
		}
		if (sigaddset(&mask, atoi(argv[2])) == -1) {
			perror("sigaddset() failed");
			exit(1);
		}
		if (sigismember(&mask, atoi(argv[2]))) {
			printf("%s is a signal(inserted).\n", argv[2]);
		} else {
			printf("%s is not a signal.\n", argv[2]);
		}
		break;
	case 'd':
		if (sigfillset(&mask) == -1) {
			perror("sigfillset() failed");
			exit(1);
		}
		if (sigdelset(&mask, atoi(argv[2]))) {
			perror("sigdelset() failed");
			exit(1);
		}
		if (sigismember(&mask, atoi(argv[2]))) {
			printf("%s is a signal.\n", argv[2]);
		} else {
			printf("%s is not a signal(deleted).\n", argv[2]);
		}
		break;
	}

	exit(0);
}

