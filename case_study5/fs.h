/* fs.h
* Various definitions for OSP Practical Case Study E
* 
* Dr Evan Crawford (e.crawford@westernsydney.edu.au)
* COMP 30015 Operating Systems Programming
* This is the sample file.
*/
#ifndef FS_H
#define FS_H
/* Prevent multiple inclusion with preprocessor guard */
#include<stdint.h>

/* The bitmap */
#define DISKSIZE (851*1024) /* The disk size in bytes */
#define BLOCKSIZE (512) /* The block size */
#define NUMBLOCKS (DISKSIZE/BLOCKSIZE) /* number of blocks on disk */
#define DIR_ENTRIES 16 
extern uint8_t bitmap[NUMBLOCKS/8];

/* The directory entry */
struct entry
{
	int8_t user;
	char name[9];
	char extension[4];
	int16_t blockcount;
	int16_t block[24];
};

/* The Directory */
extern struct entry directory[DIR_ENTRIES];
/* extern here means the variable is defined in another
* file, prevents multiple definition errors
*/

int toggle_bit(int block);
/* Toggles the value of the bit 'block', in  the external array 'bitmap'.
* returns the current value of the bit
*
*  Does NOT validate 'block'!!!
*/

int block_status(int block);
/* Returns the status of 'block', in the external array 'bitmap'
* returns 0 if bitmap bit is 0, not 0 if bitmap bit is 1
*
* Does NOT validate block!!! 
*/

void init_disk();
/* Initialise the disk
*/

void list_files();
/* List the files
*/

#endif