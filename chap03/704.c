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
#include <sys/sem.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};
int semid_to_signal;

static void signal_handler(int sig);
static void p(int semid, int where);
static void v(int semid, int where);
static void proc_child(int semid, int where);

void
main(int argc, char *argv[])
{
	int i;
	int n_proc = 4;
	pid_t *pid;
	int semid, semkey;
	union semun semarg;
	struct semid_ds semds;

	if (argc != 3 || argv[1][0] != '-') {
		perror("Usage: ./a.out -k <key>");
		exit(1);
	}
	getopt(argc, argv, "k");

	if (signal(SIGINT, signal_handler) == SIG_ERR) {
		perror("signal() failed");
		exit(1);
	}

	semkey = atoi(argv[2]);
	if ((semid = semget((key_t)semkey, 2, 
			IPC_CREAT | IPC_EXCL | 0644)) == -1) {
		printf("[Parent]: Your key is conflicted. ");
		printf("Process will re-define key as [%d]\n", semkey+1);
		semkey += 1;
		if ((semid = semget((key_t)semkey, 2, 
				IPC_CREAT | 0644)) == -1) {
			perror("semget() failed");
			exit(1);
		}
	}

	semarg.val = 1;
	if (semctl(semid, 0, SETVAL, semarg) == -1) {
		perror("semctl() failed");
		exit(1);
	}
	if (semctl(semid, 1, SETVAL, semarg) == -1) {
		perror("semctl() failed");
		exit(1);
	}

	semid_to_signal = semid;

	pid = (pid_t *)calloc(n_proc, sizeof(pid_t));
	for (i = 0; i < n_proc; i++) {
		if ((pid[i] = fork()) == 0) {
			if (i % 2 == 0) {
				proc_child(semid, 0);
			} else {
				proc_child(semid, 1);
			}
		}
	}

	while (!0) {
		sleep(4);

		semarg.buf = &semds;
		if (semctl(semid, 0, IPC_STAT, semarg) == -1) {
			perror("semctl() failed");
			exit(1);
		}

		semarg.array = calloc(semds.sem_nsems, 
			sizeof(semarg.array[0]));
		if (semctl(semid, 0, GETALL, semarg) == -1) {
			perror("semctl() failed");
			exit(1);
		}

		printf("\n[Parent]: Print semaphore information.\n");
		printf("  -- Changed time:    %s", ctime(&semds.sem_ctime));
		printf("  -- Last operation:  %s", ctime(&semds.sem_otime));
		for (i = 0; i < semds.sem_nsems; i++) {
			printf("  -- PID:             %d\n", 
				semctl(semid, i, GETPID, NULL));
			printf("  -- Waiting for p(): %d\n", 
				semctl(semid, i, GETNCNT, NULL));
			printf("  -- Waiting for v(): %d\n", 
				semctl(semid, i, GETZCNT, NULL));
		}
		printf("\n");
	}

	exit(0);
}

static void
signal_handler(int sig)
{
	if (semctl(semid_to_signal, 0, IPC_RMID, NULL) == -1) {
		perror("semctl() failed");
		exit(1);
	}
	printf("[Parent]: Semaphore is removed.\n");
	printf("[Parent]: Exit program.\n");

	exit(0);
}

static void
p(int semid, int where)
{
	struct sembuf pop;

	pop.sem_num = where;
	pop.sem_op = -1;
	pop.sem_flg = SEM_UNDO;
	if (semop(semid, &pop, 1) == -1) {
		perror("semop() failed");
		exit(1);
	}

	return;
}

static void
v(int semid, int where)
{
	struct sembuf vop;

	vop.sem_num = where;
	vop.sem_op = 1;
	vop.sem_flg = SEM_UNDO;
	if (semop(semid, &vop, 1) == -1) {
		perror("semop() failed");
		exit(1);
	}

	return;
}

static void
proc_child(int semid, int where)
{
	p(semid, where);

	printf("[%5d]: Child: I'm running my job...\n", getpid());
	sleep(5);
	printf("[%5d]: Child: My job is done.\n", getpid());
	
	v(semid, where);

	exit(0);
}

