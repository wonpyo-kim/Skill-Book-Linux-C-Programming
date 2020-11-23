
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define TOP_SPEED 300
#define SPEED_ITER 10
#define SPEED_STEP 30
#define DELAY_FACTOR 10000

typedef struct
{
	char vendor[50];
	unsigned int current_speed;
	unsigned int target_speed;
} CAR;

void init_car(CAR *);
void drive_car(CAR *);
static void move(CAR *);
static void accelerate(CAR *);
static void brake(CAR *);
static void delay(int);

int main(void)
{
	static CAR car;

	init_car(&car);
	drive_car(&car);

	return 0;
}

void init_car(CAR *car)
{
	strcpy(car->vendor, "KIA");
	car->current_speed = 0;
	car->target_speed = 0;

	return;
}

void drive_car(CAR *car)
{
	char buffer[81];
	unsigned int target_speed;
	char *str;

	printf("\nThis program is a car driving program\n");
	printf("You can handle the speed 0 to %d\n", TOP_SPEED);
	printf("Enter the speed and press enter to drive\n");
	printf("EOF or (Ctrl+C) EXIT\n");
	printf("\nEnter the speed: ");

	while (fgets(buffer, 81, stdin)) {
		str = buffer;

		while (*str != '\n') {
			while (*str == ' ') {
				str++;
			}
			if (!isdigit(*str)) {
				printf("Invalid speed. Try again\n");
				str++;
			} else {
				sscanf(str, "%d", &target_speed);
				if (target_speed == car->current_speed) {
					printf("\n\a%d is current speed\n", target_speed);
				} else {
					if (target_speed < 0 || target_speed > TOP_SPEED) {
						printf("Invalid speed, Try again\n");
					} else {
						car->target_speed = target_speed;
						move(car);
					}
				}
				while (isdigit(*str)) {
					str++;
				}
			}
		}
		printf("\nEnter the speed: ");
	}
	

	return;
}

static void move(CAR *car)
{
	if (car->current_speed < car->target_speed) {
		accelerate(car);
	} else {
		brake(car);
	}

	return;
}

static void accelerate(CAR *car)
{
	printf("\nPressing accelerate...\n");

	(car->current_speed)++;
	while (car->current_speed != car->target_speed) {
		(car->current_speed)++;
		delay(500);
	}
	
	printf("Current speed: %d\n", car->current_speed);

	return;
}

static void brake(CAR *car)
{
	printf("\nPressing brake...\n");

	(car->current_speed)--;
	while (car->current_speed != car->target_speed) {
		(car->current_speed)--;
		delay(500);
	}

	printf("Current speed: %d\n", car->current_speed);

	return;
}

static void delay(int t)
{
	int i;

	for (i = 0; i < (t * DELAY_FACTOR); i++);

	return;
}

