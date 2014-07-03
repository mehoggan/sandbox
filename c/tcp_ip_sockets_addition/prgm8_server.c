#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <math.h>

int acceptfd;
int socketfd;
int bindfd;
int listenfd;

void catcher(int sig)
{
	printf("Server is closing connection\n");
	close(bindfd);
	close(listenfd);
	close(socketfd);
	close(acceptfd);
	exit(0);
}

int main(int argc, char* argv[])
{
	/*
	 *	Used to retain IP address
	 */
	unsigned char buf[sizeof(struct in6_addr)];
	struct in_addr ipaddress;
	ipaddress.s_addr = inet_addr("192.168.1.1");
	/*
	 *	Used in binding network address to port
	 */
	struct sockaddr_in for_binding = {AF_INET, 7000};// INADDR_ANY};
	for_binding.sin_addr = ipaddress;
	
	/*
	 *	Establish a handle to make link between processes:
	 *	AF_INET is for IP_vs 4
	 *	SOCK_STREAM is for connection mode
	 *	SOCK_STREAM is also for TCP
	 */
	if((socketfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("Socket end point failed on Server");
		exit(1);
	}

	/*
	 *	Associate the ip address and the port bind them to a socket
	 */
	if((bindfd = bind(socketfd, (struct sockaddr*) &for_binding, sizeof(struct sockaddr_in))) == -1)
	{
		perror("Socket was unable to bind");
		exit(1);
	}
	else
	{
		printf("Bound to - %d:%d\n", for_binding.sin_addr, for_binding.sin_port);
	}

	/*
	 *	Now listen in on that port -> set up to wait for incoming calls
	 */
	if((listenfd = listen(socketfd, 512)) == -1)
	{
		perror("Lietening failed:");
		exit(1);
	}
	else
	{
		printf("Listening on - %d:%d\n", for_binding.sin_addr, for_binding.sin_port);	
	}

	/*
	 *	Create a new socket to handle the specific communication
	 *
	 *
	 *	used to close socket
	 */
	static struct sigaction act;
	act.sa_handler = catcher;
	sigfillset(&(act.sa_mask));
	sigaction(SIGPIPE, &act, NULL);
	
	char c;	
	
	for(;;)
	{
		printf("Waiting for client to bind to new socket\n");
		if((acceptfd = accept(socketfd, NULL, NULL)) == -1)
		{
			perror("Can not accept communication:");
			exit(1);
		}
		if(fork() == 0)
		{
			int num[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
			int total = 0;
			int count = 0;
			int loop;
			int cumulate = 0;
	
			printf("Entering Child: %d\n", getpid());
			while(recv(acceptfd, &c, 1, 0) > 0)
			{
				if(c >= '0' && c <= '9')
				{
					int x = (c - 48);
					num[count] = x;
					//printf("num[%d] = %d\n", count, x);
					count++;	
				}
				else if(c == '\n')
				{
					int power = 0;
					if(count > 0)
					{
						for(loop = count - 1; loop >= 0; loop--)
						{
							cumulate = cumulate + (num[loop] * pow(10.0, (double)power++));  
						}
						total = total + cumulate;
						printf("The total is now: %d\n", total);
						cumulate = 0;
					}
					count = 0;
				}						
				send(acceptfd, &c, 1, 0);
			}
			printf("Child Exited\n");	
		}
	}
	exit(0);
}
