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
#include <stdbool.h>
#include <stdlib.h>

typedef struct
{
	int key;
} DATA;

typedef struct Node
{
	DATA data;
	struct Node *link;
} NODE;

NODE* add_node(NODE *list, NODE *prev, DATA input);
NODE* del_node(NODE *list, NODE *prev, NODE *curr);
bool find_node(NODE *list, NODE **prev, NODE **curr, int target);
void print_node(NODE *list);

int main(void)
{
	NODE *list, *prev, *curr;
	DATA data;
	int select;
	char yes = 'y';

	printf("This program tests linked list.\n");

	list = NULL;

	while (!0) {
		printf("1. Insert data to list\n");
		printf("2. Delete data in list\n");
		printf("3. Search data in list\n");
		printf("4. Print data in list\n");
		printf("5. Terminate\n");
		printf("Enter the menu: ");
		scanf("%d", &select);

		if (select == 1) {
			do {
				printf("\nInsert data to list.\n");
				printf("Please enter the key: ");
				scanf("%d", &data.key);
				if (find_node(list, &prev, &curr, data.key)) {
					printf("Your key is already in list. Try again.\n");
				} else {
					list = add_node(list, prev, data);
				}
				printf("\n[y] to continue, [n] to stop: ");
				scanf(" %c", &yes);
			} while (yes == 'y');
		} else if (select == 2) {
			printf("\nDelete data in list.\n");
			printf("Please enter the key: ");
			scanf("%d", &data.key);
			if (find_node(list, &prev, &curr, data.key)) {
				printf("Key found. Delete node\n\n");
				list = del_node(list, prev, curr);
			} else {
				printf("Cannot found key.\n\n");
			}
		} else if (select == 3) {
			printf("\nSearch data in list.\n");
			printf("Please enter the key: ");
			scanf("%d", &data.key);
			if (find_node(list, &prev, &curr, data.key)) {
				printf("Key found.\n\n");
			} else {
				printf("Canoot found key.\n\n");
			}
		} else if (select == 4) {
			printf("\nPrint data in list.\n[LIST]: ");
			print_node(list);
		} else {
			break;
		}
	}
	
	return 0;
}

NODE* add_node(NODE *list, NODE *prev, DATA input)
{
	NODE *new;
	
	if (!(new = (NODE *)malloc(sizeof(NODE)))) {
		printf("add_node(): Cannot allocate memory.\n");
		return list;
	}

	new->data = input;

	if (prev == NULL) {
		new->link = list;
		list = new;
	} else {
		new->link = prev->link;
		prev->link = new;
	}

	return list;
}

NODE* del_node(NODE *list, NODE *prev, NODE *curr)
{
	if (prev == NULL) {
		list = curr->link;
	} else {
		prev->link = curr->link;
	}
	free(curr);

	return list;
}

bool find_node(NODE *list, NODE **prev, NODE **curr, int target)
{
	bool found = false;

	*prev = NULL;
	*curr = list;

	while (*curr != NULL && target > (*curr)->data.key) {
		*prev = *curr;
		*curr = (*curr)->link;
	}

	if (*curr && target == (*curr)->data.key) {
		found = true;
	}

	return found;
}

void print_node(NODE *list)
{
	NODE *runner;

	runner = list;
	while (runner != NULL) {
		printf("%4d ", runner->data.key);
		runner = runner->link;
	}
	printf("\n\n");

	return;
}

