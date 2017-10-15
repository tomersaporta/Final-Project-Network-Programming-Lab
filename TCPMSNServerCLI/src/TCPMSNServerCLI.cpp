//============================================================================
// Name        : TCPMSNServerCLI.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "TCPMSNServer.h"
using namespace networkingLab;
using namespace std;

void printInstructions(){
	cout << "-----------------------" << endl;
		cout << " s - start \n x - shutdown server \n lp - list peers " << endl;
		cout << "-----------------------" << endl;
}

int main() {
	printInstructions();
	TCPMSNServer* server =new TCPMSNServer();
	while (true) {
		string cmd;
		cin >> cmd;
		if (cmd == "s") {
			server->startServer();
		} else if (cmd == "x") {
			cout << "shutdown server.." << endl;
			server->close();
			break;
		}else if(cmd == "lp"){
			string s = server->getPeerList();
			cout<<s<<endl;
		}else{
			cout << "wrong input" << endl;
			printInstructions();
		}
	}
	return 0;
}
