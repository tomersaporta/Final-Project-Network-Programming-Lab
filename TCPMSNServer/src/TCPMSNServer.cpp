/*
 * TCPMSNServer.cpp
 *
 *  Created on: Jun 26, 2017
 *      Author: user
 */

#include "TCPMSNServer.h"

using namespace std;
namespace networkingLab {

TCPMSNServer::TCPMSNServer() {
	this->server = new Server(MSNGR_PORT, this);
	this->path="highScore.txt";
	this->loadHighScore();
	this->dispatcher = new Dispatcher(this);
	this->brokerMng = new BrokerMng(this);
	this->login = new Login(this);
}

void TCPMSNServer::handleConnectedPeer(TCPSocket* peer) {
	this->login->addPeer(peer);

}
void TCPMSNServer::handleLoginPeer(TCPSocket* peer, string user_name) { //(TCPSocket* peer, useName)
	//updateMaps
	if (!user_name.empty()) {
		ostringstream Convert;
		Convert<< peer->getRemotedSocketPort();
		string ipPort = peer->getRemotedSocketIP() + ":" + Convert.str();
		updateMaps(ipPort, user_name);
	}
	this->dispatcher->addPeer(peer);
}

void TCPMSNServer::handleReturnedPeer(TCPSocket* peer,string user_name) {

	ostringstream Convert;
	Convert << peer->getRemotedSocketPort();
	string ipPort = peer->getRemotedSocketIP() + ":" + Convert.str();
	updateMaps(ipPort, user_name);

	this->dispatcher->addPeer(peer);


}

void TCPMSNServer::startServer() {
	sleep(2);
	this->start();

}
string TCPMSNServer:: getRandomName(){
	int num= rand()%(ipToName.size()+1);
	string name=ipToName.begin().operator ++(num)->second;
	return name;
}

void TCPMSNServer::close() {
	this->saveHighScore();
	this->dispatcher->close();
	this->login->close();
	this->server->close();

}

TCPMSNServer::~TCPMSNServer() {
	if (this->server != NULL) {
		delete this->server;
		this->server = NULL;
	}
	if (this->dispatcher != NULL) {
		delete this->dispatcher;
		this->dispatcher = NULL;
	}
	if (this->brokerMng != NULL) {
		delete this->brokerMng;
		this->brokerMng = NULL;
	}
}
void TCPMSNServer::run() {
	this->server->startServer();
	sleep(2);
	this->login->startLogin();

	this->dispatcher->startDispatcher();
	this->server->waitForThread();

	this->dispatcher->waitForThread();
	this->login->waitForThread();
}
string TCPMSNServer::getPeerList() {
	return this->dispatcher->getPeersList();
}

void TCPMSNServer::manageGameSession(User* user1, User* user2) {
	this->brokerMng->createGameBroker(user1, user2);
}

string TCPMSNServer::getName(string ip) {
	return ipToName[ip];
}
string TCPMSNServer::getIP(string name) {
	return nameToIp[name];
}
void TCPMSNServer::updateMaps(string ipPort, string name) {
	this->ipToName[ipPort] = name;
	this->nameToIp[name] = ipPort;
}
string TCPMSNServer::getNames() {
	string names = "";
	for (map<string, string>::iterator it = nameToIp.begin();
			it != nameToIp.end(); ++it)
		names += it->first + ":";
	return names;
}
void TCPMSNServer::removeUserFromMap(string ipPort,string name){

	this->ipToName.erase(ipPort);
	this->nameToIp.erase(name);
}

void TCPMSNServer::addToHighScore(string userName, int userScore) {
	//insert user score  data
	pair<string, int> userS;
	userS.first = userName;
	userS.second = userScore;
	this->highScore.push_back(userS);
	this->sortScore();

}


void TCPMSNServer::loadHighScore() {

	ssize_t ret_in;
	//creat file
	File * highScoreFile = new File(this->path, O_RDONLY);
	char buffer[1024];
	//read from file to buffer
	while ((ret_in = read(highScoreFile->socket_fd, &buffer, sizeof(buffer)))
			> 0) {
		cout << "reading high score data..." << endl;
	}

	std::vector<char*> v;
	char* chars_array = strtok(buffer, " .\n");
	while (chars_array) {
		v.push_back(chars_array);
		chars_array = strtok(NULL, " .\n");
	}


	for (size_t n = 1; n < v.size(); n += 3) {
		stringstream strValue;
		pair<string, int> p;
		p.first = v[n];
		strValue << v[n + 1];
		strValue >> p.second;

		this->highScore.push_back(p);
	}

//	for (auto it =highScore.begin(); it != highScore.end(); ++it) {
//			std::cout << it->first << "," << it->second << "\n";
//		}

	highScoreFile->close();

	this->sortScore();

}

void TCPMSNServer::saveHighScore() {

	File * saveFile = new File(this->path, O_RDWR | O_CREAT | O_TRUNC);
	string s;
	int i = 1;
	vector<pair<string, int> >::iterator it;
	for (it = highScore.begin(); it != highScore.end(); ++it) {
		stringstream strValue1, strValue2;
		strValue1 << i;
		strValue2 << it->second;
		string ii, score;
		strValue1 >> ii;
		strValue2 >> score;
		 s += ii + "." + it->first + " " + score + "\n";

		i++;
	}

	if (saveFile->write(s.data(), s.length()) < 0) {
		cout << "cant write to file " << this->path << endl;
	}
	cout << "file saved: " << this->path << endl;
	saveFile->close();

}

void TCPMSNServer::sortScore() {
	//use operator ()
	vector<pair<string, int> > mapcopy(this->highScore.begin(),
			this->highScore.end());
	sort(mapcopy.begin(), mapcopy.end(), less_second<string, int>());
	this->highScore = mapcopy;
}

// getHighScor return string
string TCPMSNServer::getHighScoreList() {
	string s;
	int i = 1;
	vector<pair<string, int> >::iterator it;
	for (it = highScore.begin(); it != highScore.end(); ++it) {
		stringstream strValue1, strValue2;
		strValue1 << i;
		strValue2 << it->second;
		string ii, score;
		strValue1 >> ii;
		strValue2 >> score;
		 s += ii + "." + it->first + " " + score + "\n";
		i++;
	}
	return s;

}

void TCPMSNServer::removePeer(TCPSocket* peer) {
	this->dispatcher->removePeerFromListner(peer);
}

} /* namespace npl */


