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
#define COPYMODE 0644

int check_file(char *src_file, char *dst_file);
int get_file_permission(char *src_file);
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
    
    src_err = stat(av[1], &src);
    dst_err = stat(av[2], &dst);

    if (src_err == -1) {
        oops("Error getting src stat", av[1]);
    } else if (dst_err == 0 && src.st_ino == dst.st_ino) {
		// if no dst_err then a file exists in the destination
		// if the dst inode number and src inode number are the same
		// then it's the same file and we do nothing
		exit(1);
	}

	// S_ISDIR() comes from sys/stat.h
	// checks iif dir then true
	// if no dst_err then a file exists in the destination
	if (dst_err == 0 && S_ISDIR(dst.st_mode)) {
		char file_path[512];
		printf("%s\r\n\r\n", strrchr(av[1], '/') + 1);

		if ((out_fd = creat(av[2], src.st_mode)) == -1){
			oops("Cannot creat into directory", av[2]);
		}
	} else {
		
		// Here the permissions are used from the source file
		// `src.st_mode` = src file permissions
		if ((out_fd = creat(av[2], src.st_mode)) == -1){
			oops("Cannot creat", av[2]);
		}
	}


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