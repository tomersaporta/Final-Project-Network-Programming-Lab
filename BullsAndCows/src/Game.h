/*
 * Game.h
 *
 *  Created on: Sep 3, 2017
 *      Author: user
 */

#ifndef GAME_H_
#define GAME_H_

#include "TCPMSNClient.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <time.h>

using namespace std;
namespace networkingLab {

class Game: public TCPMSNClientHandler {
	int num[4];

	string checkNumber(string snum);
	string convertInt(int n);
	int score;
	bool win;

public:
	bool loginLevel;
	bool userLevel;
	bool gameLevel;
	bool acceptPlay;
	Game();
	void printLoginInstructions();
	void printUserInstructions();
	void getRandNumber();
	void printNumArray();
	virtual bool acceptGame(string name);
	virtual void onMessageRecived(string message);
	virtual void onOpenSession(string ipPort);
	virtual void onClosedSession();
	virtual void onGetUsers(string list);
	virtual void onAccepteAnswer(bool answer);
	virtual void onRecvMsg(string msg);
	virtual void onGameEnding();
	virtual void onLoginSuccess();
	virtual void onLoginUserFailed();
	virtual void onLoginPasswordFailed();
	virtual void onRegisterSuccess();
	virtual void onNoUser();
	virtual void onGetTopScore(string list);

	virtual ~Game();
};

} /* namespace networkingLab */

#endif /* GAME_H_ */
