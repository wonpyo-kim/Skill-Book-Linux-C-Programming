
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 128

void
main(int argc, char *argv[])
{
	pid_t pid;
	int shmfd;
	struct stat st;
	void *shmaddr;
	char *shm_name;
	char buffer[MAX_SIZE];
	
	if (argc != 3 || argv[1][0] != '-') {
		perror("Usage: ./a.out -f <shared memory name>");
		exit(1);
	}

	getopt(argc, argv, "f");

	shm_name = argv[2];

	if ((shmfd = shm_open(shm_name, O_CREAT, 0644)) == -1) {
		perror("shm_open() failed");
		exit(1);
	}

	pid = fork();
	if (pid == -1) {
		perror("fork() failed");
		exit(1);
	} else if (pid != 0) {
		if ((shmfd = shm_open(shm_name, O_RDWR, 0)) == -1) {
			perror("shm_open() failed");
			exit(1);
		}

		strcpy(buffer, "Hello child process");

		if (ftruncate(shmfd, strlen(buffer)) == -1) {
			perror("ftruncate() failed");
			exit(1);
		}
	
		if ((shmaddr = mmap(NULL, MAX_SIZE, PROT_READ | PROT_WRITE, 
				MAP_SHARED, shmfd, 0)) == MAP_FAILED) {
			perror("mmap() failed");
			exit(1);
		}

		memcpy((char *)shmaddr, buffer, strlen(buffer));

		printf("[Parent]: Wait for child...\n");
		wait(NULL);

		if (close(shmfd) == -1) {
			perror("close() failed");
			exit(1);
		}

		if (munmap(shmaddr, MAX_SIZE) == -1) {
			perror("munmap() failed");
			exit(1);
		}

		if (shm_unlink(shm_name) == -1) {
			perror("shm_unlink() failed");
			exit(1);
		}

		printf("[Parent]: Done. Exit.\n");
	} else {
		sleep(0.5);

		if ((shmfd = shm_open(shm_name, O_RDONLY, 0)) == -1) {
			perror("shm_open() failed");
			exit(1);
		}

		if (fstat(shmfd, &st) == -1) {
			perror("fstat() failed");
			exit(1);
		}

		if ((shmaddr = mmap(NULL, st.st_size, PROT_READ,
				MAP_SHARED, shmfd, 0)) == MAP_FAILED) {
			perror("mmap() failed");
			exit(1);
		}

		memcpy(buffer, (char *)shmaddr, st.st_size);
		printf("[Child1]: GET: %s\n", buffer);

		printf("[Child1]: Exit program.\n");
		if (close(shmfd) == -1) {
			perror("close() failed");
			exit(1);
		}
		exit(0);
	}

	exit(0);
}

