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

