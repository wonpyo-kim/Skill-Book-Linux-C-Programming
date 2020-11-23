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

int main(void)
{
	int select;
	double celcius, kelvin, fahrenheit;

	printf("This program calculates temperature\n");
	
	while (!0) {
		printf("Choose the menu you want\n");
		printf("1. celcius to fahrenheit\n");
		printf("2. celcius to kelvin\n");
		printf("3. fahrenheit to celcius\n");
		printf("4. fahrenheit to kelvin\n");
		printf("5. EXIT\n");
		printf("Choose: ");
		scanf("%d", &select);

		if (select == 1 || select == 2) {
			printf("\nPlease enter celcius : ");
			scanf("%lf", &celcius);
			if (select == 1) {
				fahrenheit = celcius * 9 / 5 + 32;
				printf("Fahrenheit: %.2f\n", fahrenheit);
			} else {
				kelvin = celcius + 273.15;
				printf("Kelvin: %.2f\n", kelvin);
			}
		} else if (select == 3 || select == 4) {
			printf("\nPlease enter fahrenheit : ");
			scanf("%lf", &fahrenheit);
			if (select == 3) {
				celcius = (fahrenheit-32) * 5 / 9;
				printf("Celcius: %.2f\n", celcius);
			} else {
				kelvin = (fahrenheit-32) * 5 / 9 + 273.15;
				printf("Kelvin: %.2f\n", kelvin);
			}
		} else if (select == 5) {
			break;
		} else {
			printf("Wrong menu, try again\n");
		}
		printf("\n");
	}

	return 0;
}


