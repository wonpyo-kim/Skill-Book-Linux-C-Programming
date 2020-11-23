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

