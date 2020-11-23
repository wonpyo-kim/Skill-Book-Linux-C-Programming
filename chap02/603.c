
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Node
{
	int data;
	struct Node *next;
} NODE;

typedef struct
{
	NODE *front;
	NODE *rear;
} QUEUE;

bool enqueue(QUEUE *queue, int input);
bool dequeue(QUEUE *queue, int *output);
void print_queue(QUEUE *queue);

int main(void)
{
	QUEUE *queue;
	int select, data;
	char yes = 'y';
	bool result;

	printf("This program tests a queue.\n");

	queue = malloc(sizeof(QUEUE));
	if (!queue) {
		printf("Cannot allocate queue(memory). Abort.\n");
		return -1;
	}
	queue->front = NULL;
	queue->rear = NULL;

	while (!0) {
		printf("1. Enqueue data to queue.\n");
		printf("2. Dequeue data from queue.\n");
		printf("3. Print queue.\n");
		printf("4. Terminate.\n");
		printf("Enter the menu: ");
		scanf("%d", &select);

		if (select == 1) {
			do {
				printf("\nEnqueue data to queue.\n");
				printf("Please enter the key(int): ");
				scanf("%d", &data);
				result = enqueue(queue, data);
				if (result) {
					printf("\nEnqueue completed. Enter y to continue: ");
					scanf(" %c", &yes);
				} else {
					printf("\nFailed to enqueue data.\n\n");
				}
			} while (yes == 'y');
		} else if (select == 2) {
			printf("\nDequeue data from queue.\n");
			result = dequeue(queue, &data);
			if (result) {
				printf("\n[DEQUEUE]: %d\n\n", data);
			} else {
				printf("\nFailed to dequeue data.\n\n");
			}
		} else if (select == 3) {
			printf("\nPrint queue.\n");
			print_queue(queue);
		} else {
			break;
		}
	}

	return 0;
}

bool enqueue(QUEUE *queue, int input)
{
	NODE *new;

	new = (NODE *)malloc(sizeof(NODE));
	if (new) {
		new->data = input;
		new->next = NULL;

		if (queue->front == NULL) {
			queue->front = new;
		} else {
			queue->rear->next = new;
		}
		queue->rear = new;

		return true;
	} else {
		return false;
	}
}

bool dequeue(QUEUE *queue, int *output)
{
	NODE *target;  // target will be deleted from queue.

	if (queue->front == NULL) {
		return false;
	} else {
		*output = queue->front->data;
		target = queue->front;

		if (queue->rear->next != NULL) {
			queue->front = NULL;
			queue->rear = NULL;
		} else {
			queue->front = queue->front->next;
		}

		return true;
	}
}

void print_queue(QUEUE *queue)
{
	int data;

	printf("[QUEUE]: ");
	while (dequeue(queue, &data)) {
		printf("%4d ", data);
	}
	printf("\n\n");

	return;
}

