
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


