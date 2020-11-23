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
#include <sys/msg.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 256

struct msgbuf {
	long mtype;
	char mdata[MAX_SIZE];
};

void print_msqinfo(struct msqid_ds mds);

void
main(int argc, char *argv[])
{
	int mid, mkey;
	struct msgbuf p_msg;
	struct msqid_ds p_mds;

	if (argc != 2) {
		perror("Usage: ./a.out <key>");
		exit(1);
	}
	mkey = atoi(argv[1]);

	if ((mid = msgget((key_t)mkey, IPC_CREAT | 0644)) == -1) {
		perror("msgget() failed");
		exit(1);
	}

	p_msg.mtype = 2;
	strcpy(p_msg.mdata, "msgctl() test");
	if (msgsnd(mid, &p_msg, strlen(p_msg.mdata), 0) == -1) {
		perror("msgsnd() failed");
		exit(1);
	}
	printf("Message sent.\n");

	if (msgctl(mid, IPC_STAT, &p_mds) == -1) {
		perror("msgctl() failed");
		exit(1);
	}
	print_msqinfo(p_mds);

	if (msgrcv(mid, &p_msg, MAX_SIZE, 0, 0) == -1) {
		perror("msgrcv() failed");
		exit(1);
	}
	printf("Message received.\n");

	if (msgctl(mid, IPC_STAT, &p_mds) == -1) {
		perror("msgctl() failed");
		exit(1);
	}
	print_msqinfo(p_mds);

	if (msgctl(mid, IPC_RMID, 0) == -1) {
		perror("msgctl() failed");
		exit(1);
	}
	printf("Message queue is removed.\n");

	exit(0);
}

void
print_msqinfo(struct msqid_ds mds)
{
	printf("Print message's information.\n");
	printf("   Permission:           %o\n", mds.msg_perm.mode);
	printf("   Last msgsnd():        %s", ctime(&mds.msg_stime));
	printf("   Last msgrcv():        %s", ctime(&mds.msg_rtime));
	printf("   Last change:          %s", ctime(&mds.msg_ctime));
	printf("   Bytes in queue:       %ld\n", mds.__msg_cbytes);
	printf("   Messages in queue:    %ld\n", mds.msg_qnum);
	printf("   Max bytes in queue:   %ld\n", mds.msg_qbytes);
	printf("   PID of last msgsnd(): %d\n", mds.msg_lspid);
	printf("   PID of last msgrcv(): %d\n\n", mds.msg_lrpid);

	return;
}

