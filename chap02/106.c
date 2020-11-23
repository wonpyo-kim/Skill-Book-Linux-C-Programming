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

#define EARNED_INCOME_TAX_RATE     4     // 4%
#define LOCAL_INCOME_TAX_RATE      10    // 10% of EARNED_INCOME TAX
#define NATIONAL_PENSION_RATE      4.5   // 4.5%
#define EMPLOYMENT_INSURANCE_RATE  0.8   // 0.8%
#define HEALTH_INSURANCE_RATE      3.38  // 3.38%

int main(void)
{
	float salary;
	float eit, lit, np, ei, hi;
	float total;

	printf("This program calculates social insurance tax in salary\n");
	printf("Please enter your salary(monthly): ");
	scanf("%f", &salary);

	eit = salary * (EARNED_INCOME_TAX_RATE / 100.0);
	lit = eit * (LOCAL_INCOME_TAX_RATE / 100.0);
	np = salary * (NATIONAL_PENSION_RATE / 100.0);
	ei = salary * (EMPLOYMENT_INSURANCE_RATE / 100.0);
	hi = salary * (HEALTH_INSURANCE_RATE / 100.0);
	total = eit + lit + np + ei + hi;

	printf("Earned income tax:    %10d WON\n", (int)eit);
	printf("Local income tax:     %10d WON\n", (int)lit);
	printf("National pension:     %10d WON\n", (int)np);
	printf("Employment insurance: %10d WON\n", (int)ei);
	printf("Health insurane:      %10d WON\n", (int)hi);
	printf("TOTAL:                %10d WON\n", (int)total);

	return 0;
}


