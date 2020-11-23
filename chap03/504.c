
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static void signal_handler(int sig);

void
main(int argc, char *argv[])
{
	int count = 0;

	if (argc != 2 || argv[1][0] != '-') {
		perror("Usage: ./a.out -[k]");
		exit(1);
	}

	getopt(argc, argv, "k");

	switch (argv[1][1]) {
	case 'k':
		if (signal(SIGINT, signal_handler) == SIG_ERR) {
			perror("signal() failed");
			exit(1);
		}
		for (;;) {
			printf("I'm running...\n");
			sleep(1);
			count++;
			if (count == 5) {
				kill(getpid(), SIGINT);
			}
		}
		break;
	}

	exit(0);
}

static void
signal_handler(int sig)
{
	printf("SIGINT signal detected. Kill process.\n");

	raise(SIGKILL);

	return;
}

