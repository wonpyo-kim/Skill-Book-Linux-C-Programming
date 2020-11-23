
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define RANGE 20

void make_random_array(int []);
void print_array(int []);
void swap(int *, int *);
void sort_select(int []);
void sort_bubble(int []);
void sort_insert(int []);

int main(void)
{
	int i;
	int select;
	int arr[RANGE];

	printf("This program sorts array\n");

	while (!0) {
		printf("1. Selection sort\n");
		printf("2. Bubble sort\n");
		printf("3. Insertion sort\n");
		printf("4. Exit\n");
		printf("Choose the menu: ");
		scanf("%d", &select);

		if (select >= 1 && select <= 3) {
			make_random_array(arr);
			printf("Original array: ");
			print_array(arr);

			switch (select) {
			case 1:
				sort_select(arr);
				break;
			case 2:
				sort_bubble(arr);
				break;
			case 3:
				sort_insert(arr);
				break;
			}
		} else {
			break;
		}

		printf("Sorted array  : ");
		print_array(arr);
		printf("\n\n");
	}

	return 0;
}

void make_random_array(int arr[])
{
	int i;

	for (i = 0; i < RANGE; i++) {
		arr[i] = rand() % RANGE;
	}

	return;
}

void print_array(int arr[])
{
	int i;

	for (i = 0; i < RANGE; i++) {
		printf("%2d ", arr[i]);
	}
	printf("\n");

	return;
}

void swap(int *x, int *y)
{
	int temp;

	temp = *x;
	*x = *y;
	*y = temp;
}

void sort_select(int arr[])
{
	int lowest, current, walker;
	
	current = walker = 0;

	while (current < RANGE) {
		lowest = current;
		walker = current+1;

		while (walker <= RANGE) {
			if (arr[walker] < arr[lowest]) {
				lowest = walker;
			}
			walker++;
		}

		swap(&arr[current], &arr[lowest]);
		current++;
	}

	return;
}

void sort_bubble(int arr[])
{
	int current, walker;

	current = walker = 0;

	while (current < RANGE) {
		walker = RANGE;

		while (walker > current) {
			if (arr[walker] < arr[walker-1]) {
				swap(&arr[walker], &arr[walker-1]);
			}
			walker--;
		}

		current++;
	}

	return;
}

void sort_insert(int arr[])
{
	int temp, current, walker;
	bool target;

	current = 1;

	while (current <= RANGE) {
		target = false;
		temp = arr[current];
		walker = current-1;

		while (walker >= 0 && !target) {
			if (temp < arr[walker]) {
				arr[walker+1] = arr[walker];
				walker--;
			} else {
				target = true;
			}
		}

		arr[walker+1] = temp;
		current++;
	}

	return;
}

