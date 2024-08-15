/* logserver.c -- implementation of the log server
 * Dr Evan Crawford (e.crawford@westernsydney.edu.au)
 * COMP 30015 Operating Systems Programming
 * Practical Case Study C
 * This is the sample file
 */
#include <signal.h>
#include "logservice.h"

int queue_id; /* stores queue_id for use in signal handler */

void handler(int sig);


int main()
{
	printf("Please make me useful!\n");
	exit(0); /* delete this line once you start */

	/* TODO: initialise the message queue here */

	/* install signal handler to clean up queue
	 * do this after you have created the queue
	 * then you dont need to check if it is valid!
	 */
	signal(SIGINT, handler);


	while (1)
	{
		/* TODO: receive a message */

		/* TODO: display the message */

	}

	return 0;
}


void handler(int sig)
{
	/* TODO: clean up the queue here */

	exit(0);

}
