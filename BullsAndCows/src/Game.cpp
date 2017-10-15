/*
 * Game.cpp
 *
 *  Created on: Sep 3, 2017
 *      Author: user
 */

#include "Game.h"

namespace networkingLab {

Game::Game() {

	win=false;
	score=0;
	loginLevel=false;
	userLevel=false;
	gameLevel=false;
	acceptPlay=false;

}
void Game::printLoginInstructions(){
	cout<<"To register please type: r <user name> <password>"<<endl;
	cout<<"To login please type: l <user name> <password>"<<endl;
	cout<<"To exit type: x"<<endl;
}

void Game::printUserInstructions(){
	cout<<"To start a game with a specific user type: p <user name>"<<endl;
	cout<<"To get a list of available users please type: li"<<endl;
	cout<<"To start a game with a random player: u" <<endl;
	cout<<"To get top score list type: ts"<<endl;
	cout<<"To exit type: x"<<endl;
}

bool Game::acceptGame(string name) {
	string answer="";
		cout<<"Accept a game with " + name +"\n type a <YES/NO>"<<endl;
		cin>>answer;
		transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
		if (answer.compare("yes")==0)
			return true;
		else
			return false;
	}
void Game::onLoginSuccess() {
	cout<<"You logged in successfully"<<endl;
	this->loginLevel=true;
	this->printUserInstructions();
}

void Game::onLoginUserFailed() {
	cout<<"The user name is incorrect - try again"<<endl;
	this->printLoginInstructions();
}

void Game::onLoginPasswordFailed() {
	cout<<"The password is incorrect- try again"<<endl;
	this->printLoginInstructions();
}

void Game::onRegisterSuccess() {
	cout<<"You registered successfully"<<endl;
	this->loginLevel=true;
	this->printUserInstructions();

}


void Game::onMessageRecived(string message) {

}

void Game::onOpenSession(string ipPort) {
}

void Game::onClosedSession() {
}

void Game::onGetUsers(string list) {
	string delimiter= ":";
	size_t pos = 0;
	string token;
	int i=1;
	cout<<"These are the users that are available to play:"<<endl;
	while ((pos = list.find(delimiter)) != string::npos) {
		ostringstream ss;
		ss<<i;
		string num=ss.str();
	    token = num + ") " + list.substr(0, pos);
	    cout << token << endl;
	    list.erase(0, pos + delimiter.length());
	    i++;
	}

}

void Game::onAccepteAnswer(bool answer) {
	if(answer){
		string guess;

		this->getRandNumber();
		cout<<"******************************************"<<endl;
		cout<<"*****       Starting the game      ******"<<endl;
		cout<<"*****************************************"<<endl;
		cout<<"To exit type: x"<<endl;
		cout<<"Your number is: "<<endl;
		this->printNumArray();

		cout<<"start guessing the number of the other user, type: g <your guess >(number between 1000-9999)"<<endl;
	}
	else{
		cout<<"The user refused to play with you - try a new user"<<endl;
		this->printUserInstructions();
	}
}
void Game:: printNumArray(){


	for (int i=0;i<4; i++){
		cout<<num[i]<<"";
	}
		cout<<endl;
}

void Game::onRecvMsg(string msg) {
	string type = msg.substr(0, msg.find(":"));
	string message = msg.substr(msg.find(":")+1, msg.length());
	string guess;
	//other user quit game
	if(type.compare("quit")==0){
		cout<<"The second user quit the game - the game is finished"<<endl;
		this->sdk->gameFinished(-1);
	}
	//other user guessed a number
	else if(type.compare("guess")==0){
		score++;
		string sco=this->convertInt(score);
		string answer=this->checkNumber(message);
		//if the guess was correct
		if(win){
			cout<<"The other user won- he guessed your number in " + sco + " guess's"<<endl;
			string result= "win: you are the winner, your guess was correct- number of guess's " + sco;
			this->sdk->sendByMessenger(result);
			this->sdk->gameFinished(score);
			this->printUserInstructions();

		}

		else{
		cout<<"the other user guessed " + message + "\n he guessed " + sco + " times"<<endl;
		string result= "result:"+ answer + "\n Number of guess's " + sco;
		this->sdk->sendByMessenger(result);
		}
	}
	//receiving the result of the users guess
	else if(type.compare("result")==0){
		cout<<"The result of your guess is:\n " + message<<endl;
		cout<<"Guess again"<<endl;

	}
	else if(type.compare("win")==0){
		cout<<message<<endl;
		this->printUserInstructions();

	}

}

void Game::onGameEnding() {
}

void Game::onNoUser(){
	cout<<"No such user"<<endl;
		this->printUserInstructions();
}



Game::~Game() {

}
void Game::getRandNumber(){
	srand(time(NULL));
	int n=rand()%(9999-1000+1)+1000;
	for (int i=3;i>=0;i--){
		int y=n%10;
		n=n/10;
		num[i]=y;
	}
}
string Game::checkNumber(string snum){
	int gnum;
	int array[4];
	int black=0;
	int white=0;
	sscanf(snum.c_str(), "%d", &gnum);
	for(int i=3;i>=0;i--){
		int y=gnum%10;
		gnum=gnum/10;
		array[i]=y;
	}
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(array[i]==num[i] && j==i){
				black++;
				break;
			}
			else if(array[j]==num[i] && j!=i)
				white++;
		}
	}
	//lift a flag if answered correct
	if(black==4)
		this->win=true;

	string sblack=this->convertInt(black);
	string swhite= this->convertInt(white);
	string answer= "number of blacks: " + sblack + "\n number of whites: " + swhite;
	return answer;
}
string Game::convertInt(int n){
	ostringstream ss;
			ss<<n;
			return ss.str();
}


void Game::onGetTopScore(string list) {
	cout<<list<<endl;
}

} /* namespace networkingLab */


