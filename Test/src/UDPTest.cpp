//============================================================================
// Name        : Test.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "UDPTest.h"

namespace networkingLab {


UDPTest::UDPTest() {
	// TODO Auto-generated constructor stub

}

UDPTest::~UDPTest() {
	// TODO Auto-generated destructor stub
}

bool UDPTest::test(){

	char buffer[100];
	memset((void*)buffer,0,100);

	int rec;
	int sec =0;
	//create UDP server
	UDPSocket* server = new UDPSocket(3467);

	//create udp client
	UDPSocket* client =new UDPSocket();
	string msg ="Hello Tomer Test";
	//send a message from the cliemnt to the server
	//client->sendTo(msg, "127.0.0.1", 3467);

	client->connect("127.0.0.1", 3467);
	client->write(msg.c_str(),msg.length());

	// read the message by the server
		//rec = server->recv(buffer, sizeof(buffer));
	rec = server->read(buffer, sizeof(buffer));
	cout<<"send msg:"<<msg.c_str()<<endl;
		//string r = string(buffer);
		cout<<"recv msg:"<<buffer<<endl;
		//cout<<"reply: "<<endl;
		//server->reply(msg);

	// compare the message sent with the message received
		if(strcmp(msg.c_str(), buffer)==0)
			sec=1;

		if(sec){
			client->close();
			server->close();
			return true;
		}
	//close all sockets
		client->close();
		server->close();

	//clear mem
		return false;
}

}


