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

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void
main(int argc, char *argv[])
{
	sigset_t mask;

	if (argc != 3 || argv[1][0] != '-') {
		perror("Usage: ./a.out -[a|d] <signal number>");
		exit(1);
	}

	getopt(argc, argv, "ad");

	switch (argv[1][1]) {
	case 'a':
		if (sigemptyset(&mask) == -1) {
			perror("sigemptyset() failed");
			exit(1);
		}
		if (sigaddset(&mask, atoi(argv[2])) == -1) {
			perror("sigaddset() failed");
			exit(1);
		}
		if (sigismember(&mask, atoi(argv[2]))) {
			printf("%s is a signal(inserted).\n", argv[2]);
		} else {
			printf("%s is not a signal.\n", argv[2]);
		}
		break;
	case 'd':
		if (sigfillset(&mask) == -1) {
			perror("sigfillset() failed");
			exit(1);
		}
		if (sigdelset(&mask, atoi(argv[2]))) {
			perror("sigdelset() failed");
			exit(1);
		}
		if (sigismember(&mask, atoi(argv[2]))) {
			printf("%s is a signal.\n", argv[2]);
		} else {
			printf("%s is not a signal(deleted).\n", argv[2]);
		}
		break;
	}

	exit(0);
}

