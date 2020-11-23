
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_MAX 255

void
main(int argc, char *argv[])
{
	char path[NAME_MAX];
	char *temp = "temp";
	char *target = "303.c";
	DIR *dp;
	struct dirent *dirp;

	if (getcwd(path, NAME_MAX) == NULL) {
		perror("getcwd() failed");
		exit(1);
	}
	printf("\nCurrent directory: %s\n", path);

	if (mkdir(temp, 0755) == -1) {
		perror("mkdir() failed");
		exit(1);
	}

	if (chdir(temp) == -1) {
		perror("chdir() failed");
		exit(1);
	}

	system("/bin/cp ../301.c .");
	system("/bin/cp ../302.c .");
	system("/bin/cp ../303.c .");

	if (chdir("..") == -1) {
		perror("chdir() failed");
		exit(1);
	}

	if ((dp = opendir(temp)) == NULL) {
		perror("opendir() failed");
		exit(1);
	}

	printf("[%s]: ", temp);
	while (dirp = readdir(dp)) {
		printf("%s ", dirp->d_name);
	}
	printf("\n");

	rewinddir(dp);

	printf("[Search]: ");
	while (dirp = readdir(dp)) {
		if (!strcmp(dirp->d_name, target)) {
			printf("%s file in %s\n\n", dirp->d_name, temp);
		}
	}

	closedir(dp);
	
	exit(0);
}

