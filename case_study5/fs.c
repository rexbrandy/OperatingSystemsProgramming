
/* fs.c
* Some useful functions for OSP Practical Case Study E
*
* Dr Evan Crawford (e.crawford@westernsydney.edu.au)
* COMP 30015 Operating Systems Programming
* This is the sample file.
*/
#include"fs.h"
#include<stdio.h>

uint8_t bitmap[NUMBLOCKS/8];
struct entry directory[DIR_ENTRIES];

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
	for (int i = 0; i < DIR_ENTRIES; i++) {
		if (directory[i].user != -1) {
			printf("%s.%s\r\n", directory[i].name, directory[i].extension);
		}
	}
}

void print_bitmap(){
	// This shit dont work at all
	for (int i = 0; i < NUMBLOCKS; i++) {
		printf("%d", block_status(i) ? 1 : 0);
		if ((i+1) % 8 == 0) {
			printf("\r\n");
		}
	}
	printf("\r\n");
}