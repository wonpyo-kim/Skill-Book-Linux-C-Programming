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

void print_menu(void);
void get_numbers(double *, double *);
double add(double, double);
double sub(double, double);
double mul(double, double);
double div(double, double);

int main(void)
{
	int select;
	double x, y;
	double r;

	printf("This program is a calculator\n");

	while (!0) {
		print_menu();

		printf("Select: ");
		scanf("%d", &select);

		if (select >= 1 && select < 5) {
			get_numbers(&x, &y);
			if (select == 1) {
				r = add(x, y);
			} else if (select == 2) {
				r = sub(x, y);	
			} else if (select == 3) {
				r = mul(x, y);
			} else if (select == 4) {
				r = div(x, y);
			}
			printf("Result: %.3f\n", r);
		} else {
			break;
		}
	}

	return 0;
}

void print_menu(void)
{
	printf("\nPlease select menu\n");
	printf("1. Add\n");
	printf("2. Sub\n");
	printf("3. Multiply\n");
	printf("4. Divide\n");
	printf("5. Exit\n");
}

void get_numbers(double *x, double *y)
{
	printf("Enter the x: ");
	scanf("%lf", x);
	printf("Enter the y: ");
	scanf("%lf", y);
}

double add(double x, double y)
{
	return x + y;
}

double sub(double x, double y)
{
	return x - y;
}

double mul(double x, double y)
{
	return x * y;
}

double div(double x, double y)
{
	if (x == 0 || y == 0) {
		return 0.0;
	} else {
		return x / y;
	}
}

