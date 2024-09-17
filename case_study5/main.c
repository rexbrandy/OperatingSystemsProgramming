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

void print_menu(int file_index);

int main(int ac, char**av) {
	// Init disk before anything starts
	init_disk();
	int choice;

	while(1){
		print_menu(open_file);
		scanf("%d", &choice);

		if (open_file == -1) {		
			switch (choice)
			{
			case 1:
				init_disk();
				break;
			case 2:
				list_files();
				break;
			case 3:
				print_bitmap();
				break;
			case 4:
				open_file = open_create_file();
				break;
			default:
				printf("Enter valid choice");
			}
		} else {
			switch (choice)
			{
			case 1:
				open_file = open_create_file();
				break;
			case 3:
				write_block_to_file(open_file);
				break;
			case 5:
				open_file = -1;
				break;
			default:
				printf("Enter valid choice");
			}
		}
	}
	return 0;
}

void print_menu(int file_index) {
	if (file_index == -1) {
		printf("1. Init disk\n"); // Done
		printf("2. List files\n"); // Done
		printf("3. Print bitmap\n"); // Done
		printf("4. Open/Create file\n"); // Done
		printf("Enter your choice: ");
	} else {
		printf("Open File: %s.%s\r\n", directory[file_index].name, directory[file_index].extension);
		printf("1. Open new file\n"); // Test
		printf("2. Read file\n"); // Make
		printf("3. Write file\n"); // Done
		printf("4. Delete File\n"); // Make
		printf("5. Close File\n"); // Done
	}
}