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
#include <math.h>

int main(void)
{
	int select;
	float a, b, c;
	float x1, x2;
	float discriminant;

	while (!0) {
		printf("This program calculates quadratic equation\n");
		printf("1. Calculates\n");
		printf("2. Exit\n");
		printf("Enter the menu: ");
		scanf("%d", &select);
	
		if (select == 1) {
			printf("Enter the a, b, c: ");
			scanf("%f %f %f", &a, &b, &c);
		
			discriminant = b * b - (4 * a * c);
		
			if (a == 0 && b == 0) {
				printf("\nThe root doesn't exist\n\n");
			} else if (a == 0 && b != 0 && c != 0) {
				x1 = (-1 * c) / b;
				printf("\nThe root is [%f]\n\n", x1);
			} else if (discriminant < 0) {
				printf("\nThe root doesn't have real values\n\n");
			} else {
				x1 = ((-1 * b) + sqrt(b * b - (4 * a * c))) / (2 * a);
				x2 = ((-1 * b) - sqrt(b * b - (4 * a * c))) / (2 * a);
				printf("\nThe root is [%f, %f]\n\n", x1, x2);
			}
		} else {
			break;
		}
	}

	return 0;
}

