
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 5

void proc_sum(int *data);
void proc_deviation(int *data);
void proc_stddev(int *data);

void
main(int argc, char *argv[])
{
	int i;
	int n_proc;
	int data[SIZE] = {20, 24, 37, 36, 31};
	pid_t *pid;

	if (argc != 2) {
		perror("Usage: ./a.out <number of processes>");
		exit(1);
	}

	n_proc = atoi(argv[1]);

	pid = (pid_t *)calloc(n_proc, sizeof(pid_t));

	for (i = 0; i < n_proc; i++) {
		pid[i] = fork();
		if (pid[i] > 0) {
			wait(NULL);
		} else if (pid[i] == 0) {
			printf("PID is %d, parent process pid is %d\n",
				getpid(), getppid());
			switch (i) {
			case 0:
				proc_sum(data);
				break;
			case 1:
				proc_deviation(data);
				break;
			case 2:
				proc_stddev(data);
				break;
			default:
				printf("I don't do anything. :)\n\n");
				break;
			}
			exit(0);
		}
	}
	
	free(pid);
	exit(0);
}

void
proc_sum(int *data)
{
	int i;
	int sum = 0;

	for (i = 0; i < SIZE; i++) {
		sum += *(data+i);
	}
	printf("[Sum]: %8d\n\n", sum);

	return;
}

void
proc_deviation(int *data)
{
	int i;
	int sum = 0;
	float avg = 0.0;
	float devi[SIZE] = {0.0};
	
	for (i = 0; i < SIZE; i++) {
		sum += *(data+i);
	}
	avg = (float)sum / (float)SIZE;

	printf("[Deviation]: ");
	for (i = 0; i < SIZE; i++) {
		devi[i] = *(data+i) - avg;
		printf(" %.2f", devi[i]);
	}
	printf("\n\n");

	return;
}

void
proc_stddev(int *data)
{
	int i;
	int sum = 0;
	float avg = 0.0;
	float devi[SIZE] = {0.0};
	float variance = 0.0;
	float stddev = 0.0;

	for (i = 0; i < SIZE; i++) {
		sum += *(data+i);
	}
	avg = (float)sum / (float)SIZE;

	for (i = 0; i < SIZE; i++) {
		devi[i] = *(data+i) - avg;
		variance += devi[i] * devi[i];
	}
	variance = variance / SIZE;

	stddev = sqrt(variance);
	printf("[Standard Deviation]: %.4f\n\n", stddev);

	return;
}

