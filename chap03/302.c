
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 1024

int read_file_and_print(int fd);

void
main(int argc, char *argv[])
{
	int fd;
	int r_count, f_size = 0;
	char *f_name = "301.txt";
	char buf[SIZE];

	printf("\nThis program reads and changes file size.\n\n");

	if ((fd = open(f_name, O_RDONLY)) == -1) {
		perror("open() failed");
		exit(1);
	}
	f_size = read_file_and_print(fd);
	printf("Original file size: %d bytes.\n\n", f_size);

	close(fd);

	if (truncate(f_name, 100) == -1) {
		perror("truncate() failed");
		exit(1);
	}
	if ((fd = open(f_name, O_RDONLY)) == -1) {
		perror("open() failed");
		exit(1);
	}
	f_size = read_file_and_print(fd);
	printf("Truncated file size: %d bytes.\n\n", f_size);

	close(fd);

	if ((fd = open(f_name, O_RDWR)) == -1) {
		perror("open() failed");
		exit(1);
	}
	if (ftruncate(fd, 50) == -1) {
		perror("ftruncate() failed");
		exit(1);
	}
	f_size = read_file_and_print(fd);
	printf("Ftruncated file size: %d bytes.\n\n", f_size);

	close(fd);

	exit(0);
}

int
read_file_and_print(int fd)
{
	int r_count, f_size = 0;
	char buf[SIZE] = {};

	printf("---------- FILE DATA ----------\n");
	while ((r_count = read(fd, buf, SIZE)) > 0) {
		printf("%s", buf);
		f_size += r_count;
	}
	printf("\n-------------------------------\n");

	return f_size;
}

