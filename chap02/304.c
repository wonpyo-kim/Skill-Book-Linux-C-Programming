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

#define S_JAN 3
#define S_FEB 6
#define S_MAR 0
#define S_APR 3
#define S_MAY 5
#define S_JUN 1
#define S_JUL 3
#define S_AUG 6
#define S_SEP 2
#define S_OCT 2
#define S_NOV 0
#define S_DEC 2
#define D_JAN 31
#define D_FEB 29
#define D_MAR 31
#define D_APR 30
#define D_MAY 31
#define D_JUN 30
#define D_JUL 31
#define D_AUG 31
#define D_SEP 30
#define D_OCT 31
#define D_NOV 30
#define D_DEC 31

int get_date_start(int);
int get_date_range(int);
void print_month(int);

int main(void)
{
	int select, month;

	printf("This program prints month\n");

	while (!0) {
		printf("1. Print month\n");
		printf("2. Exit\n");
		printf("Choose the menu: ");
		scanf("%d", &select);

		if (select == 1) {
			printf("Enter the month: ");
			scanf("%d", &month);
			if (month < 1 || month > 12) {
				printf("Wrong month. Try again\n");
			} else {
				print_month(month);
			}
		} else {
			break;
		}
	}

	return 0;
}

int get_date_start(int month)
{
	if (month == 1) {
		return S_JAN;
	} else if (month == 2) {
		return S_FEB;
	} else if (month == 3) {
		return S_MAR;
	} else if (month == 4) {
		return S_APR;
	} else if (month == 5) {
		return S_MAY;
	} else if (month == 6) {
		return S_JUN;
	} else if (month == 7) {
		return S_JUL;
	} else if (month == 8) {
		return S_AUG;
	} else if (month == 9) {
		return S_SEP;
	} else if (month == 10) {
		return S_OCT;
	} else if (month == 11) {
		return S_NOV;
	} else if (month == 12) {
		return S_DEC;
	} else {
		printf("get_start_date(): error in month\n");
		return -1;
	}
}

int get_date_range(int month)
{
	if (month == 1) {
		return D_JAN;
	} else if (month == 2) {
		return D_FEB;
	} else if (month == 3) {
		return D_MAR;
	} else if (month == 4) {
		return D_APR;
	} else if (month == 5) {
		return D_MAY;
	} else if (month == 6) {
		return D_JUN;
	} else if (month == 7) {
		return D_JUL;
	} else if (month == 8) {
		return D_AUG;
	} else if (month == 9) {
		return D_SEP;
	} else if (month == 10) {
		return D_OCT;
	} else if (month == 11) {
		return D_NOV;
	} else if (month == 12) {
		return D_DEC;
	} else {
		printf("get_start_range(): error in month\n");
		return -1;
	}
}

void print_month(int month)
{
	int w_counter;
	int walker;
	int date_start = get_date_start(month);
	int date_range = get_date_range(month);

	printf("\n\n      2020 %2d Calendar\n\n", month);
	printf("SUN MON TUE WED THU FRI SAT\n");
	printf("---------------------------\n");

	for (w_counter = 0; w_counter < date_start; w_counter++) {
		printf("    ");
	}
	for (walker = 1; walker <= date_range; walker++) {
		if (w_counter > 6) {
			printf("\n");
			w_counter = 1;
		} else {
			w_counter++;
		}
		printf("%3d ", walker);
	}
	printf("\n---------------------------\n\n\n");

	return;
}

