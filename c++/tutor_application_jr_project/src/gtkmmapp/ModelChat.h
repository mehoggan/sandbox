/*
 * ModelChat.h
 *
 *  Created on: Feb 14, 2010
 *      Author: Matthew
 */

#ifndef MODELCHAT_H_
#define MODELCHAT_H_

#include "includes.h"

class TCP_IP_Socket;
class MainWindow;

class ModelChat
{
public:
	ModelChat();
	ModelChat(MainWindow* hwnd);
	~ModelChat();
    TCP_IP_Socket* get_chat_socket();
    void establish_Socket();
    void delete_Socket();
private:
	MainWindow* hwnd;
	TCP_IP_Socket* chat_socket;
};

#endif /* MODELCHAT_H_ */
