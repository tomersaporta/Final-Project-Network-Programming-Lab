/*
 * TCPMSNClientTest.h
 *
 *  Created on: Jun 11, 2017
 *      Author: user
 */

#ifndef SDKTEST_H_
#define SDKTEST_H_

#include "TCPMSNClient.h"
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;


namespace networkingLab {

class ClientHandlerTest:public TCPMSNClientHandler{

public:
	bool testing;
	string msg;
	string messages;
	ClientHandlerTest();
	virtual bool acceptGame(string name);
	virtual void onMessageRecived(string message);
	virtual void onGetUsers(string list);
	virtual void onAccepteAnswer(bool answer);
	virtual void onRecvMsg(string msg);
	virtual void gameFinished(int score);
	virtual void onLoginSuccess();
	virtual void onLoginUserFailed();
	virtual void onLoginPasswordFailed();
	virtual void onRegisterSuccess();
	virtual void onNoUser();
	virtual void onGetTopScore(string list);

	virtual ~ClientHandlerTest(){}
};


class TCPMSNClientTest {
public:
	TCPMSNClientTest();
	virtual ~TCPMSNClientTest();
	bool test();
};

} /* namespace networkingLab */

#endif /* SDKTEST_H_ */
