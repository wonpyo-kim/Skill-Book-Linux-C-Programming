
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void *thread_func(void *arg);

void
main(int argc, char *argv[])
{
	pthread_t tid;
	void *ret;
	int s;

	if ((s = pthread_create(&tid, NULL, thread_func, "Hello World\n")) != 0) {
		perror("pthread_create() failed");
		exit(1);
	}

	printf("Message from main()\n");
	if ((s = pthread_join(tid, &ret)) != 0) {
		perror("pthread_join() failed");
		exit(1);
	}

	printf("Thread returned %ld\n", (long)ret);

	exit(0);
}

static void *
thread_func(void *arg)
{
	char *s = (char *)arg;

	printf("%s", s);

	return (void *)strlen(s);
}

