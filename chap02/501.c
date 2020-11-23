
#include <stdio.h>
#include <stdbool.h>

#define NUM_OF_LINUX 4

typedef struct
{
	char name[30];
	char kernel_version[10];
	int disk_space;
} LINUX;

void print_data(LINUX list[]);
void sort_insert(LINUX list[]);

int main(void)
{
	int i;
	LINUX os_list[NUM_OF_LINUX] = 
		{
			{"Ubuntu Server 18.04", "4.4.15", 16},
			{"Ubuntu Desktop 18.04", "4.4.13", 32},
			{"Cent OS 8", "3.15.6", 8},
			{"Fedora", "3.13.26", 40}
		};

	printf("\nPrint struct data\n");
	print_data(os_list);

	sort_insert(os_list);

	printf("\nPrint sorted struct data\n");
	print_data(os_list);

	printf("\n");

	return 0;
}

void print_data(LINUX list[])
{
	int i;

	for (i = 0; i < NUM_OF_LINUX; i++) {
		printf("%s, %s, %dGB\n", list[i].name, 
			list[i].kernel_version, list[i].disk_space);
	}

	return;
}

void sort_insert(LINUX list[])
{
	bool target;
	LINUX temp;
	LINUX *p_current, *p_walker, *p_last;

	p_current = list+1;
	p_last = list + NUM_OF_LINUX-1;

	while (p_current <= p_last) {
		target = false;
		temp = *p_current;

		p_walker = p_current - 1;

		while (p_walker >= list && !target) {
			if (temp.disk_space < p_walker->disk_space) {
				*(p_walker+1) = *p_walker;
				p_walker--;
			} else {
				target = true;
			}
		}
		*(p_walker+1) = temp;
		p_current++;
	}

	return;
}

