
/* fs.c
* Some useful functions for OSP Practical Case Study E
*
* Dr Evan Crawford (e.crawford@westernsydney.edu.au)
* COMP 30015 Operating Systems Programming
* This is the sample file.
*/
#include"fs.h"
#include<stdio.h>
#include<string.h>

uint8_t bitmap[NUMBLOCKS/8];
struct entry directory[DIR_ENTRIES];
int open_file = -1;

int toggle_bit(int block)
{
	int elem = block / 8;
	int pos  = block % 8;
	int mask = 1 << pos;

	bitmap[elem] ^= mask;

	return bitmap[elem] & mask;
}


int block_status(int block)
{
	int elem = block / 8;
	int pos = block % 8;
	int mask = 1 << pos;

	return bitmap[elem] & mask;
}  

void init_disk() {
	// Set all to unowned
	for (int i = 0; i < DIR_ENTRIES; i++) {
		directory[i].user = -1;
	}

	// Also need to reinit disk? - does this mean set bitmap back to all 0?

	/* why must these be marked*/
	for (int i = 0; i < 2; i++) {
		toggle_bit(i);
	}
	

}

void list_files() {
	int something_found = -1;

	for (int i = 0; i < DIR_ENTRIES; i++) {
		if (directory[i].user != -1) {
			something_found = 1;
			printf("file: %s.%s size: %d blocks\r\n", directory[i].name, directory[i].extension, directory[i].blockcount);
		}
	}

	if (something_found == -1) {
		printf("No files\r\n");
	}
	printf("\r\n");
}

void print_bitmap(){
	// This shit dont work at all
	for (int i = 0; i < NUMBLOCKS; i++) {
		printf("%d", block_status(i) ? 1 : 0);
		if ((i+1) % 8 == 0) {
			printf("  ");
		}
	}
	printf("\r\n");
}

int open_create_file() {
	char name[9], extension[4];
	printf("Enter file name:\r\n");
	scanf("%s", name);
	printf("Enter file extension:\r\n");
	scanf("%s", extension);
				
	// Need to assign file to use and flick first bit on
	int first_empty = -1;

	for (int i = 0; i < DIR_ENTRIES; i++) {
		// While looping dirs we mark which one is the first empty dir
		if (first_empty == -1 && directory[i].user == -1) {
			first_empty = i;
		}
		// If found return file index
		if (directory[i].user != -1 && strcmp(directory[i].name, name) && strcmp(directory[i].extension, extension)){
			return i;
		}
	}

	// Now we init a new file
	printf("File not found.\r\nCreating file: %s.%s\r\n\r\n", name, extension);
	directory[first_empty].user = 1;
	strcpy(directory[first_empty].name, name);
	strcpy(directory[first_empty].extension, extension);
	directory[first_empty].blockcount = 0;


	return first_empty;
}

void write_block_to_file(int file_index) {
	if (directory[file_index].blockcount >= 24) {
		printf("File is full\r\n");
		return;
	}

	// Loop over blocks and find first empty block in bitmap
	for (int i = 0; i < NUMBLOCKS; i++) {
		// if bit == 0 then it is free
		if (block_status(i) == 0) {
			// mark as used
			toggle_bit(i);
			directory[file_index].block[directory[file_index].blockcount] = i;
			directory[file_index].blockcount++;
			return;
		}
	}

	printf("Disk is full\r\n");
}

void read_file(int file_index) {
	printf("file: %s.%s size: %d\r\nblocks: ", directory[file_index].name, directory[file_index].extension, directory[file_index].blockcount);
	for (int i = 0; i < directory[file_index].blockcount; i++) {
		printf("%d, ", directory[file_index].block[i]);
	}
	printf("\r\n");
}

void delete_file(int file_index) {
	for (int i = 0; i < directory[file_index].blockcount; i++) {
		// Loop over block array and turn off all blocks
		toggle_bit(directory[file_index].block[i]);
		directory[file_index].block[i] = 0;
	}
	directory[file_index].blockcount = 0;
	strcpy(directory[file_index].name, "\0");
	strcpy(directory[file_index].extension, "\0");
	directory[file_index].user = -1;
}