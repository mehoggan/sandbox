/*
 * Daemon.h
 *
 *  Created on: March 5, 2010
 *      Author: Matthew
 */

#ifndef DAEMON_H_
#define DAEMON_H_

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include "Tokenizer.h"

using namespace std;

#define MYPORT_DRAW "3490"	// the port users will be connecting to
#define MYPORT_CHAT "3491"
#define IPADDRESS "192.168.1.1"	// ip address of server
#define NUMOFCONNECTIONS 10    	// how many pending connections queue will hold

typedef int SOCKETFD;

class Daemon
{
public:
	Daemon();
	~Daemon();
	int run();
	int login();
	char* draw_data();
	char* chat_data();
	char* access_database();
private:
	char* host;
	struct addrinfo specs_draw;
	struct addrinfo* results_draw; 
	SOCKETFD sockfd_draw;
	SOCKETFD acceptfd_draw;
	int draw_pid;
	struct sockaddr_storage client_info_draw;
	socklen_t addr_size_draw;

	struct addrinfo specs_chat;
	struct addrinfo* results_chat; 
	SOCKETFD sockfd_chat;
	SOCKETFD acceptfd_chat;
	int chat_pid;
	struct sockaddr_storage client_info_chat;
	socklen_t addr_size_chat;

	void test_section();
};

#endif /* DAEMON_H_ */
