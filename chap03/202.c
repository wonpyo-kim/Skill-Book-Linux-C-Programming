
#include <stdio.h>
#include <stdlib.h>

void main(int argc, char *argv[])
{
	int i;

	if (argc < 2) {
		perror("Usage: Input argument");
		exit(1);
	}

	printf("Number of argument: %d\n", argc);
	for (i = 1; i < argc; i++) {
		printf("Argument %d (argv[%d]): %s\n", i, i, argv[i]);
	}

	printf("\nDetails of arguments.\n");
	for (i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			printf("argv[%d] is a option: %s\n", i, argv[i]);
		} else {
			printf("argv[%d] is a argument: %s\n", i, argv[i]);
		}
	}

	exit(0);
}

