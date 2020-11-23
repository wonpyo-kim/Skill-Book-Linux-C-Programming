
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void print_mode(__mode_t st_mode);

void
main(int argc, char *argv[])
{
	struct stat st;

	if (argc != 3 || argv[1][0] != '-') {
		perror("Usage: ./a.out -[a|t|b|i|m] <filename>");
		exit(1);
	}

	getopt(argc, argv, "atbim");

	if (stat(argv[2], &st) == -1) {
		perror("stat() failed");
		exit(1);
	}

	switch (argv[1][1]) {
	case 'a':
		printf("\nPrint all infomations from [%s]\n", argv[2]);
		printf("Device: %ld\n", st.st_dev);
		printf("File serial number: %ld\n", st.st_ino);
		printf("File mode: %d\n", st.st_mode);
		printf("Link count: %ld\n", st.st_nlink);
		printf("UID: %d\n", st.st_uid);
		printf("GID: %d\n", st.st_gid);
		printf("Device number: %ld\n", st.st_rdev);
		printf("Size of file: %ld\n", st.st_size);
		printf("Optimal block size: %ld\n", st.st_blksize);
		printf("512-byte blocks allocated: %ld\n", st.st_blocks);
		printf("Last access: %s", ctime(&st.st_atime));
		printf("Last modification: %s", ctime(&st.st_mtime));
		printf("Last status change: %s\n", ctime(&st.st_ctime));
		break;
	case 't':
		printf("\nLast access: %s", ctime(&st.st_atime));
		printf("Last modification: %s", ctime(&st.st_mtime));
		printf("Last status change: %s\n", ctime(&st.st_ctime));
		break;
	case 'b':
		printf("\nOptimal block size: %ld\n", st.st_blksize);
		printf("512-byte blocks allocated: %ld\n\n", st.st_blocks);
		break;
	case 'i':
		printf("\nUID: %d\n", st.st_uid);
		printf("GID: %d\n", st.st_gid);
		printf("Device number: %ld\n", st.st_rdev);
		printf("Size of file: %ld\n", st.st_size);
		printf("File mode: %d\n\n", st.st_mode);
		break;
	case 'm':
		printf("\nDetail of file mode: ");
		print_mode(st.st_mode);
		printf("\n");
		break;
	}

	exit(0);
}

void print_mode(__mode_t st_mode)
{
	switch (st_mode & S_IFMT) {
	case S_IFIFO:
		printf("FIFO file\n");
		break;
	case S_IFCHR:
		printf("Character special file\n");
		break;
	case S_IFDIR:
		printf("Directory\n");
		break;
	case S_IFBLK:
		printf("Block special file\n");
		break;
	case S_IFREG:
		printf("Regular file\n");
		break;
	case S_IFLNK:
		printf("Link file\n");
		break;
	case S_IFSOCK:
		printf("Socket file\n");
		break;
	}
}

