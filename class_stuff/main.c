#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main(int argc, char *argv[]) {
    int i;

    char command[strlen(argv[1])+1];
    strcpy(command, argv[1]);
\
    for (i=0; i<argc; i++) {
        /*command_args[i] = *argv[i];*/
        printf("argv[%i]='%s'\n", i, argv[i]);
    }

    printf("%s", command);
    /* execlp(&command, &command, command_args, NULL); */
    /* execlp("ls", "ls", NULL);*/

    return 0;
}