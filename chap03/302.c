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

