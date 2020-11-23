/*
 * BSD-3-Clause
 *
 * Copyright (c) 2020 Wonpyo Kim, 
 * Hallym University Software Convergence School, Hongpub. 
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this 
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this 
 *    list of conditions and the following disclaimer in the documentation and/or other 
 *    materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may
 *    be used to endorse or promote products derived from this software without specific 
 *    prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY 
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED 
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 * WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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

