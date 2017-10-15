/*
 * Broker.cpp
 *
 *  Created on: Jun 26, 2017
 *      Author: user
 */

#include "Broker.h"

namespace networkingLab {

void Broker::run() {
	TCPSocket* aPeer;
	while (!stop) {
		aPeer = this->tcpListen->listenToSocket();
		this->handlePeer(aPeer);
	}
}

Broker::~Broker() {
	// TODO Auto-generated destructor stub
}

void Broker::handlePeer(TCPSocket* peer) {
	char * buff;
	int cmdNet, cmd, len;
	int rec;
	string ip, strPort;
	bool success = true;

	//set the destination peer
	rec = peer->read((char*) &cmdNet, 4);

	if (rec <= 0)
		success = false;
	cmd = ntohl(cmdNet);

	if (success) {
		switch (cmd) {

		case GAME_FINISH: {

			cout << "GAME_FINISH" << endl;
			stringstream strValue;
			int score;
			// get from user 1 name and score
			peer->read((char *) &len, sizeof(len));
			len = ntohl(len);
			buff = new char[len];
			peer->read(buff, len);
			string str = buff;
			//the user is quit in the middle of the game
			if (str.compare("-1") != 0) {
				std::vector<char*> v;
				char* chars_array = strtok(buff, ":");
				while (chars_array) {
					v.push_back(chars_array);
					chars_array = strtok(NULL, ":");
				}

				string userName = v[0];
				strValue << v[1];
				strValue >> score;
				cout << "GAME_FINISH: " << userName << " : " << score << endl;

				this->parent->saveUsersScore(userName, score);

				this->parent->rleasePeer(this->user1->getPeer(),
						this->user1->getName());
				sleep(2);
				this->parent->rleasePeer(this->user2->getPeer(),
						this->user2->getName());
				sleep(2);

			} else {
				cout<<"-1"<<endl;
				this->parent->rleasePeer(this->user1->getPeer(),
						this->user1->getName());
				sleep(2);
				this->parent->rleasePeer(this->user2->getPeer(),
						this->user2->getName());
				sleep(2);

				this->parent->handler->removePeer(peer);

			}

			break;
		}

		default:
			break;
		}

	}

}

int Broker::sendCommand(TCPSocket* destPeer, int cmd, const char* buff) {

	int cmdNet = htonl(cmd);
	int res = destPeer->write((char*) &cmdNet, 4);
	if (res < 4) {
		return -1;
	}
	if (buff != NULL) {
		int len = strlen(buff);
		int lenNet = htonl(len);
		res = destPeer->write((char*) &lenNet, 4);
		if (res < 4) {
			return -1;
		}
		res = destPeer->write(buff, len);
		if (res < len) {
			return -1;
		}
	}
	return res;

}

Broker::Broker(User* user1, User* user2, BrokerMng* parent) {
	this->parent = parent;
	this->user1 = user1;
	this->user2 = user2;
	//cout<<"TESTING THE START BROKER"<<endl;
	this->tcpListen = new MultipleTCPSocketsListener();
	this->stop = false;

	this->tcpListen->addSocket(this->user1->getPeer());
	sleep(2);
	this->tcpListen->addSocket(this->user2->getPeer());

	this->start();
	//cout<<"TESTING THE END BROKER"<<endl;
	this->sendUsersIpPort();
}
string Broker::getIpPort(TCPSocket* peer) {
	string ip = peer->getRemotedSocketIP();
	int port = peer->getRemotedSocketPort();
	string sPort = "";
	ostringstream convert;
	convert << port;
	sPort = convert.str();
	string ipPort = ip + ":" + sPort;
	return ipPort;
}

void Broker::sendUsersIpPort() {
	string ipPortU1 = this->getIpPort(this->user1->getPeer());
	string ipPortU2 = this->getIpPort(this->user2->getPeer());
	string msgTo1 = this->getPort(ipPortU1) + ":" + ipPortU2;
	string msgTo2 = this->getPort(ipPortU2) + ":" + ipPortU1;
	int send1 = this->sendCommand(this->user1->getPeer(), PEER_DATA,
			msgTo1.c_str());
	sleep(1);
	int send2 = this->sendCommand(this->user2->getPeer(), PEER_DATA,
			msgTo2.c_str());
	//cout<<"TESTING THE SEND IPPORT"<<endl;
	if (send1 < 0 || send2 < 0)
		perror("SEND PEER DATA Failed");

}
string Broker::getPort(string ipPort) {
	string strPort = ipPort.substr(ipPort.find(":") + 1, ipPort.length());
	return strPort;
}

} /* namespace networkingLab */

