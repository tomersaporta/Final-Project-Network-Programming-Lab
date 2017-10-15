/*
 * Server.cpp
 *
 *  Created on: Jun 26, 2017
 *      Author: user
 */

#include "Server.h"

namespace networkingLab {
Server::Server(int port, ServerHandler* handler) {
	this->handler = handler;
		this->port = port;
		this->stop = false;
		this->serverSocket = NULL;
}

void Server::run() {
	while (!stop) {
		TCPSocket *newPeer = this->serverSocket->listenAndAccept();
		if (newPeer != NULL){
			this->handler->handleConnectedPeer(newPeer);
		}
	}
}

void Server::startServer() {

	this->serverSocket = new TCPSocket(this->port);
	cout << "TCP server binding..." << endl;
	this->start();

}

void Server::close() {
	this->stop = true;
		this->serverSocket->close();
}

Server::~Server() {
	if (this->handler != NULL) {
		delete this->handler;
		this->handler = NULL;
	}
	if (this->serverSocket != NULL) {
		delete this->serverSocket;
		this->serverSocket = NULL;
	}

}

} /* namespace networkingLab */

