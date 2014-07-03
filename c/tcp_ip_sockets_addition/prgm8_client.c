#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	char c;
	char rc;

	/*
	 *	Used to retain IP address
	 */
	unsigned char buf[sizeof(struct in6_addr)];
	struct in_addr ipaddress;
	ipaddress.s_addr = inet_addr("192.168.1.1");
	/*
	 *	Used in binding to the server
	 */
	struct sockaddr_in server = {AF_INET, 7000};
	server.sin_addr = ipaddress;

	int socketfd;
	int connectfd;
	
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
	 *	Connect clients socket to servers socket
	 */
	if((connectfd = connect(socketfd, (struct sockaddr*) &server, sizeof(struct sockaddr_in))) == -1)
	{
		perror("Socket was unable to connect");
		exit(1);
	}
	else
	{
		printf("Connected to - %d:%d\n", server.sin_addr, server.sin_port);
	}
	
	for(rc = '\n';;)
	{
		if(rc == '\n')
		{
			printf("Input a lower case character: ");
		}
		c = getchar();
		send(socketfd, &c, 1, 0);
		if(recv(socketfd, &rc, 1, 0) > 0)
		{
			if(((!(rc >= '0') || !(rc <= '9')) || rc == '!') && rc != '\n' )
			{	
				printf("Invalid input\n");
				close(socketfd);
				exit(1);
			}
			else
			{
				printf("%c", rc);
			}		
		}
		else
		{
			printf("server has died\n");
			close(socketfd);
			exit(1);
		}
	}
	close(socketfd);	
	exit(0);
}
