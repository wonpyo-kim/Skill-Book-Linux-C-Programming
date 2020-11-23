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
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
main(int argc, char *argv[])
{
	int i;
	uid_t uid;
	gid_t gid;
	struct passwd *pw;
	struct group *gr;

	printf("This program shows your information.\n");

	uid = getuid();
	if ((pw = getpwuid(uid)) == NULL) {
		perror("getpwuid()");
		exit(1);
	}
	printf("User name : %s, UID: %d, GID: %d, HOME: %s\n", 
		pw->pw_name, pw->pw_uid, pw->pw_gid, pw->pw_dir);
	
	gid = getgid();
	if ((gr = getgrgid(gid)) == NULL) {
		perror("getgrgid()");
		exit(1);
	}
	printf("Group name: %s, GID: %d\n", gr->gr_name, gr->gr_gid);

	do {
		if ((gr = getgrent()) != NULL) {
			for (i = 0; gr->gr_mem[i] != NULL; i++) {
				if (!strcmp(pw->pw_name, gr->gr_mem[i])) {
					printf("%d(%s) ", gr->gr_gid, gr->gr_name);
				}
			}
		}
	} while (gr != NULL);
	printf("\n");

	exit(0);
}

