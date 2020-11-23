
#include <stdio.h>

#define NUM_DIMS 5
#define NUM_CHARS 8

void get_freq(char *, int *);
void put_hist(int *);

int main(void)
{
	int i;
	char arr[NUM_DIMS][NUM_CHARS] =
		{{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'},
		 {'b', 'b', 'h', 'h', 'h', 'e', 'g', 'a'},
		 {'c', 'f', 'f', 'f', 'f', 'e', 'a', 'c'},
		 {'d', 'd', 'd', 'e', 'a', 'b', 'b', 'b'},
		 {'e', 'e', 'e', 'b', 'b', 'a', 'g', 'g'}};
	int freq[NUM_CHARS] = {0};

	get_freq(arr, freq);
	put_hist(freq);	

	return 0;
}

void get_freq(char *arr, int *freq)
{
	int i, j;

	for (i = 0; i < NUM_DIMS; i++) {
		for (j = 0; j < NUM_CHARS; j++) {
			freq[*(arr+(NUM_CHARS*i)+j)-97]++;
		}
	}

	return;
}

void put_hist(int *freq)
{
	int i, j;

	for (i = 0; i < NUM_CHARS; i++) {
		printf("%c %d ", (i+97), freq[i]);
		for (j = 0; j < freq[i]; j++) {
			printf("*");
		}
		printf("\n");
	}

	return;
}

