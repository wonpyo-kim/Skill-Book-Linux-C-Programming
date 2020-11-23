
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static void signal_handler(int sig);

void
main(int argc, char *argv[])
{
	int count = 0;
	struct sigaction sigact;
	struct sigaction sigact_def;

	if (argc != 2 || argv[1][0] != '-') {
		perror("Usage: ./a.out -[a]");
		exit(1);
	}

	getopt(argc, argv, "a");

	switch (argv[1][1]) {
	case 'a':
		sigact.sa_handler = signal_handler;
		sigact.sa_flags = 0;
		if (sigfillset(&sigact.sa_mask) == -1) {
			perror("sigfillset() failed");
			exit(1);
		}
		if (sigaction(SIGINT, &sigact, &sigact_def) == -1) {
			perror("sigaction() failed");
			exit(1);
		}
		if (sigaction(SIGQUIT, &sigact, &sigact_def) == -1) {
			perror("sigaction() failed");
			exit(1);
		}
		for (;;) {
			printf("I'm still running...\n");
			sleep(1);
			count++;
			if (count == 10) {
				if (sigaction(SIGINT, &sigact_def, NULL) == -1) {
					perror("sigaction() failed");
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
	static int count = 0;

	if (sig == SIGINT) {
		count++;
		printf("SIGINT detected %d times.\n", count);
	} else {
		printf("Another signal is detected.\n");
	}

	return;
}

