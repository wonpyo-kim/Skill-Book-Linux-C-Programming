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

typedef struct Node
{
	int data;
	struct Node *link;
} NODE;

typedef struct
{
	int count;
	NODE *top;
} STACK;

bool push(STACK *stack, int input);
bool pop(STACK *stack, int *output);
void print_stack(STACK *stack);

int main(void)
{
	STACK *stack;
	int select, data;
	char yes = 'n';
	bool result;

	printf("This program tests a stack.\n");

	stack = malloc(sizeof(STACK));
	if (!stack) {
		printf("Canoot allocate stack. Abort.\n");
		return -1;
	}
	stack->top = NULL;
	stack->count = 0;

	while (!0) {
		printf("1. Push data to stack.\n");
		printf("2. Pop data from stack.\n");
		printf("3. Print data in stack. (pop all)\n");
		printf("4. Terminate.\n");
		printf("Enter the menu: ");
		scanf("%d", &select);

		if (select == 1) {
			do {
				printf("\nPush data to stack.\n");
				printf("Please enter the key(int): ");
				scanf("%d", &data);
				result = push(stack, data);
				if (result) {
					printf("\nPush completed. Enter 'y' to continue: ");
					scanf(" %c", &yes);
				} else {
					printf("\nFailed to push data.\n");
				}
			} while (yes == 'y');
		} else if (select == 2) {
			printf("\nPop data from stack.\n");
			result = pop(stack, &data);
			if (result) {
				printf("\n[POP]: %d\n\n", data);
			} else {
				printf("\nFailed to pop data.\n\n");
			}
		} else if (select == 3) {
			printf("\nPrint data in stack.\n");
			print_stack(stack);
		} else {
			break;
		}
	}

	return 0;
}

bool push(STACK *stack, int input)
{
	NODE *new;

	new = (NODE *)malloc(sizeof(NODE));
	if (new) {
		new->data = input;
		new->link = stack->top;
		stack->top = new;
		stack->count++;
		return true;
	} else {
		return false;
	}

	return false;
}

bool pop(STACK *stack, int *output)
{
	NODE *target;  // target will be deleted from stack.

	if (stack->top) {
		*output = stack->top->data;
		target = stack->top;
		stack->top = (stack->top)->link;
		stack->count--;
		free(target);
		return true;
	} else {
		return false;
	}

	return false;
}

void print_stack(STACK *stack)
{
	int data;

	printf("[STACK]: ");
	while (pop(stack, &data)) {
		printf("%4d ", data);
	}
	printf("\n\n");

	return;
}

