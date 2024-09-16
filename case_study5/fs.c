
/* fs.c
* Some useful functions for OSP Practical Case Study E
*
* Dr Evan Crawford (e.crawford@westernsydney.edu.au)
* COMP 30015 Operating Systems Programming
* This is the sample file.
*/
#include"fs.h"


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

	for (int i = 0; i < DIR_ENTRIES; i++) {
		toggle_bit(i);
	}
}