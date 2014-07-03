/*
 *  TCP_IP_Socket.cpp
 *
 *  Created on: March 5, 2010
 *      Author: Matthew Hoggan
 */

#include "TCP_IP_Socket.h"
#include "Shape.h"
#include "MainWindow.h"
#include "Student.h"
#include <string.h>

TCP_IP_Socket::TCP_IP_Socket(MainWindow* hwnd, char* port) {
	this->hwnd = hwnd;
	this->establish_server_domainname_string(IPADDRESS);
	memset(&(this->specs), 0, sizeof (this->specs));
	this->specs.ai_family = AF_UNSPEC;  // use IPv4 or IPv6, whichever
   	this->specs.ai_socktype = SOCK_STREAM;
	this->specs.ai_flags = AI_PASSIVE;     // fill in my IP for me
	int status0 = 0;
	if((status0 = getaddrinfo(IPADDRESS, port, &(this->specs), &(this->results))) == -1) {
		fprintf(stderr, "Failed to getinfo: %s\n", gai_strerror(status0));
		exit(0);
	}
	this->establish_server_ip_string();
	if((this->socketfd = socket((this->results)->ai_family, (this->results)->ai_socktype, (this->results)->ai_protocol)) == -1) {
		fprintf(stderr, "Failed to get socket: %s\n", gai_strerror(this->socketfd));
		exit(0);
	}
	if((this->connectfd = connect((this->socketfd), (this->results)->ai_addr, (this->results)->ai_addrlen)) == -1) {
		fprintf(stderr, "Failed to connect: %s\n", gai_strerror(this->connectfd));
		exit(0);
	}
}


TCP_IP_Socket::~TCP_IP_Socket() {
	int eof = EOF;
	int* p_eof = &eof;
	send((this->socketfd), p_eof, 1, 0);
	close(this->socketfd);
	freeaddrinfo(this->results);
}

void TCP_IP_Socket::set_server_ustring(const char* server_name) { this->server_domainname = new ustring(server_name); }
void TCP_IP_Socket::set_serverip_ustring(const char* ip) { this->server_ip = new ustring(ip); }
Glib::ustring* TCP_IP_Socket::get_server_domainname_string() { return this->server_domainname; }
Glib::ustring* TCP_IP_Socket::get_server_ip_string() {  return this->server_ip; }
void TCP_IP_Socket::set_session(bool SESSION) {	this->SESSION = SESSION; }

void TCP_IP_Socket::establish_server_domainname_string(const char* domain_name) {
	this->server_name = domain_name;
	this->set_server_ustring(this->server_name);
}

void TCP_IP_Socket::establish_server_ip_string() {
	char ipstr[INET6_ADDRSTRLEN];
	void* addr;
	if ((this->results)->ai_family == AF_INET) { // IPv4
		struct sockaddr_in* ipv4 = (struct sockaddr_in*)(this->results)->ai_addr;
		addr = &(ipv4->sin_addr);
	} else { // IPv6
		struct sockaddr_in6* ipv6 = (struct sockaddr_in6 *)(this->results)->ai_addr;
		addr = &(ipv6->sin6_addr);
	}
	inet_ntop((this->results)->ai_family, addr, ipstr, sizeof ipstr);
	this->set_serverip_ustring(ipstr);
}

char TCP_IP_Socket::receive_packet_login() {
	void* pckt;
	int pckt_size = 0;
	pckt = (char*)malloc(4);
	if((pckt_size = recv((this->socketfd), pckt, 4, 0)) == 0) {
		fprintf(stderr, "Failed to connect: %s\n", gai_strerror(pckt_size));
	}
	return *((char*)(pckt));
}

int TCP_IP_Socket::send_packet(char* packet) {
	int status;
	size_t size = strlen(packet);
	if((status = send((this->socketfd), packet, size, 0)) == 0) {
		fprintf(stderr, "Failed to send: %s\n", gai_strerror);
	}
	return 0;
}

const char* TCP_IP_Socket::receive_packet_student_queue() {
	void* pckt = NULL;
	void* pckt2 = NULL;
	if(pckt != NULL) {
		memset(&(pckt), 0, sizeof (pckt));
		free(pckt);
	}
	if(pckt2 != NULL) {
		memset(&(pckt), 0, sizeof (pckt2));
		free(pckt2);
	}
	string test("Matthew Hoggan Physicis 2:7:30 Andrew Hamilton Math 24:0:0 Alex David Selebesy 0:0:1 Vahe Margoussian Automata 2:10:23 Daniel Serry Math 2:10:23");
	const char* pckt_test = test.c_str();
	return pckt_test;
}

int TCP_IP_Socket::send_shape_packet(Shape* shape) {
	int rtn = 0;
	char packet[2048];
	sprintf	(
			packet, "%d %f %f %f %f %f %f %f %f %f %f\n", 
			shape->get_type(), shape->get_radius(), shape->get_x(), 
			shape->get_y(), shape->get_x_0(), shape->get_y_0(), 
			shape->get_theta(), shape->get_red(), shape->get_green(), 
			shape->get_blue(), shape->get_sides()
		);
	size_t size = strlen(packet);
	if((rtn = send((this->socketfd), packet, size, 0)) == 0) {
		fprintf(stderr, "Failed to send: %s\n", gai_strerror);
	}
	return rtn;
}

int TCP_IP_Socket::send_text_packet(const char* text_packet) {
	int rtn = 0;
	char packet[2048];
	sprintf(packet, "%s", text_packet);
	strcat(packet, "\n");
	size_t size = strlen(packet);
	if((rtn = send((this->socketfd), packet, size, 0)) == 0) {
		fprintf(stderr, "Failed to send: %s\n", gai_strerror);
	}
	return rtn;
}

void TCP_IP_Socket::recieve_Text_Data(Glib::ustring student, TextView* output) {
	int* pckt;
	while(SESSION) {
		char pckt[4096];
		int pckt_size = 0;
		if((pckt_size = recv((this->socketfd), pckt, 4096, 0)) == 0) {
			fprintf(stderr, "Failed to connect: %s\n", gai_strerror(pckt_size));
		}
		cout << "Just recieved " << pckt << endl;
		Glib::RefPtr<TextBuffer> input = output->get_buffer();
		Glib::ustring input_String = input->get_text(false);
		Glib::ustring post(input_String);
		post.append(student);
		post.append(": ");
		post.append(pckt);
		input->set_text(post);
		memset(&(pckt), 0, 4096);
	}
}

void TCP_IP_Socket::recieve_Draw_Data(int x) {
	cout << "The value passed to draw thread function was " << x << endl;
	int count = 0;
	int* pckt;
	while(SESSION) {
	}
}









