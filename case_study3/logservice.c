/* logservice.c -- implementation of the log service
 * Dr Evan Crawford (e.crawford@westernsydney.edu.au)
 * COMP 30015 Operating Systems Programming
 * Practical Case Study C
 * This is the sample file
 */
#include "logservice.h"

int logServiceInit()
{
	int id;

	/* TODO: connect to message queue here */

	return id;

}

int logMessage(int serviceId,char *message)
{
	int rv;

	printf("The message is \"%s\"\n", message);

	/* TODO: Validate message length here */

	/* TODO: Send the message */

	return rv;
}
