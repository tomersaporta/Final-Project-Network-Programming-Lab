/*
 * TCPMSNClient.cpp
 *
 *  Created on: Jun 11, 2017
 *      Author: user
 */

#include "TCPMSNClient.h"
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

namespace networkingLab {

TCPMSNClientHandler::TCPMSNClientHandler() {
	this->sdk = new TCPMSNClient();
	this->sdk->setHandler(this);
}
TCPMSNClient* TCPMSNClientHandler::getSDK() {
	return this->sdk;
}

TCPMSNClient::TCPMSNClient() {
	this->handler = NULL;
	this->UDPMsg = NULL;
	client = NULL;
	this->isConnected = true;

}

void TCPMSNClient::setHandler(TCPMSNClientHandler * handler) {
	this->handler = handler;
}
TCPMSNClient::~TCPMSNClient() {

}

bool TCPMSNClient::connect(string ip) {
	client = new TCPSocket(ip, (size_t) MSNGR_PORT);
	if (this->client->socket_fd < 0)
		return false;
	this->start();
	return true;
}

bool TCPMSNClient::openSession(string ip, int port) {
	char buff[100];
	sprintf(buff, "%s:%d", ip.c_str(), port);
	int rec = sendCommand(OPEN_SESSION_WITH_PEER, buff);
	if (rec < 0)
		perror("ERROR send OPEN_SESSION_WITH_PEER to server");
	return rec > -1;

}

bool TCPMSNClient::login(string user_name, string password) {
	string s = user_name + ":" + password;
	int rec = sendCommand(LOG_IN, s.data());
	if (rec < 0)
		perror("ERROR send LOG_IN to server");
	return rec > -1;

}

bool TCPMSNClient::registering(string user_name, string password) {

	string s = user_name + ":" + password;
	int rec = sendCommand(REGISTER, s.data());
	if (rec < 0)
		perror("ERROR send REGISTER to server");
	return rec > -1;

}

void TCPMSNClient::sendMessage(string msg) {
	int rec = sendCommand(SEND_MSG_TO_PEER, msg.data());
	if (rec < 0)
		perror("ERROR send SEND_MSG_TO_PEER  to server");

}

void TCPMSNClient::closeSession() {
	int rec = sendCommand(CLOSE_SESSION_WITH_PEER, NULL);
	if (rec < 0)
		perror("ERROR send CLOSE_SESSION_WITH_PEER  to server");
}

void TCPMSNClient::disconnect() {
	if (this->isConnected) {
		int rec = sendCommand(EXIT, NULL);
		if (rec < 0) {
			perror("ERROR send EXIT to server");
		}
		this->isConnected = false;
	}
}

void TCPMSNClient::exit() {


	if(this->UDPMsg!= NULL){
	this->UDPMsg->close();
	}
	string s  ="-1";
	this->sendCommand(GAME_FINISH, s.c_str());
	this->client->close();
	delete this->client;
}

int TCPMSNClient::getPort() {
	struct sockaddr_in s_in;
	socklen_t len = sizeof(s_in);
	getsockname(client->socket_fd, (struct sockaddr *) &s_in, &len);
	return ntohs(s_in.sin_port);

}
void TCPMSNClient::run() {
	while (this->isConnected) {
		this->recvCommand();
	}
}

int TCPMSNClient::sendCommand(int cmd, const char* buff) {
	int cmdNet = htonl(cmd);
	int res = client->write((char*) &cmdNet, 4);
	if (res < 4) {
		return -1;
	}
	if (buff != NULL) {
		int len = strlen(buff);
		int lenNet = htonl(len);
		res = client->write((char*) &lenNet, 4);
		if (res < 4) {
			return -1;
		}
		res = client->write(buff, len);
		if (res < len) {
			return -1;
		}
	}
	return res;

}
void TCPMSNClient::recvCommand() {

	char * buff;
	int cmdNet, cmd, len;
	int rec;
	bool success = true;
	rec = client->read((char*) &cmdNet, 4);
	if (rec <= 0)
		success = false;
	cmd = ntohl(cmdNet);

	if (success) {
		switch (cmd) {

		case REGISTER_SUCCEESED: {
			this->handler->onRegisterSuccess();
			cout<<"register succeeded"<<endl;
			break;
		}

		case LOG_IN_REFUSED_PASSWORD: {
			this->handler->onLoginPasswordFailed();
			break;
		}
		case LOG_IN_REFUSED_USERNAME: {
			this->handler->onLoginUserFailed();
			cout<<"login succeeded"<<endl;
			break;
		}
		case LOG_IN_SUCCEESED:{
			this->handler->onLoginSuccess();
			break;
		}

		case NAME_LIST: {
			this->client->read((char *) &len, sizeof(len));
			len = ntohl(len);
			buff = new char[len];
			string list = "";
			this->client->read(buff, len);
			for (int i = 0; i < len; i++)
				list += buff[i];
			this->handler->onGetUsers(list);
			break;
		}
		case TOP_SCORE: {
				this->client->read((char *) &len, sizeof(len));
				len = ntohl(len);
				buff = new char[len];
				string list = "";
				this->client->read(buff, len);
				for (int i = 0; i < len; i++)
					list += buff[i];
				this->handler->onGetTopScore(list);
				break;
			}
		case ACCEPT_ANSWER: {
			cout << "get accept answer" << endl;
			string name = "";
			this->client->read((char *) &len, sizeof(len));
			len = ntohl(len);
			buff = new char[len];
			this->client->read(buff, len);
			for (int i = 0; i < len; i++)
				name += buff[i];
			bool answer = this->handler->acceptGame(name);
			string sendAnswer = "";
			if (answer) {
				sendAnswer = "true";
				//save user name for updating top score
				this->otherUserName = name;
			} else
				sendAnswer = "false";
			this->sendCommand(ACCEPT_ANSWER, sendAnswer.c_str());
			break;
		}
		case PEER_DATA: {

			int localPort;
			stringstream strValue1, strValue2;
			int destPort;
			string destIP;
			this->client->read((char *) &len, sizeof(len));
			len = ntohl(len);
			buff = new char[len];
			this->client->read(buff, len);

			std::vector<string> v;
			char* chars_array = strtok(buff, ":");
			while (chars_array) {
				v.push_back(chars_array);
				chars_array = strtok(NULL, ":");
			}

			strValue1 << v[0];
			strValue1 >> localPort;
			strValue2 << v[2];
			strValue2 >> destPort;
			destIP = v[1];

			this->UDPMsg = new UDPMessenger(localPort, destIP, destPort,
					this->handler);
			cout << "UDP Messenger created" << endl;
			this->handler->onAccepteAnswer(true);
			break;
		}
		case REFUSE_GAME:{
			this->handler->onAccepteAnswer(false);
			break;
		}
		case NO_USER:{
					this->handler->onNoUser();
					break;
				}

		default: {
			break;
		}

		}
	}

}
bool TCPMSNClient::getRandomUser() {
	int rec = sendCommand(RANDOM_USER, NULL);
	if (rec < 0){
		perror("ERROR send GET_RANDOM_USER  to server");
	return false;
	}
	return true;

}

bool TCPMSNClient::playGame(string name) {
	this->otherUserName = name;
	int rec = sendCommand(PLAY_GAME, name.c_str());
	if (rec < 0){
		perror("ERROR send PLAY_GAME  to server");
		return false;
	}
	return true;
}
bool TCPMSNClient::getNameList() {
	int rec = sendCommand(NAME_LIST, NULL);
	if (rec < 0){
		perror("ERROR send NAME_LIST  to server");
	return false;
	}
	return true;
}
void TCPMSNClient::sendByMessenger(string msg) {
	this->UDPMsg->sendTo(msg);
}
void TCPMSNClient::gameFinished(int score) {
	string msg;
	if(score==-1){
		msg="-1";
	}
	else{
	ostringstream ss;
	ss<<score;
	msg=this->otherUserName + ":" + ss.str();
	}
	cout<<"send command GAME_FINISH"<<endl;
	int rec = sendCommand(GAME_FINISH, msg.c_str());
	if (rec < 0)
		perror("ERROR send GAME_FINISH  to server");
	this->UDPMsg->close();
}
void TCPMSNClient::getTopScores() {
	int rec = sendCommand(TOP_SCORE, NULL);
	if (rec < 0)
		perror("ERROR send TOP_SCORE  to server");
}



} /* namespace networkingLab */

