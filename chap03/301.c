
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1024

void
main(int argc, char *argv[])
{
	int fd_o, fd_c;
	int r_count;
	off_t f_size;
	char *fo_name = "301.txt";
	char *fc_name = "301_copy.txt";
	char buf[SIZE];
	char str[] = 
"There are a variety of substances in the water which \
includes bacteria and parasites that causes various type \
of diseases in both human and animal bodies. Previously, \
the optical microscope was generally used for observing \
and analyzing the water samples in the laboratory.\n";

	printf("\nThis program shows file write and copy.\n\n");

	fd_o = open(fo_name, O_WRONLY | O_CREAT | O_EXCL, 0644);
	if (fd_o == -1) {
		perror("open() failed. File will be deleted");
		if ((fd_o = open(fo_name, O_WRONLY | O_TRUNC)) != -1) {
			printf("Existing file is flushed.\n");
		} else {
			printf("Cannot access a file. Check the permission.\n");
			exit(1);
		}
	}

	if (write(fd_o, str, sizeof(str)) == -1) {
		perror("write() failed");
		exit(1);
	}

	if ((f_size = lseek(fd_o, 0, SEEK_END)) == -1) {
		perror("lseek() failed");
		exit(1);
	}
	printf("\nFile size : %ld bytes.\n", f_size);
	
	close(fd_o);

	if ((fd_c = creat(fc_name, 0644)) == -1) {
		perror("creat() failed");
		exit(1);
	}
	printf("\nNew file created.\n");

	if ((fd_o = open(fo_name, O_RDONLY)) == -1) {
		perror("open() failed");
		exit(1);
	}

	while ((r_count = read(fd_o, buf, SIZE)) > 0) {
		if (write(fd_c, buf, r_count) != r_count) {
			perror("write() failed");
			exit(1);
		}
	}
	printf("\nText copied to %s\n\n", fc_name);

	close(fd_o);
	close(fd_c);

	exit(0);
}

