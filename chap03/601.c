
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

#define TARGET_FILE "text.txt"
#define SIZE 1024

void
main(int argc, char *argv[])
{
	int pid, status;
	int fp_d, fc_d;
	struct flock fp_lock, fc_lock;
	char buf[SIZE];

	pid = fork();
	if (pid == -1) {
		perror("fork() failed");
		exit(1);
	} else if (pid > 0) {
		wait(&status);

		printf("[Parent]: Process will lock [%s]\n", TARGET_FILE);
		fp_lock.l_type = F_RDLCK;
		fp_lock.l_whence = SEEK_SET;
		fp_lock.l_start = 0;
		fp_lock.l_len = 0;

		if ((fp_d = open(TARGET_FILE, O_RDWR)) == -1) {
			perror("open() failed");
			exit(1);
		}

		if (fcntl(fp_d, F_SETLKW, &fp_lock) == -1) {
			perror("fcntl() failed");
			exit(1);
		}
		printf("[Parent]: File locked.\n");

		read(fp_d, buf, SIZE);
		buf[sizeof(buf)-1] = '\0';
		printf("[Parent]: %s", buf);

		exit(0);  // unlocked
	} else {
		printf("[Child]: Process will lock [%s]\n", TARGET_FILE);
		fc_lock.l_type = F_WRLCK;
		fc_lock.l_whence = SEEK_SET;
		fc_lock.l_start = 0;
		fc_lock.l_len = 0;

		if ((fc_d = open(TARGET_FILE, O_RDWR | O_CREAT, 
				0666)) == -1) {
			perror("open() failed");
			exit(1);
		}

		if (fcntl(fc_d, F_SETLK, &fc_lock) == -1) {
			perror("fcntl() failed");
			exit(1);
		}
		printf("[Child]: File locked.\n");

		write(fc_d, "This is child process's message.\n", 34);
		printf("[Child]: File write complete.\n");

		exit(0);  // unlocked
	}

	exit(0);
}

