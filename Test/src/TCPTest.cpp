/*
 * TCPTest.cpp
 *
 *  Created on: May 2, 2017
 *      Author: user
 */

#include "TCPTest.h"


using namespace std;
namespace networkingLab {

TCPTest::TCPTest() {
	// TODO Auto-generated constructor stub

}

TCPTest::~TCPTest() {
	// TODO Auto-generated destructor stub
}

bool TCPTest::test(){


	char msg[100]= "Tomer TCP Test";
	char buffer[100];
	//start() - runnin the server
	this->start();
	//sleep
	sleep(3);
//Create a TCP client
	//new TCP Socket
	TCPSocket *client = new TCPSocket("127.0.0.1", TCPTEST_PORT);
	//writ

	client->write(msg, sizeof(msg));
	//read
	client->read(buffer, sizeof(buffer));

	cout<<"Message from the server:"<<buffer<<endl;
	//close
	client->close();
	delete client;
	//check
	if(strcmp(msg, buffer)==0){
		return true;
	}

	return false;
}
void TCPTest::run(){

	char buffer[100];
	memset((void*)buffer,0,100);
	int rec;

	//The server side

	//open TCP Socket
	TCPSocket *server = new TCPSocket(TCPTEST_PORT);

	//Accept
	TCPSocket * aClient = server->listenAndAccept();

	//rec = aClient->write(std::string(buffer, sizeof(buffer)));
	//read with the new client
	rec= aClient->read(buffer, sizeof(buffer));

	cout<<"Message from the client:"<<buffer<<endl;
	//writ with the new client
	aClient->write(buffer, sizeof(buffer));
	//close

	aClient->close();
	server->close();
	delete server;
	delete aClient;
}

} /* namespace networkingLab */
