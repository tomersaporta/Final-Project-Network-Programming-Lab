/*
 * BrokerMng.cpp
 *
 *  Created on: Jun 26, 2017
 *      Author: user
 */

#include "BrokerMng.h"

namespace networkingLab {

BrokerMng::BrokerMng(BrokerMngHandler* handler) {
	this->handler = handler;
}



void BrokerMng::rleasePeer(TCPSocket* peer,string user_name) {
	this->handler->handleReturnedPeer(peer,user_name);
}

BrokerMng::~BrokerMng() {
	if (this->handler != NULL) {
		delete this->handler;
		this->handler = NULL;
	}
}

void BrokerMng::createGameBroker(User* user1, User* user2) {
	cout << "Playing game " + user1->getName() + " : " + user2->getName()<< endl;
	int cmdNet, len;
	char*buff;
	string answer = "";
	int cmd = htonl(ACCEPT_ANSWER);
	int rec1 = user2->getPeer()->write((char*) &cmd, 4);
	int len1 = user1->getName().length();
	int length = htonl(len1);
	sleep(2);
	int rec2=user2->getPeer()->write((char*) &length, 4);
	int rec3=user2->getPeer()->write(user1->getName().c_str(), len1);

	if (rec1 < 0 || rec2<0 || rec3<0)
		perror("ERROR send accept failed");

	int rec4 = user2->getPeer()->read((char*) &cmdNet, 4);
	int rec5=user2->getPeer()->read((char *) &len, sizeof(len));
	len = ntohl(len);
	buff = new char[len];
	int rec6=user2->getPeer()->read(buff, len);
	if (rec4 < 0 || rec5<0 || rec6<0)
			perror("ERROR read accept answer failed");
	for (int i = 0; i < len; i++) {
		answer += buff[i];
	}
	if (answer.compare("true") == 0){

		Broker* b =new Broker(user1, user2, this);
	}
	else {
		int cmd = htonl(REFUSE_GAME);
		int rec1 = user1->getPeer()->write((char*) &cmd, 4);
		if(rec1<0){
			perror("ERROR send refuse answer failed");
		}
		this->rleasePeer(user1->getPeer(),user1->getName());
		this->rleasePeer(user2->getPeer(),user2->getName());

	}
}
void BrokerMng::saveUsersScore(string userName, int userScore) {
	this->handler->addToHighScore(userName, userScore);
}

} /* namespace networkingLab */

