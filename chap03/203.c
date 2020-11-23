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

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void    get_numbers    (double *x, double *y);
double  addition       (double x, double y);
double  substraction   (double x, double y);
double  multiplication (double x, double y);
double  division       (double x, double y);

void
main(int argc, char *argv[])
{
	int opt;
	double x, y, r;

	if (argc != 2 || argv[1][0] != '-') {
		perror("Usage: ./a.out -a -s -m -d");
		exit(1);
	}

	while ((opt = getopt(argc, argv, "asmd")) != -1) {
		if (opt != '?') {
			get_numbers(&x, &y);
		} else {
			exit(1);
		}
	}

	switch (argv[1][1]) {
	case 'a':
		r = addition(x, y);
		break;
	case 's':
		r = substraction(x, y);
		break;
	case 'm':
		r = multiplication(x, y);
		break;
	case 'd':
		r = division(x, y);
		break;
	}
	printf("Result: %.3f\n", r);

	exit(0);
}

void
get_numbers(double *x, double *y)
{
	printf("Enter the number x: ");
	scanf("%lf", x);
	printf("Enter the number y: ");
	scanf("%lf", y);
}

double
addition(double x, double y)
{
	return x + y;
}

double
substraction(double x, double y)
{
	return x - y;
}

double
multiplication(double x, double y)
{
	return x * y;
}

double
division(double x, double y)
{
	if (x == 0 || y == 0) {
		return 0.0;
	} else {
		return x / y;
	}
}

