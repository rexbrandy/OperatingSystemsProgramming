/* cp1.c -- simple copy program example
 * Dr Evan Crawford (e.crawford@westernsydney.edu.au)
 * COMP 30015 Operating Systems Programming
 * Practical Case Study D
 * This sample file was adapted from:
 * Molay, B. (2003). cp1.c. In Understanding unix/linux programming.
 *           Source Code, Prentice Hall.
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

#define BUFFERSIZE 4096

void create_bak(char *file_path, int file_stmode);
void oops(char *, char *);

int main(int ac, char *av[])
{
	int in_fd;
	int out_fd;
	int n_chars;
	char buf[BUFFERSIZE];

    int src_st_mode;

    struct stat src, dst;
    int src_err, dst_err;

    if (ac != 3){
		fprintf(stderr, "usage: %s source destination\n", *av);
		exit(1);
	}

	if ((in_fd = open(av[1], O_RDONLY)) == -1) {
		oops("Cannot open ", av[1]);
	}
	
	// Get the stats of the src and dst files
    src_err = stat(av[1], &src);
    dst_err = stat(av[2], &dst);

    if (src_err == -1) {
        oops("Error getting src stat", av[1]);
    }
	
	/// if no dst_err then a something exists in the destination
	if (dst_err == 0) {

		// Check if dst file is the same as src file
		if (src.st_ino == dst.st_ino) {
			// if dst inode number and src inode number are the same
			// then it's the same file and we do nothing
			exit(1);
		}
	 
		// S_ISDIR() comes from sys/stat.h
		// checks if dir then true
		if (S_ISDIR(dst.st_mode)) {
			// We need to create the path by using the dir 
			// and appending the file to the end
			char file_path[512];

			// This checks if the last character is /
			// if it is we change it to null ('/0')
			if(strcmp(&av[2][strlen(av[2])-1], "/") == 0) {
				av[2][strlen(av[2])-1] = '\0';
			}

			snprintf(file_path, 512, "%s/%s", av[2], av[1]);

			// Check if there is a file with the same name as the source
			struct stat nf;
    		int nf_err;
			src_err = stat(file_path, &nf);
			if (nf_err == 0) {
				create_bak(file_path, &nf.st_mode);
			}

			if ((out_fd = creat(file_path, src.st_mode)) == -1){
				oops("Cannot creat into directory", av[2]);
			}
		} else {
			// This block is for when there is a dst file and it's not a dir
			// We need to back it up and create the out_fd
		}
	} else {
		// Here the permissions are used from the source file
		// `src.st_mode` = src file permissions
		if ((out_fd = creat(av[2], src.st_mode)) == -1){
			oops("Cannot creat", av[2]);
		}
	}


	// Write to new file here
	while ((n_chars = read(in_fd, buf, BUFFERSIZE)) > 0){
		if (write(out_fd, buf, n_chars) != n_chars){
			oops("Write error to ", av[2]);
		}
	}

	if (n_chars == -1){
		oops("Read error from ", av[1]);
	}

	if (close(in_fd) == -1 || close(out_fd) == -1){
		oops("Error closing files", "");
	}

	return 0;
}

void oops(char *s1, char *s2){
	fprintf(stderr, "Error: %s ", s1);
	perror(s2);
	exit(1);
}

/* This is the backup dest code
-----------------
// File exists make a backup
char new_name[strlen(av[2])+4];
strcat(new_name, av[2]);
strcat(new_name, ".bak");

printf("%s", new_name);
*/

void create_bak(char * file_path, int file_stmode) {
	int bak_in;
	int bak_out;
	int n_chars;
	char bak_buf[BUFFERSIZE];

	char bak[518]; // This is to make new file name
	snprintf(bak, 518, "%s.%s", file_path, ".bak"); 

	if ((bak_in = open(file_path, O_RDONLY)) == -1) {
		oops("Cannot open ", file_path);
	}

	if ((bak_out = creat(bak, file_stmode)) == -1){
		oops("Cannot creat", bak);
	}

	// Write to new file here
	while ((n_chars = read(bak_in, bak_buf, BUFFERSIZE)) > 0){
		if (write(bak_out, bak_buf, n_chars) != n_chars){
			oops("Write error to ", bak);
		}
	}

	if (n_chars == -1){
		oops("Read error from ", bak);
	}

	if (close(bak_in) == -1 || close(bak_out) == -1){
		oops("Error closing files", "");
	}
}