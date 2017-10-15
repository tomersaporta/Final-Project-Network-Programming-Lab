/*
 * TCPMSNServer.h
 *
 *  Created on: Jun 26, 2017
 *      Author: user
 */

#ifndef SRC_TCPMSNSERVER_H_
#define SRC_TCPMSNSERVER_H_
#include "Server.h"
#include "Dispatcher.h"
#include "BrokerMng.h"
#include "BrokerMngHandler.h"
#include "DispatcherHandler.h"
#include "ServerHandler.h"
#include "MThread.h"
#include "Login.h"
#include <map>
#include <string>
#include "ServerProtocol.h"

//operator () to sort the high score data by smallest score
template <typename T1, typename T2>
struct less_second {
    typedef pair<T1, T2> type;
    bool operator ()(type const& a, type const& b) const {
        return a.second < b.second;
    }
};

using namespace std;
namespace networkingLab {

class TCPMSNServer: public ServerHandler,LoginHandler,DispatcherHandler,BrokerMngHandler, MThread {
private:
	Server* server;
	Dispatcher* dispatcher;
	BrokerMng* brokerMng;
	Login* login;
	//updateMaps;
	map <string,string> ipToName;
	map <string,string> nameToIp;
	vector< pair< string, int > >highScore;
	string path;

public:

	virtual void manageGameSession(User* user1, User* user2);
	virtual string getName(string ip);
	virtual string getIP(string name);
	virtual string getNames();
	void updateMaps(string ipPort, string name);
	virtual string getRandomName();
	TCPMSNServer();
	virtual void handleConnectedPeer(TCPSocket* peer);
	virtual void handleReturnedPeer(TCPSocket* peer,string user_name);
	virtual void handleLoginPeer(TCPSocket* peer, string user_name);
	virtual void removeUserFromMap(string ipPort,string name);
	virtual string getHighScoreList();
	void loadHighScore();
	void saveHighScore();
	void sortScore();
	virtual void addToHighScore(string userName, int userScore);
	void startServer();
	void close();
	virtual ~TCPMSNServer();
	void run();
	string getPeerList();
	virtual void removePeer(TCPSocket* peer);

};

} /* namespace npl */

#endif /* SRC_TCPMSNSERVER_H_ */
