
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static void signal_handler(int sig);

void
main(int argc, char *argv[])
{
	int count = 0;
	sigset_t mask;

	if (argc != 2 || argv[1][0] != '-') {
		perror("Usage: ./a.out -[h]");
		exit(1);
	}

	getopt(argc, argv, "h");

	switch (argv[1][1]) {
	case 'h':
		if (signal(SIGINT, signal_handler) == SIG_ERR) {
			perror("signal() failed");
			exit(1);
		}
		for (;;) {
			printf("I'm still running...\n");
			sleep(1);
			count++;
			if (count == 10) {
				if (signal(SIGINT, SIG_DFL) == SIG_ERR) {
					perror("signal() failed");
					exit(1);
				}
			}
		}
		break;
	}

	exit(0);
}

static void 
signal_handler(int sig)
{
	printf("Handler is called !!\n");
}

