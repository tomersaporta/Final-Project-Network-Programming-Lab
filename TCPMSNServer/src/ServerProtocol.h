/*
 * TCPMSNProtocol.h
 *
 *  Created on: Jul 7, 2017
 *      Author: user
 */

#ifndef SRC_SERVERPROTOCOL_H_
#define SRC_SERVERPROTOCOL_H_

/**
 * TCP Messenger protocol:
 * all messages are of the format [Command 4 byte int]
 * and optionally data follows in the format [Data length 4 byte int][ Data ]
 */
#define MSNGR_PORT 3356
///////////Network //////////////////////
#define CLOSE_SESSION_WITH_PEER 		1
#define OPEN_SESSION_WITH_PEER 			2
#define EXIT							3
#define SEND_MSG_TO_PEER				4
#define SESSION_REFUSED					5
#define SESSION_ESTABLISHED				6
#define INTERRUPT_SOCKET                7
//////////Login / Register///////////////
#define LOG_IN							8
#define LOG_IN_REFUSED_PASSWORD			9
#define LOG_IN_REFUSED_USERNAME			10
#define LOG_IN_SUCCEESED				11
#define INTERRUPT_SOCKET_LOGIN			12
#define REGISTER						13
#define REGISTER_REFUSED				14
#define REGISTER_SUCCEESED				15
/////////User ///////////////////////////
#define REFUSE_GAME					   19
#define PLAY_GAME					   20
#define NAME_LIST					   21
#define	ACCEPT_ANSWER				   22
#define RANDOM_USER						23
#define PEER_DATA						24
#define GAME_FINISH					   25
#define TOP_SCORE					   26
#define NO_USER						   27

#define TEST_PEER_NAME "test"
#define SESSION_REFUSED_MSG "Connection to peer refused, peer might be busy or disconnected, try again later"




#endif /* SRC_SERVERPROTOCOL_H_ */
