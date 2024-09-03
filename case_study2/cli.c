#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<errno.h>

#define MAX_LINE 4096
#define MAX_WORDS MAX_LINE/2
/* a line can have at most MAX_LINE/2 words, why?  2048 bytes max string length in C*/

void tokenize(char *line, char **words, int *nwords);
/* break line into words separated by whitespace, placing them in the
   array words, and setting the count to nwords */

int main()
{
    char line[MAX_LINE], *words[MAX_WORDS], message[MAX_LINE], buff[FILENAME_MAX];
    int cont_loop = 1, nwords=0;


    while(cont_loop)
    {
        /* 
        My CLI shows you the current working dir in the prompt line

        FILENAME_MAX comes from <stdio.h>
        getcwd() - gets current dir and puts it in buff, FILENAME_MAX is the max length of the buff
         */
        getcwd(buff, FILENAME_MAX);
        printf("%s$> ", buff);

        /* read a line of text here and store it in `line`*/
        if (fgets(line, MAX_LINE, stdin) != NULL) {

            /* Remove whitespace from line */
            line[strcspn(line, "\n")] = 0;

            /* tokenize function splits line and places each word into `words` */
            tokenize(line,words,&nwords);

            /* if no words inputted, go to next loop */
            if (nwords == 1 && words[0] == NULL) {
                continue;
            } 
            
            /*
            if inputted cmd is 'exit', leave

            The strcmp() compares two strings character by character.
            If the strings are equal, the function returns 0.
            */         
            if (strcmp(words[0], "exit") == 0) { /* if inputted cmd is 'exit', leave */
                break;
            } else if (strcmp(words[0], "cd") == 0) { /* you can't run `cd` with exec() so we check here before we fork anything */
                chdir(words[1]);
                continue;
            }
 
            /* stdout needs to be flushed to prevent weird behaviour */
            fflush(stdout);

            pid_t pid;
            switch (pid = fork())
            {
            case -1:
                /* if pid -1 - then forking failed */
                perror("Unable to fork.... why?!");
                break;
            
            case 0:
                /* pid 0 - we are in the child */
                if (execvp(words[0], words) < 0) {
                    perror("Command exec error");
                }
                break;
            
            default:
                /* Wheres my kids */
                wait(NULL);
                break;
            }


        } else {
            printf("Error Reading input");
            continue;
        }        
        /* More to do here */

    }
    return 0;
}

/* this function works, it is up to you to work out why! */
void tokenize(char *line, char **words, int *nwords)
{
    *nwords=1;

    for(words[0]=strtok(line," \t\n");
        (*nwords<MAX_WORDS)&&(words[*nwords]=strtok(NULL, " \t\n"));
        *nwords=*nwords+1
        ); /* empty body */
    return;
}
