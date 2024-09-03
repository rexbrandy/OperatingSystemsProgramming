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

#define BUFFERSIZE 4096
#define COPYMODE 0644

void oops(char *, char *);
int check_file(char src_file, char dst_file);

int main(int ac, char *av[])
{
	int in_fd;
	int out_fd;
	int n_chars;
	char buf[BUFFERSIZE];

	if (ac != 3)
	{
		fprintf(stderr, "usage: %s source destination\n", *av);
		exit(1);
	}

	if ((in_fd = open(av[1], O_RDONLY)) == -1)
	{
		oops("Cannot open ", av[1]);
	}

	if ((out_fd = creat(av[2], COPYMODE)) == -1)
	{
		oops("Cannot creat", av[2]);
	}

    if (check_file(av[1], av[2])  == -1) {
        oops("Files are the same", "");
    }

	while ((n_chars = read(in_fd, buf, BUFFERSIZE)) > 0)
	{
		if (write(out_fd, buf, n_chars) != n_chars)
		{
			oops("Write error to ", av[2]);
		}
	}

	if (n_chars == -1)
	{
		oops("Read error from ", av[1]);
	}

	if (close(in_fd) == -1 || close(out_fd) == -1)
	{
		oops("Error closing files", "");
	}

	return 0;
}

void oops(char *s1, char *s2)
{
	fprintf(stderr, "Error: %s ", s1);
	perror(s2);
	exit(1);
}

int check_file(char src_file, char dst_file)
{
    // If inode number of files is the same
    // then they are the same file
    struct stat src, dst;
    int src_err, dst_err;
    
    src_err = stat(src_file, &src);
    dst_err = stat(dst_file, &dst);

    if (src.st_ino == dst.st_ino) {
        // if they're the same return -1
        return -1;
    }
    // else return 1
    return 1;
}