
#include <pwd.h>
#include <grp.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

void print_dir(char *target, int opt);
void print_dir_detail(char *target);
void _get_mode(__mode_t st_mode, char *mode);

void
main(int argc, char *argv[])
{
	char *target;
	bool op_mode = false;

	if (argc == 1) {
		target = ".";
	} else if (argc == 2) {
		if (argv[1][0] == '-') {
			target = ".";
			op_mode = true;
		} else {
			target = argv[1];
		}
	} else {
		if (argv[1][0] == '-') {
			target = argv[2];
			op_mode = true;
		} else {
			perror("Usage: ./a.out (-[a|l]) (pathname)");
			exit(1);
		}
	}

	getopt(argc, argv, "al");

	if (op_mode) {
		switch (argv[1][1]) {
		case 'a':
			print_dir(target, 1);
			break;
		case 'l':
			print_dir_detail(target);
			break;
		}
	} else {
		print_dir(target, 0);
	}

	exit(0);
}

void
print_dir(char *target, int opt)
{
	DIR *dp;
	struct dirent *dirp;

	if ((dp = opendir(target)) == NULL) {
		perror("opendir() failed");
		exit(1);
	}

	printf("\n");
	while (dirp = readdir(dp)) {
		if (opt) {
			printf("%s  ", dirp->d_name);
		} else {
			if (strncmp(dirp->d_name, ".", 1)) {
				printf("%s  ", dirp->d_name);
			}
		}
	}
	printf("\n\n");

	closedir(dp);
}

void
print_dir_detail(char *target)
{
	DIR *dp;
	struct dirent *dirp;
	struct stat st;
	char mode[16];
	char time[32];

	if ((dp = opendir(target)) == NULL) {
		perror("opendir() failed");
		exit(1);
	}

	printf("\n");
	while (dirp = readdir(dp)) {
		if (lstat(dirp->d_name, &st) == -1) {
			perror("lstat() failed");
			exit(1);
		}

		_get_mode(st.st_mode, mode);

		sprintf(time, "%s", ctime(&st.st_mtime));
		time[strlen(time)-1] = '\0';

		printf("%s %ld ", mode, st.st_nlink);
		printf("%s %s ", getpwuid(st.st_uid)->pw_name, 
			getgrgid(st.st_gid)->gr_name);
		printf("%8ld %s %s\n", st.st_size, time, dirp->d_name);
	}
	printf("\n");

	closedir(dp);
}

void
_get_mode(__mode_t st_mode, char *mode)
{
	int idx, i;

	idx = i = 0;

	switch (st_mode & S_IFMT) {
	case S_IFIFO:
		mode[idx++] = 'f';
		break;
	case S_IFCHR:
		mode[idx++] = 'c';
		break;
	case S_IFDIR:
		mode[idx++] = 'd';
		break;
	case S_IFBLK:
		mode[idx++] = 'b';
		break;
	case S_IFREG:
		mode[idx++] = '-';
		break;
	}
	
	for (i = 0; i < 3; i++) {
		if (st_mode & (S_IREAD >> i*3)) {
			mode[idx++] = 'r';
		} else {
			mode[idx++] = '-';
		}
		if (st_mode & (S_IWRITE >> i*3)) {
			mode[idx++] = 'w';
		} else {
			mode[idx++] = '-';
		}
		if (st_mode & (S_IEXEC >> i*3)) {
			mode[idx++] = 'x';
		} else {
			mode[idx++] = '-';
		}
	}
	mode[idx] = '\0';
}

