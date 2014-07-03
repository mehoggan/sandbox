/*
 * prgm6.c
 *
 *  Created on: Oct 3, 2009
 *      Author: Matthew
 */
#include "prgm6.h"

#define MSGSIZE 256

pid_t main_pid;

pid_t pid;
pid_t cpid;
int status;

int main(int argc, char* argv[])
{
	argument_count = argc;

	main_pid= getpid();
	int x;

	if(pipe(pipflag) < 0)
	{
		perror("Can't make pipe\n");
	}

	for(x = 0; x < argc; x++)
	{
		 /* Protect the loop from spawning the next child *
		 * with out this i get more than argc children	  */
		if(cpid != -1)
		{
			pid = fork();
		}
		/*	If you take out && cpid != -1 the loop    *
		 * 	continues incrementing x executing all 	  *
		 * 	the processes at once			  */
		if(pid == 0 && cpid != -1)
		{
			dup2(pipflag[1], 1);
			execl("./wc_special", NULL);
			//write(pipflag[1], "Hello World", BUFFER);
		}
		if(pid > 0)
		{
			cpid = wait(&status);
			close(pipflag[1]);
			read(pipflag[0], input, BUFFER);
			printf("Totally from %s", input);
		}
	}
	exit(0);
}
