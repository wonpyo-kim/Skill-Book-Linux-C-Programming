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

