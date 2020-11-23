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

#define SECTION1 1424752
#define SECTION2 2374587
#define SECTION3 3324422
#define SECTION4 4274257
#define SECTION5 4794174
#define SECTION6 6173926
#define SECTION7 7123761
#define SECTION8 9798348
#define SECTION9 14247522

unsigned int check_section(float);
void print_section(unsigned int);

int main(void)
{
	float money_month, money_year;
	int select;
	unsigned int section;

	while (!0) {
		printf("This program checks your income section\n");
		printf("1. Based on salary per month\n");
		printf("2. Based on salary per year\n");
		printf("3. Exit\n");
		printf("Please enter the type: ");
		scanf("%d", &select);

		if (select == 1) {
			printf("Enter your salary per month: ");
			scanf("%f", &money_month);
			if (money_month >= 0) {
				section = check_section(money_month);
				print_section(section);
			} else {
				printf("Invalid salary. try again\n");
				continue;
			}
		} else if (select == 2) {
			printf("Enter your salary per year: ");
			scanf("%f", &money_year);
			if (money_year >= 0) {
				money_month = money_year / 12;
				section = check_section(money_month);
				print_section(section);
			} else {
				printf("Invalid salary. try again\n");
				continue;
			}
		} else {
			break;
		}
		printf("\n\n");
	}
	
	return 0;
}

unsigned int check_section(float salary)
{
	if (salary <= SECTION1) {
		return 1;
	} else if (salary > SECTION1 && salary <= SECTION2) {
		return 2;
	} else if (salary > SECTION2 && salary <= SECTION3) {
		return 3;
	} else if (salary > SECTION3 && salary <= SECTION4) {
		return 4;
	} else if (salary > SECTION4 && salary <= SECTION5) {
		return 5;
	} else if (salary > SECTION5 && salary <= SECTION6) {
		return 6;
	} else if (salary > SECTION6 && salary <= SECTION7) {
		return 7;
	} else if (salary > SECTION7 && salary <= SECTION8) {
		return 8;
	} else if (salary > SECTION8 && salary <= SECTION9) {
		return 9;
	} else {
		return 10;
	}

	return 0;
}

void print_section(unsigned int section)
{
	switch (section) {
	case 1:
		printf("\nYour section is 1\n");
		break;
	case 2:
		printf("\nYour section is 2\n");
		break;
	case 3:
		printf("\nYour section is 3\n");
		break;
	case 4:
		printf("\nYour section is 4\n");
		break;
	case 5:
		printf("\nYour section is 5\n");
		break;
	case 6:
		printf("\nYour section is 6\n");
		break;
	case 7:
		printf("\nYour section is 7\n");
		break;
	case 8:
		printf("\nYour section is 8\n");
		break;
	case 9:
		printf("\nYour section is 9\n");
		break;
	case 10:
		printf("\nYour section is 10\n");
		break;
	}

	return;
}

