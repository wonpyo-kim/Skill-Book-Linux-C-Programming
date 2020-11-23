
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

