/*
 * MultipleTCPSocketsListenerTester.cpp
 *
 *  Created on: May 22, 2017
 *      Author: Tomer Saporta
 */


#include "MultipleTCPSocketsListenerTester.h"



namespace networkingLab {

MultipleTCPSocketsListenerTester::MultipleTCPSocketsListenerTester() {
	this->testFail = false;
	// create the server sockets
			for (int i=0;i<TEST_SIZE;i++){
				TCPSocket* newSock = new TCPSocket(MTCPSL_PORT+i);
				this->serverSockets.push_back(newSock);
			}

}

MultipleTCPSocketsListenerTester::~MultipleTCPSocketsListenerTester() {
	//close and delete all server sockets
			for (int i=0;i<TEST_SIZE;i++){
				serverSockets[i]->close();
				delete serverSockets[i];
			}
}

void MultipleTCPSocketsListenerTester::run() {

	//the test loop
	for (int j = 0; j < TEST_SIZE; j++) {
		//create a MultipleTCPSocketsListener and add the sockets to it
		MultipleTCPSocketsListener multiTCPSockLis;
		multiTCPSockLis.addSockets(serverSockets);

		//use MultipleTCPSocketsListener to find the socket that is ready
		TCPSocket* readySocket = multiTCPSockLis.listenToSocket();

		//perform listen and accept on the ready socket
		TCPSocket* aClient = readySocket->listenAndAccept();

		if (aClient != NULL) {
			char buffer[1024];
			memset((void*) buffer, 0, sizeof(buffer));
			int len;

			//receive the incoming message
			int rec = aClient->read((char*) &len, 4); // message size
			if(rec<0){
				perror("ERROR receive message length - server side");
			}

			len = ntohl(len);

			rec = aClient->read(buffer, len);
			if(rec<0){
				perror("ERROR receive message - server side");
			}

			cout << "receive message:" << buffer << endl;

			//compare the incoming message to the global message var
			if (rec != (int)this->message.length()) {
				perror("FAIL1: receive different message length - server side");
				testFail = true;
			}
			if (message != buffer) {
				perror("FAIL2: receive different message- - server side");
				testFail = true;
			}
			//create a new message
			this->message = "Hello!";
			cout << "sending message:" << message << endl;
			len = htonl(message.length());

			// send the message back to the client
			aClient->write((char*) &len, sizeof(len));
			aClient->write(message.data(), message.length());
		}

		//close and delete the new peer socket
		aClient->close();
		delete aClient;

	}
	cout << "Multiple TCPSockets Listener ended " << endl;
}

void MultipleTCPSocketsListenerTester::createClientAndSendRecvMsg(int port){
	//create client TCP socket named cSocket

	TCPSocket* cSocket = new TCPSocket("127.0.0.1",port);
	// this part test the send methods
		this->message = "Tomer Saporta";
		cout<<"sending message:"<<message<<endl;

		int len = htonl(message.length());

		cSocket->write((char*) &len, 4);
		cSocket->write(message.data(), message.length());

	char buffer[1024];
	memset((void*)buffer,0,sizeof(buffer));

	MultipleTCPSocketsListener multiTCPSockLis;
	multiTCPSockLis.addSocket(cSocket);

	for (int i=0;i<1;i++){
		TCPSocket* readtCSocket = multiTCPSockLis.listenToSocket();
		readtCSocket->read((char*)&len,4);
		len = ntohl(len);
		int rc = readtCSocket->read(buffer, len);
		cout<<"receive message:"<<buffer<<endl;
		if (rc != message.length()){
			perror("FAIL1: receive different message length - client side");
			testFail = true;
		}
		if (message != buffer){
			perror("FAIL2: receive different message - client side");
			testFail = true;
		}
	}
	cout<<"client closing"<<endl;
	cSocket->close();
	cout<<"test completed"<<endl;
}




bool MultipleTCPSocketsListenerTester::test() {

	//create server socket named sSocket
		testFail = false;
		//int port = 55555;
		// create and start the server part
		TCPSocket* tcpServer = new TCPSocket(MTCPSL_PORT);
		this->start();
		sleep(2);//give a chance for the TCP server to start

		//call the client test TEST_SIZE times
		for (int i=0;i<TEST_SIZE;i++){
			cout << "testing client #" <<i<< endl;
			createClientAndSendRecvMsg(MTCPSL_PORT+i);
		}

		//wait for the server to close and delete it
		this->waitForThread();
		delete tcpServer;

		//check if there where any failures
		if (testFail){
			return false;
		}else{
			return true;
		}
	}


} /* namespace networkingLab */


