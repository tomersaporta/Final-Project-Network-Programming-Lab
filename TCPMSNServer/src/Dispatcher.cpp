/*
 * Dispatcher.cpp
 *
 *  Created on: Jun 26, 2017
 *      Author: user
 */

#include "Dispatcher.h"

namespace networkingLab {

Dispatcher::Dispatcher(DispatcherHandler* handler) {
	this->handler = handler;
	this->stop = false;
	this->newPeerToAdd = NULL;
	this->tcpListener = new MultipleTCPSocketsListener();
	this->fakeSocket = NULL;
	this->init = true;
}

void Dispatcher::startDispatcher() {
	cout << "dispatcher started" << endl;
	//init the demo peer
	this->initFakeSocket();

}

Dispatcher::~Dispatcher() {
	if (this->handler != NULL) {
		delete this->handler;
		this->handler = NULL;
	}
	if (this->tcpListener != NULL) {
		delete this->tcpListener;
		this->tcpListener = NULL;
	}
}

void Dispatcher::addPeer(TCPSocket* peer) {
	if (this->init) {
		//add the new socket

		this->tcpListener->addSocket(peer);
		this->init = false;
		this->start();
	} else {
		this->newPeerToAdd = peer;
		//Interrupt the fake socket
		this->interruptFakeSocket();
	}
}
void Dispatcher::close() {
	this->stop = true;
}

void Dispatcher::handlePeer(TCPSocket* peer) {

	char * buff;
	int cmdNet, cmd, len;
	int rec;
	string ip, strPort;

	bool success = true;
	rec = peer->read((char*) &cmdNet, 4);
	if (rec <= 0)
		success = false;
	cmd = ntohl(cmdNet);

	if (success) {
		switch (cmd) {

		case INTERRUPT_SOCKET: {

			this->tcpListener->addSocket(this->newPeerToAdd);
			cout << "new peer connected: " << newPeerToAdd->getRemotedSocketIP()
					<< ":" << newPeerToAdd->getRemotedSocketPort() << endl;

			break;
		}
		case PLAY_GAME: {
			//cout<<"TEST PLAY GAME"<<endl;
					string ipPort1 = this->getIpPort(peer);
					string name1 = this->handler->getName(ipPort1);
					User* user1 = new User(peer, name1);
					string name2;
					peer->read((char *) &len, sizeof(len));
					len = ntohl(len);
					buff = new char[len];
					peer->read(buff, len);
					for (int i = 0; i < len; i++)
						name2 += buff[i];
					string ipPort2 = this->handler->getIP(name2);
					if(ipPort2.compare("null")==0){
						int cmdList = htonl(NO_USER);
						peer->write((char*) &cmdList, 4);
					}
					else{
					TCPSocket* peer2=this->getPeer(ipPort2);
					User* user2 = new User(peer2, name2);
					this->handler->manageGameSession(user1, user2);
					this->tcpListener->removeSocket(peer);
					this->tcpListener->removeSocket(peer2);
					this->handler->removeUserFromMap(ipPort1, name1);
					this->handler->removeUserFromMap(ipPort2, name2);
					}
					break;
				}
		case RANDOM_USER:{
					string ipPort1 = this->getIpPort(peer);
					string name1 = this->handler->getName(ipPort1);
					User* user1 = new User(peer, name1);
					string name2=this->handler->getRandomName();
					string ipPort2 = this->handler->getIP(name2);
					User* user2 = new User(this->getPeer(ipPort2), name2);
					this->handler->manageGameSession(user1, user2);
					break;
				}

		case NAME_LIST: {

					string names = this->handler->getNames();
					int cmdList = htonl(NAME_LIST);
					peer->write((char*) &cmdList, 4);
					int len = names.length();
					int length = htonl(len);
					peer->write((char*) &length, 4);
					peer->write(names.c_str(), len);
					break;
				}
		case TOP_SCORE:{
					//write back to the client the getting string
					int cmdList = htonl(TOP_SCORE);
					peer->write((char*) &cmdList, 4);
					string highScoreList = this->handler->getHighScoreList();
					int length=  htonl(highScoreList.length());
					peer->write((char*) &length, 4);
					peer->write(highScoreList.c_str(), highScoreList.length());

					break;
				}

		case EXIT: {
			this->tcpListener->removeSocket(peer);
			peer->close();
			break;
		}
		default: {
			break;
		}

		}
	}

}

void Dispatcher::interruptFakeSocket() {
	int cmd = htonl(INTERRUPT_SOCKET);
	int rec = this->fakeSocket->write((char*) &cmd, 4);
	if (rec < 4)
		perror("ERROR INTERRUPT_SOCKET Failed");

}

void Dispatcher::initFakeSocket() {
	this->fakeSocket = new TCPSocket("127.0.0.1", MSNGR_PORT);

}

void Dispatcher::run() {
	TCPSocket * aPeer;
	while (!stop) {
		//Blocking call
		aPeer = this->tcpListener->listenToSocket();
		this->handlePeer(aPeer);
	}
}
string Dispatcher::getPeersList() {
	string s = this->tcpListener->getPeerList();
	return s;
}

string Dispatcher::getListNames() {
	return this->handler->getNames();
}

TCPSocket* Dispatcher::getPeer(string ipPort) {
	int port;
	string ip = ipPort.substr(0, ipPort.find(":"));
	string strPort = ipPort.substr(ipPort.find(":")+1, ipPort.length());
	sscanf(strPort.c_str(), "%d", &port);
	TCPSocket* temp=this->tcpListener->searchSocket(port, ip);
	return temp;

}

void Dispatcher::startGame(User* user1, User* user2) {
	this->handler->manageGameSession(user1, user2);
}

string Dispatcher::getIpPort(TCPSocket* peer) {
	string ip = peer->getRemotedSocketIP();
	int port = peer->getRemotedSocketPort();
	string sPort = "";
	ostringstream convert;
	convert << port;
	sPort = convert.str();
	string ipPort = ip + ":" + sPort;
	return ipPort;
}

void Dispatcher::removePeerFromListner(TCPSocket* peer) {
	cout<<"removePeerFromListner"<<endl;
	this->tcpListener->removeSocket(peer);
}

} /* namespace networkingLab */


