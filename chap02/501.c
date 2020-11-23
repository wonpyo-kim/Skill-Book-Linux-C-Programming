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

#define NUM_OF_LINUX 4

typedef struct
{
	char name[30];
	char kernel_version[10];
	int disk_space;
} LINUX;

void print_data(LINUX list[]);
void sort_insert(LINUX list[]);

int main(void)
{
	int i;
	LINUX os_list[NUM_OF_LINUX] = 
		{
			{"Ubuntu Server 18.04", "4.4.15", 16},
			{"Ubuntu Desktop 18.04", "4.4.13", 32},
			{"Cent OS 8", "3.15.6", 8},
			{"Fedora", "3.13.26", 40}
		};

	printf("\nPrint struct data\n");
	print_data(os_list);

	sort_insert(os_list);

	printf("\nPrint sorted struct data\n");
	print_data(os_list);

	printf("\n");

	return 0;
}

void print_data(LINUX list[])
{
	int i;

	for (i = 0; i < NUM_OF_LINUX; i++) {
		printf("%s, %s, %dGB\n", list[i].name, 
			list[i].kernel_version, list[i].disk_space);
	}

	return;
}

void sort_insert(LINUX list[])
{
	bool target;
	LINUX temp;
	LINUX *p_current, *p_walker, *p_last;

	p_current = list+1;
	p_last = list + NUM_OF_LINUX-1;

	while (p_current <= p_last) {
		target = false;
		temp = *p_current;

		p_walker = p_current - 1;

		while (p_walker >= list && !target) {
			if (temp.disk_space < p_walker->disk_space) {
				*(p_walker+1) = *p_walker;
				p_walker--;
			} else {
				target = true;
			}
		}
		*(p_walker+1) = temp;
		p_current++;
	}

	return;
}

