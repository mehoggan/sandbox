/*
 * TCP_IP_Socket.h
 *
 *  Created on: March 5, 2010
 *      Author: Matthew
 */

#ifndef TCP_IP_SOCKET_H_
#define TCP_IP_SOCKET_H_

#include "includes.h"

class Shape;
class MainWindow;
class Student;

#define MYPORT "3490"  			// the port server sends data to
#define IPADDRESS "www.matthewh.me"	// the server
#define NUMOFCONNECTIONS 1    		// how many pending connections queue will hold

class TCP_IP_Socket
{
public:
	TCP_IP_Socket(MainWindow* hwnd, char* port);
	~TCP_IP_Socket();
	void set_server_ustring(const char* server_domainname);
	void set_serverip_ustring(const char* ip);

	Glib::ustring* get_server_domainname_string();
	Glib::ustring* get_server_ip_string();

	int send_packet(char* packet);
	char receive_packet_login();
	const char* receive_packet_student_queue();

	int send_shape_packet(Shape* shape);
	int send_text_packet(const char* text_packet);

	void recieve_Text_Data(Glib::ustring student, TextView* output);
	void recieve_Draw_Data(int x);

	void set_session(bool SESSION);
private:
	MainWindow* hwnd;
	const char* server_name;
	int socketfd;
	int connectfd;
	Glib::ustring* server_domainname;
	Glib::ustring* server_ip;
	struct addrinfo specs;
	struct addrinfo* results;

	void establish_server_domainname_string(const char* domain_name);
	void establish_server_ip_string();

	bool SESSION;
};

#endif /* TCP_IP_SOCKET_H_ */
