
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


