
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 256

struct shm_data {
	int val;
	char text[MAX_SIZE];
};

static void print_shminfo(struct shmid_ds shmds);

void
main(int argc, char *argv[])
{
	pid_t pid;
	int shmid, shmkey;
	void *shmaddr;
	struct shmid_ds shmds;
	struct shm_data *shmbuf;
	char buffer[MAX_SIZE];

	if (argc != 3 || argv[1][0] != '-') {
		perror("Usage: ./a.out -k <key>");
		exit(1);
	}

	getopt(argc, argv, "k");

	shmkey = atoi(argv[2]);

	if ((shmid = shmget((key_t)shmkey, MAX_SIZE, 
			IPC_CREAT | IPC_EXCL | 0644)) == -1) {
		printf("[Parent]: Your key is conflicted. ");
		printf("Process will re-define key as [%d]\n", shmkey+1);
		shmkey += 1;
		if ((shmid = shmget((key_t)shmkey, MAX_SIZE, 
				IPC_CREAT | 0644)) == -1) {
			perror("shmget() failed");
			exit(1);
		}
	}

	pid = fork();
	if (pid == -1) {
		perror("fork() failed");
		exit(1);
	} else if (pid != 0) {
		if ((shmaddr = shmat(shmid, (void *)0, 0)) == (void *)-1) {
			perror("shmat() failed");
			exit(1);
		}

		shmbuf = (struct shm_data *)shmaddr;
		shmbuf->val = 0;
		
		while (!0) {
			sleep(1);

			printf("[Parent]: Message to child: ");
			fgets(buffer, sizeof(buffer), stdin);

			shmbuf->val = 1;
			strcpy(shmbuf->text, buffer);
			
			if (!strncmp(buffer, "quit", 4)) {
				printf("[Parent]: Wait for child...\n");
				wait(NULL);
				printf("[Parent]: Done. Exit.\n");
				if (shmdt(shmaddr) == -1) {
					perror("shmdt() failed");
					exit(1);
				}
				if (shmctl(shmid, IPC_RMID, 0) == -1) {
					perror("shmctl() failed");
					exit(1);
				}
				break;
			}
		}
	} else { 
		if ((shmaddr = shmat(shmid, (void *)0, 0)) == (void *)-1) {
			perror("shmat() failed");
			exit(1);
		}

		shmbuf = (struct shm_data *)shmaddr;

		printf("[Child1]: I'm echo server.\n");
		while (!0) {
			if (shmbuf->val == 1) {
				if (!strncmp(shmbuf->text, "quit", 4)) {
					printf("[Child1]: Exit program.\n");
					if (shmdt(shmaddr) == -1) {
						perror("shmdt() failed");
						exit(1);
					}
					break;
				} else if (!strncmp(shmbuf->text, "info", 4)) {
					if (shmctl(shmid, IPC_STAT, &shmds) == -1) {
						perror("shmctl() failed");
						exit(1);
					}
					print_shminfo(shmds);
				}
				printf("[Child1]: GET: %s\n", shmbuf->text);
				shmbuf->val = 0;
			}
		}

		exit(0);
	}

	exit(0);
}

static void
print_shminfo(struct shmid_ds shmds)
{
	printf("Print shared memory information.\n");
	printf("  Permission:          %o\n", shmds.shm_perm.mode);
	printf("  Size of segment:     %ld\n", shmds.shm_segsz);
	printf("  Last shmat():        %s", ctime(&shmds.shm_atime));
	printf("  Last shmdt():        %s", ctime(&shmds.shm_dtime));
	printf("  Last change:         %s", ctime(&shmds.shm_ctime));
	printf("  PID of creator:      %d\n", shmds.shm_cpid);
	printf("  PID of last at/dt:   %d\n", shmds.shm_lpid);
	printf("  Current at process:  %ld\n\n", shmds.shm_nattch);

	return;
}

