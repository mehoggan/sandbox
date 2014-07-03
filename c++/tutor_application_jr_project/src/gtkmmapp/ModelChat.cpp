/*
 * ModelChat.cpp
 *
 *  Created on: Feb 14, 2010
 *      Author: Matthew
 */

#include "ModelChat.h"
#include "TCP_IP_Socket.h"

ModelChat::ModelChat() {

}

ModelChat::ModelChat(MainWindow* hwnd) {
	this->hwnd = hwnd;
	this->chat_socket = NULL;
}

ModelChat::~ModelChat() {

}

TCP_IP_Socket* ModelChat::get_chat_socket() {
	return this->chat_socket;
}

void ModelChat::establish_Socket() {
	const char* chat_port = "3491";
	this->chat_socket = new TCP_IP_Socket(this->hwnd, (char*)chat_port);
	cout << "CONNECTED" << endl;
}

void ModelChat::delete_Socket() {
	if(this->chat_socket != NULL) {
        	cout << "Deleting chat socket " << endl;
		delete this->chat_socket;
	}
}


