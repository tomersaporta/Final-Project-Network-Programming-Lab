/*
 * Login.h
 *
 *  Created on: Aug 27, 2017
 *      Author: user
 */

#ifndef SRC_LOGIN_H_
#define SRC_LOGIN_H_


#include "LoginHandler.h"
#include "TCPSocket.h"
#include "MThread.h"
#include "MultipleTCPSocketsListener.h"

#include "File.h"

#include <hash_map>
#include <iostream>

#include <list>
#include <functional>
#include <string>
#include <map>
#include <stdio.h>
#include <string.h>
#include "ServerProtocol.h"
#include <hash_fun.h>
#include <sstream>



using namespace std;
using namespace __cxx11;


namespace networkingLab {



class Login :public MThread{
private:


	map <string,string> userMap;
	string path;
	File *data;
	TCPSocket* newPeer;
	MultipleTCPSocketsListener *tcpListener;
	list<string> password;
	list<string> user_name;
	LoginHandler * handler;
	bool stop,init_first, init_second;
	TCPSocket* fakeSocket;


	char buffer[1000];//temp rpalce with list or map
	void loadData(string path);
	void interruptFakeSocket();
	void initFakeSocket();
	void saveData();

public:

	void addPeer(TCPSocket* peer);
	void handlePeer(TCPSocket * peer);

	void startLogin();

	//User validatePeer
	void close();
	void run();

	Login(LoginHandler * handler);
	virtual ~Login();
};

}/* namespace networkingLab */
#endif /* SRC_LOGIN_H_ */
