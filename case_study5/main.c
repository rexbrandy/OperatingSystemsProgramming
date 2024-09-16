/* main.c
 * Driver for OSP Practical Case Study E
 *
 * Dr Evan Crawford (e.crawford@westernsydney.edu.au)
 * COMP 30015 Operating Systems Programming
 * This is the sample file.
 */
#include <stdlib.h>
#include<stdio.h>
/* stdio.h will be found in the system path */
#include"fs.h"
/* fs.h will be found in the local path */



int main(int ac, char**av)
{
	int choice;
	
	while(1){
		printf("1. Init Disk\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		
		switch (choice)
		{
		case 1:
			init_disk();
			printf("Press enter to go back to menu\n");
			getchar();
			system("clear");
			break;
		
		default:
			printf("Enter valid choice");
		}

		return 0;
	}
}