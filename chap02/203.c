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

#define TAX_HOUSE     1   // 1%
#define TAX_INTERIOR  10  // 10%

void get_purchase_information(float *, float *, float *, 
	float *);
void print_receipt(float, float, float, float, float, float, 
	float, float, float);

int main(void)
{
	float house_width, house_length;
	float discount;
	float price_squared_meter;
	float tax_house, tax_interior;
	float price_house, price_interior = 15000000.0;
	float price_house_total, price_interior_total;
	float subtotal, total;
	
	get_purchase_information(&house_width, &house_length, 
		&price_squared_meter, &discount);

	tax_interior = price_interior * (TAX_INTERIOR / 100.0);
	price_interior_total = price_interior + tax_interior;

	price_house = (house_width * house_length) * 
		price_squared_meter;
	tax_house = price_house * (TAX_HOUSE / 100.0);
	price_house_total = price_house + tax_house;

	subtotal = price_interior_total + price_house_total;

	if (discount != 0) {
		total = subtotal - (subtotal * (discount / 100.0));
	} else {
		total = subtotal;
	}

	print_receipt(house_width, house_length, price_interior,
		price_house, tax_interior, tax_house, subtotal, 
		discount, total);

	return 0; 
}

void get_purchase_information(float *house_width, 
	float *house_length, float *price_squared_meter, 
	float *discount)
{
	printf("Width of house (meter) : ");
	scanf("%f", house_width);
	printf("Length of house (meter): ");
	scanf("%f", house_length);
	printf("Price per squared meter: ");
	scanf("%f", price_squared_meter);
	printf("Dealer discount (%%)    : ");
	scanf("%f", discount);

	return;
}

void print_receipt(float house_width, float house_length, 
	float price_interior, float price_house, float tax_interior, 
	float tax_house, float subtotal, float discount, float total)
{
	printf("\n\n-- HOUSE INFORMATION --\n");
	printf("Width : %.2f\n", house_width);
	printf("Length: %.2f", house_length);
	printf("\n\n---------------- RECEIPT ----------------\n");
	printf("Interior:        %20.0f won\n", price_interior);
	printf("House:           %20.0f won\n", price_house);
	printf("Tax of interior: %20.0f won\n", tax_interior);
	printf("Tax of house:    %20.0f won\n", tax_house);
	printf("-----------------------------------------\n");
	printf("Subtotal:        %20.0f won\n", subtotal);
	printf("Discount:        %20.0f %%\n", discount);
	printf("-----------------------------------------\n");
	printf("TOTAL:           %20.0f won\n", total);

	return;
}

