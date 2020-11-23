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

