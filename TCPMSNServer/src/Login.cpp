/*
 * Login.cpp
 *
 *  Created on: Aug 27, 2017
 *      Author: user
 */

#include "Login.h"

namespace networkingLab {

networkingLab::Login::Login(LoginHandler* handler) {
	this->stop = false;
	this->newPeer = NULL;
	this->init_first = true;
	this->init_second = false;
	this->path = "password3.txt";
	this->handler = handler;
	this->tcpListener = new MultipleTCPSocketsListener();
	this->data = NULL;
	this->fakeSocket = NULL;

	loadData(path);
}

void networkingLab::Login::handlePeer(TCPSocket* peer) {

	char * buff;
	int cmdNet, cmd, len;
	int rec;
	string user_name = "", password = "";

	bool success = true;
	rec = peer->read((char*) &cmdNet, 4);
	if (rec <= 0)
		success = false;
	cmd = ntohl(cmdNet);

	if (success) {
		switch (cmd) {
		case LOG_IN: {

			peer->read((char *) &len, sizeof(len));
			len = ntohl(len);
			buff = new char[len];
			peer->read(buff, len);
			//get the user name and password from client command
			int i;
			bool readUser = false;
			for (i = 0; i < len; i++) {
				if (buff[i] == ':')
					readUser = true;
				else if (!readUser)
					user_name += buff[i];
				else
					password += buff[i];
			}

			//search the password
			cout << "get from user: " << user_name << " " << password << endl;
			//check hash password
			stringstream str;
			hash<string> hs;
			size_t hash = hs(password);

			string hashedPass;
			str << hash;
			str >> hashedPass;

			auto it = userMap.find(user_name);
			if (it != userMap.end()) {
				cout << "user name: " << user_name << " Succeed!" << endl;
				if (it->second.compare(hashedPass) == 0) { // check password
					this->handler->handleLoginPeer(peer, user_name);
					this->tcpListener->removeSocket(peer);
					cout << "user name password: " << password << " Succeed!"
							<< endl;
					int cmdNet = htonl(LOG_IN_SUCCEESED);
					peer->write((char*) &cmdNet, 4);
					break;
				} else {
					int cmdNet = htonl(LOG_IN_REFUSED_PASSWORD);
					peer->write((char*) &cmdNet, 4);
				}
			}
			int cmdNet = htonl(LOG_IN_REFUSED_USERNAME);
			peer->write((char*) &cmdNet, 4);

			break;
		}
		case INTERRUPT_SOCKET_LOGIN: {
			//cout << " INTERRUPT_SOCKET- LOGIN" << endl;
			this->tcpListener->addSocket(this->newPeer);
			cout << "Login: " << peer->getRemotedSocketIP() << ""
					<< newPeer->getRemotedSocketPort() << endl;
			break;
		}

		case REGISTER: {

			peer->read((char *) &len, sizeof(len));
			len = ntohl(len);
			buff = new char[len];
			peer->read(buff, len);
			//get the user name and password from client command
			int i;
			bool readUser = false;
			for (i = 0; i < len; i++) {
				if (buff[i] == ':')
					readUser = true;
				else if (!readUser)
					user_name += buff[i];
				else
					password += buff[i];
			}

			cout << "get from user: " << user_name << " " << password << endl;
			cout << "Register Succeeded!" << endl;
			// hash password
			stringstream str;
			hash<string> hs;
			size_t hash = hs(password);

			string hashedPass;
			str << hash;
			str >> hashedPass;

			this->userMap[user_name] = hashedPass;

			int cmdNet = htonl(REGISTER_SUCCEESED);
			peer->write((char*) &cmdNet, 4);
			this->handler->handleLoginPeer(peer, user_name);
			this->tcpListener->removeSocket(peer);
			break;
		}

		case INTERRUPT_SOCKET: {
			cout << "INTERRUPT_SOCKET" << endl;
			break;
		}
		default: {
			break;
		}

		}

	}

}

void Login::addPeer(TCPSocket* peer) {
	if (this->init_first) {
		this->tcpListener->addSocket(peer);
		this->init_first = false;
		this->start();
		this->init_second = true;

	} else if (this->init_second) {
		string empty;
		this->handler->handleLoginPeer(peer, empty);
		this->init_second = false;
	} else {
		this->newPeer = peer;
		//Interrupt the fake socket
		this->interruptFakeSocket();
	}

}

void Login::close() {
	saveData();
	this->stop = true;
}

void Login::run() {
	TCPSocket * aPeer;
	while (!stop) {
		//Blocking call
		aPeer = this->tcpListener->listenToSocket();
		this->handlePeer(aPeer);
	}
}

void Login::loadData(string path) {

	ssize_t ret_in;
	this->data = new File(this->path, O_RDONLY);
	//read from file to buffer
	while ((ret_in = read(this->data->socket_fd, &buffer, sizeof(buffer))) > 0) {
		cout << "reading data..." << endl;
	}

	int i = 0;
	std::vector<char*> v;
	char* chars_array = strtok(this->buffer, "\n");
	while (chars_array) {
		v.push_back(chars_array);
		chars_array = strtok(NULL, "\n");
	}
	char*data[v.size() * 2];
	for (size_t n = 0; n < v.size(); ++n) {
		char* subchar_array = strtok(v[n], " ");

		while (subchar_array) {

			data[i] = subchar_array;
			i++;
			subchar_array = strtok(NULL, " ");
		}

	}
	//cout << v.size() << endl;
	for (size_t n = 0; n < v.size() * 2; n += 2) {
		this->userMap[data[n]] = data[n + 1];
	}

//	for (auto it = userMap.begin(); it != userMap.end(); ++it) {
//		std::cout << it->first << "," << it->second << "\n";
//	}

}

void Login::interruptFakeSocket() {
	int cmd = htonl(INTERRUPT_SOCKET_LOGIN);
	int rec = this->fakeSocket->write((char*) &cmd, 4);
	if (rec < 4) {
		perror("ERROR INTERRUPT_SOCKET Failed");
	}

}

void Login::initFakeSocket() {
	this->fakeSocket = new TCPSocket("127.0.0.1", MSNGR_PORT);
}

void Login::startLogin() {
	cout << "Login started" << endl;
	//init the demo peer
	this->initFakeSocket();

}

void Login::saveData() {

	File * saveFile = new File(this->path, O_RDWR | O_CREAT | O_TRUNC);

	for (map<string, string>::const_iterator loop = this->userMap.begin();
			loop != this->userMap.end(); ++loop) {
		string s = loop->first + " " + loop->second + "\n";

		if (saveFile->write(s.data(), s.length()) < 0) {
			cout << "cant write to file " << this->path << endl;
		}
	}
	cout << "file saved: " << this->path << endl;
	saveFile->close();

}

networkingLab::Login::~Login() {
	this->stop = true;

}

}

