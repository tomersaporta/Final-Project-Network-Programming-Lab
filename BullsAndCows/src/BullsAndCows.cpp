//============================================================================
// Name        : BullsAndCows.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Game.h"
#include <iostream>

using namespace networkingLab;
using namespace std;

int main() {

	cout << "Welcome to Bulls & Cows game" << endl;
	Game game;
	game.sdk->connect("127.0.0.1");
	game.printLoginInstructions();

	while (true) {
		string userName, password, command, msg;
		cin >> command;

		if (!game.loginLevel) {
			if (command.compare("r") == 0) {
				cin >> userName;
				cin >> password;
				game.sdk->registering(userName, password);

			} else if (command.compare("l") == 0) {
				cin >> userName;
				cin >> password;
				game.sdk->login(userName, password);

			} else if (command.compare("x") == 0) {
				cout << "Good by" << endl;
				return 0;
			} else {
				cout << "Wrong input" << endl;
				game.printLoginInstructions();

			}

		} else if (!game.userLevel) {

			if (command.compare("p") == 0) {
				cin >> userName;
				game.sdk->playGame(userName);
				cout << "Waiting for user to accept..." << endl;

			} else if (command.compare("li") == 0) {
				game.sdk->getNameList();

			} else if (command.compare("a") == 0) {
				sleep(4);
			} else if (command.compare("u") == 0) {
				game.sdk->getRandomUser();

			} else if (command.compare("ts") == 0) {
				game.sdk->getTopScores();

			} else if (command.compare("g") == 0) {
				string guess;
				cin >> guess;
				int numGuess;
				sscanf(guess.c_str(), "%d", &numGuess);
				while (numGuess < 1000 || numGuess > 9999) {
					cout << "Guess a number between 1000-9999" << endl;
					cin >> guess;
					sscanf(guess.c_str(), "%d", &numGuess);
				}
				string result = "guess:" + guess;
				game.sdk->sendByMessenger(result);

			}


		else if (command.compare("x") == 0) {
			cout << "Good by" << endl;
			string q = "quit:";
			if(game.sdk->UDPMsg!=NULL){
			game.sdk->sendByMessenger(q);
			}
			sleep(2);
			game.sdk->exit();
			return 0;



		} else {
			cout << "Wrong input" << endl;
			game.printUserInstructions();

		}
		}

	}

}
