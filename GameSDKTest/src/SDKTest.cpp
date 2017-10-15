/*
 * TCPMSNClientTest.cpp
 *
 *  Created on: Jun 11, 2017
 *      Author: user
 */

#include "SDKTest.h"
using namespace std;
namespace networkingLab {

//////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////                                            ///////////////////////////
///////////////////////////   ClientHandlerTest       implementation    ///////////////////////////
///////////////////////////                                            ///////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

void ClientHandlerTest::onMessageRecived(string message) {
	this->messages = message;
	cout << "Recived message: " << message << endl;
}


bool ClientHandlerTest::acceptGame(string name) {

		return true;
}



TCPMSNClientTest::TCPMSNClientTest() {


}



TCPMSNClientTest::~TCPMSNClientTest() {
}



//////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////                                            ///////////////////////////
///////////////////////////   ClientTest       implementation    ///////////////////////////
///////////////////////////                                            ///////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

void ClientHandlerTest::onGetUsers(string list){
	cout<<"Users that are connected:\n"<<list<<endl;

}
void ClientHandlerTest::onAccepteAnswer(bool answer){
	if(answer){
		cout<<"game accepted- start playing "<<endl;
	}
	else
		cout<<"game refused- try other user"<<endl;
}
void ClientHandlerTest::onRecvMsg(string msg){
	if(this->msg.compare(msg)==0)
		this->testing=true;
}
void ClientHandlerTest::onLoginSuccess() {
}

void ClientHandlerTest::onLoginUserFailed() {
}

void ClientHandlerTest::onLoginPasswordFailed() {
}

void ClientHandlerTest::onRegisterSuccess() {
}

void ClientHandlerTest::onNoUser() {
}

ClientHandlerTest::ClientHandlerTest() {
	this->testing=false;
	this->msg="check";
}

void ClientHandlerTest::gameFinished(int score){

}

bool networkingLab::TCPMSNClientTest::test() {
	int rec;

	//create client 1

	ClientHandlerTest handler1;

	TCPMSNClient* client1= handler1.getSDK();

	//connect client 1 to server

	rec = client1->connect("127.0.0.1");
	if (rec < 0) {
		perror("ERROR connect client 1");
		return false;
	}
	sleep(2);
	client1->registering("Tair", "t1990");
	ClientHandlerTest handler2;

	TCPMSNClient* client2=handler2.getSDK();
	sleep(2);

	rec = client2->connect("127.0.0.1");
	if (rec < 0) {
		perror("ERROR connect client 2");
		return false;
	}
	sleep(3);
	client2->login("shir", "5678");
	sleep(2);
	client1->getNameList();
	client1->playGame("shir");
	sleep(3);
	client2->sendByMessenger("check");
	sleep(2);
	client1->sendByMessenger("check");


	sleep(3);

	return (((ClientHandlerTest*)client1->handler)->testing && ((ClientHandlerTest*)client2->handler)->testing);



}

void ClientHandlerTest::onGetTopScore(string list) {
	cout<<list<<endl;
}



} /* namespace networkingLab */

