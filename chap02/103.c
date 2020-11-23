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

int main(void)
{
	int i = 9411;
	short s = 22;
	bool b = false;
	char c = 'H';
	double d = 255.35;
	float f = 99.9;

	printf("------------------------\n");
	printf("Implicit type conversion\n");
	printf("------------------------\n");
	printf("data: %d, %d, %d, %c, %f, %f\n", i, s, b, c, d, f);
	printf("boolean + character : %c\n", b + c);
	printf("double + char :       %f\n", d + c);
	printf("float + char :        %f\n", f + c);
	printf("short + int :         %d\n", s + i);

	i = i + b;
	f = f + i;
	d = d + f;
	b = -d;

	printf("Calculation result\n");
	printf("i: %d\n", i);
	printf("f: %f\n", f);
	printf("d: %f\n", d);
	printf("b: %d\n", b);

	return 0;
}


