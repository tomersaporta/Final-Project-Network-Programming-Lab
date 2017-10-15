/*
 * TCPMSNClient.h
 *
 *  Created on: Jun 11, 2017
 *      Author: Tomer Saporta
 */

#ifndef SRC_TCPMSNCLIENT_H_
#define SRC_TCPMSNCLIENT_H_

#include "TCPSocket.h"
#include "MThread.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>

#include "SDKProtocol.h"
#include "UDPMessenger.h"

using namespace std;
namespace networkingLab {
class TCPMSNClient;
// Abstract class implementation in TCPMSNClientTest ans TCPMSNClientCLI
class TCPMSNClientHandler {
private:

public:
	TCPMSNClient* sdk;
	TCPMSNClientHandler();
	TCPMSNClient* getSDK();
	virtual bool acceptGame(string name)=0;
	virtual void onMessageRecived(string message)=0;

	virtual void onGetUsers(string list)=0;
	virtual void onGetTopScore(string list)=0;
	virtual void onAccepteAnswer(bool answer)=0;
	virtual void onRecvMsg(string msg)=0;
	virtual void onLoginSuccess()=0;
	virtual void onLoginUserFailed()=0;
	virtual void onLoginPasswordFailed()=0;
	virtual void onRegisterSuccess()=0;
	virtual void onNoUser()=0;
	virtual ~TCPMSNClientHandler() {
	}
};

class TCPMSNClient: public MThread {

public:
	TCPSocket *client;
	TCPMSNClientHandler * handler;
	bool isConnected;
	UDPMessenger* UDPMsg;
	string otherUserName;

	TCPMSNClient();
	void setHandler(TCPMSNClientHandler * handler);
	virtual ~TCPMSNClient();
	/*
	 * game request
	 *
	 *  @param name- name of the component user
	 *
	 *  @return true on success otherwise false
	 */

	bool playGame(string name);
	/*
	 *request list of connected users
	 *
	 *  @return true on success otherwise false
	 */
	bool getNameList();

	/*
	 * connect the use to remote server on given user name and password,
	 *
	 *
	 *  @param user_name , password- user name and password required to register
	 *
	 *  @return true on success otherwise false
	 */

	bool registering(string user_name, string password);

	/*
	 * connect the use to remote server on given user name and password,
	 *
	 *
	 *  @param user_name , password- user name and password required to login
	 *
	 *  @return true on success otherwise false
	 */

	bool login(string user_name, string password);
	/*
	 * connect the client to remote server on given ip,
	 *  the server readied from the protocol
	 *
	 *  @param ip- the ip of the server to connect to
	 *
	 *  @return true on success otherwise false
	 */
	bool connect(string ip);

	/*
	 * open session between the client to other client on given ip and port
	 *
	 *  @param ip- the ip of the remote client to connect to
	 *	@param port- the port of the remote client to connect to
	 *
	 *  @return true on success otherwise false
	 */
	bool openSession(string ip, int port);

	/*
	 * send message to the connected remote client
	 *
	 *  @param msg- message to send to
	 *
	 */

	void sendMessage(string msg);

	/*
	 * close the session with the remote client
	 */
	void closeSession();

	/*
	 * disconnect the session with the server
	 */
	void disconnect();

	/*
	 * closing the application
	 */
	void exit();
	/*
	 * @return  int- the client port
	 */
	int getPort();
	/*
	 * run thread
	 */
	virtual void run();

	int sendCommand(int cmd, const char* buff);

	void recvCommand();

	bool getRandomUser();
	/*
	 * update the server when the game ends
	 *
	 *
	 *  @param score - user score winner
	 *
	 *
	 */

	void gameFinished(int score);
	/*
	 * send by UDP protocol messages
	 *
	 *
	 *  @param msg - user message
	 *
	 *
	 */
	void sendByMessenger(string msg);
	/*
	 * request for top scores list
	 *

	 */

	void getTopScores();

};

} /* namespace networkingLab */

#endif /* SRC_TCPMSNCLIENT_H_ */
