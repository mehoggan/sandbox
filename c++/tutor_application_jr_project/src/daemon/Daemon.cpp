/*
 * Daemon.cpp
 *
 *  Created on: March 5, 2010
 *      Author: Matthew
 */

#include "Daemon.h"

Daemon::Daemon() {
    memset(&(this->specs_draw), 0, sizeof (this->specs_draw));
    this->specs_draw.ai_family = AF_UNSPEC;  // use IPv4 or IPv6, whichever
    this->specs_draw.ai_socktype = SOCK_STREAM;
    this->specs_draw.ai_flags = AI_PASSIVE;     // fill in my IP for me

    if((getaddrinfo(IPADDRESS, MYPORT_DRAW, &(this->specs_draw), &(this->results_draw))) == -1) {
        fprintf(stderr, "Failed to getinfo\n");
	exit(0);
    }

    if((this->sockfd_draw = socket((this->results_draw)->ai_family, (this->results_draw)->ai_socktype, (this->results_draw)->ai_protocol)) == -1) {
        fprintf(stderr, "Failed to get socket: %s\n", gai_strerror(this->sockfd_draw));
        exit(0);
    }
    
    if((bind((this->sockfd_draw), (this->results_draw)->ai_addr, (this->results_draw)->ai_addrlen)) == -1) {
        fprintf(stderr, "Failed to bind: %s\n", gai_strerror(this->sockfd_draw));
        exit(0);
    }

    if((listen((this->sockfd_draw), NUMOFCONNECTIONS)) == -1) {
        fprintf(stderr, "Failed to listen: %s\n", gai_strerror(this->sockfd_draw));
        exit(0);
    }

/*****************************************************************************************************************************************************/

    memset(&(this->specs_chat), 0, sizeof (this->specs_chat));
    this->specs_chat.ai_family = AF_UNSPEC;  // use IPv4 or IPv6, whichever
    this->specs_chat.ai_socktype = SOCK_STREAM;
    this->specs_chat.ai_flags = AI_PASSIVE;     // fill in my IP for me

    if((getaddrinfo(IPADDRESS, MYPORT_CHAT, &(this->specs_chat), &(this->results_chat))) == -1) {
        fprintf(stderr, "Failed to getinfo\n");
	exit(0);
    }

    if((this->sockfd_chat = socket((this->results_chat)->ai_family, (this->results_chat)->ai_socktype, (this->results_chat)->ai_protocol)) == -1) {
        fprintf(stderr, "Failed to get socket: %s\n", gai_strerror(this->sockfd_chat));
        exit(0);
    }
    
    if((bind((this->sockfd_chat), (this->results_chat)->ai_addr, (this->results_chat)->ai_addrlen)) == -1) {
        fprintf(stderr, "Failed to bind chat: %s\n", gai_strerror(this->sockfd_chat));
        exit(0);
    }

    if((listen((this->sockfd_chat), NUMOFCONNECTIONS)) == -1) {
        fprintf(stderr, "Failed to listen: %s\n", gai_strerror(this->sockfd_chat));
        exit(0);
    }
}

Daemon::~Daemon() {
}

int Daemon::run() {
    const unsigned int BUF_SIZE = 1024;
    char header[256];
    char msg_draw[BUF_SIZE];
    //char msg_chat[BUF_SIZE];
    for(;;) {
    	this->addr_size_draw = sizeof(this->client_info_draw);
	cout << "Waiting for draw connection from client..." << endl;
        if((this->acceptfd_draw = accept((this->sockfd_draw), (struct sockaddr *) &(this->client_info_draw), &addr_size_draw)) == -1) {
            fprintf(stderr, "Failed to accept: %s\n", gai_strerror(this->acceptfd_draw));
            exit(1);
        }
	if( read( this->acceptfd_draw, header, 256 ) == -1 ) {
            fprintf(stderr, "Failed to read initial header: %s\n", gai_strerror(this->acceptfd_draw ) );
	    exit(1);	
	}
	memset( msg_draw,0,BUF_SIZE );
        if( read( this->acceptfd_draw, msg_draw, BUF_SIZE ) == -1 ) {
            fprintf(stderr, "Failed to read username and password: %s \n", gai_strerror(this->acceptfd_draw ) ); 
            exit(1);
        }

	cout << "Just recieved " << msg_draw << endl;

	cout << "Writing to " << this->sockfd_draw << endl;
	unsigned int valid_login = 1;
	if( (write( this->acceptfd_draw, (void*)&valid_login, 1 ) ) < 0 ) {
            fprintf(stderr, "Failed to write\n");
	    exit( 0 );
	}
	
	cout << "Waiting for chat connection from client..." << endl;
	this->addr_size_chat = sizeof(this->client_info_chat);
	if((this->acceptfd_chat = accept((this->sockfd_chat), (struct sockaddr *) &(this->client_info_chat), &addr_size_chat)) == -1) {
		fprintf(stderr, "Failed to accept: %s\n", gai_strerror(this->acceptfd_chat));
		exit(1);
	}

    }
    close( this->acceptfd_draw );
    close( this->acceptfd_chat );
    close( this->sockfd_draw );
    close( this->sockfd_chat );
}

void Daemon::test_section() {
    void* addr;
    char* ipver;
    char ipstr[INET6_ADDRSTRLEN];
    struct addrinfo* slider;
    slider = this->results_draw;
    if (slider->ai_family == AF_INET) {
        struct sockaddr_in *ipv4 = (struct sockaddr_in *)slider->ai_addr;
        addr = &(ipv4->sin_addr);
        ipver = "IPv4";
        //Convert binary ip over to a string readable by humans
        inet_ntop(slider->ai_family, addr, ipstr, sizeof ipstr);
        printf("  %s: %s:%d\n", ipver, ipstr, (int) ntohs(ipv4->sin_port));
    } else {
        struct sockaddr_in6* ipv6 = (struct sockaddr_in6 *)slider->ai_addr;
        addr = &(ipv6->sin6_addr);
        ipver = "IPv6";
        //Convert binary ip over to a string readable by humans
        inet_ntop(slider->ai_family, addr, ipstr, sizeof ipstr);
        printf("  %s: %s:%d\n", ipver, ipstr, (int) ntohs(ipv6->sin6_port));
    }
}
