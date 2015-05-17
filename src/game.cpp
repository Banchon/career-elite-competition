#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include "recvmsg.h"
#include "messagehandle.h"

using std::string;
using std::vector;


int main(int argc, char *argv[])
{
	//definition of the message types that game client can receive from gameserver
	const string SEAT-INFO-MSG = "seat/ \n";
	const string GAME-OVER-MSG = "game-over \n";
	const string BLIND-MSG = "blind/ \n";
	const string HOLD-CARDS-MSG = "hold/ \n";
	const string INQUIRE-MSG = "inquire/ \n";
	const string FLOP-MSG = "flop/ \n";
	const string TURN-MSG = "turn/ \n";
	const string RIVER-MSG = "river/ \n";
	const string SHOWDOWN-MSG = "showdown/ \n";
	const string POT-WIN-MSG = "pot-win/ \n"; 
	if(argc < 6) {
		std::cout << "error: incorrect command line arguments." << std::endl;
		std::cout << "usage: " << argv[0] <<" serverIP serverPort localIP localPort playerID" << std::endl;
		return -1;
	}

	sockaddr_in serverAddress;
	sockaddr_in localAddress;
	//int pid; //player id;

	::memset(&serverAddress, 0, sizeof(serverAddress));
	::memset(&localAddress, 0, sizeof(localAddress));

	serverAddress.sin_family = AF_INET;
	localAddress.sin_family = AF_INET;

	//transform the arguments.
	if(::inet_pton(AF_INET, argv[1], &serverAddress.sin_addr) != 1) {
	 std::cout << "error: invalid serverIP format." << std::endl;
	 return -1;
	}
	serverAddress.sin_port = ::htons(::atoi(argv[2]));

	if(::inet_pton(AF_INET, argv[3], &localAddress.sin_addr) != 1) {
		std::cout << "error: invalid localIP format." << std::endl;
		return -1;
	}
	localAddress.sin_port = ::htons(::atoi(argv[4]));

	//pid = ::atoi(argv[5]);

	//establish the TCP connect with the game server.
	int localSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if(localSocket == -1) {
		std::cout << "error: socket() fail." << std::endl;
		return -1;
	}

	//set local socket address in REUSE mode.
	int is_reuse_addr = 1;
	::setsockopt(localSocket, SOL_SOCKET, SO_REUSEADDR, &is_reuse_addr, sizeof(int));

	if(::bind(localSocket, (sockaddr *)&localAddress, sizeof(sockaddr_in)) == -1) {
		std::cout << "error: bind() fail." << std::endl;
		return -1;
	}

	//if connect to game server failed, just try to connect again.
	while(::connect(localSocket, (sockaddr *)&serverAddress, sizeof(sockaddr_in)) == -1)
		::usleep(100 * 1000); //sleep 100ms

	FILE* localSocketFileStream = fdopen(localSocket, "r+");
	if(localSocketFileStream == NULL) {
		std::cout << "error: fdopen() fail." << std::endl;
		return -1;
	}

	//registration
	std::string regmsg("reg: ");
	regmsg.append(argv[5]);
	regmsg.append(" boo \n");

	::fputs(regmsg.c_str, localSocketFileStream);
	::fflush(localSocketFileStream);

	while(true) {
		vector<string>* message_ptr = new vector<string>;
		if(recvmsg(localSocketFileStream, *message_ptr) == -1)
			return -1;

		//get the message type and call the corresponse handle interface. 
		if(message_ptr -> size() > 0) {

			if((*message_ptr)[0] == SEAT-INFO-MSG)
				seat_info_msg_handle(*message_ptr);
			else if((*message_ptr)[0] == BLIND-MSG)
				blind_msg_handle(*message_ptr);
			else if((*message_ptr)[0] == HOLD-CARDS-MSG)
				hold_cards_msg_handle(*message_ptr);
			else if((*message_ptr)[0] == INQUIRE-MSG)
				inquire_msg_handle(*message_ptr, localSocketFileStream);  //more argument needed to perform better action.
			else if((*message_ptr)[0] == FLOP-MSG)
				flop_msg_handle(*message_ptr);
			else if((*message_ptr)[0] == TURN-MSG)
				turn_msg_handle(*message_ptr);
			else if((*message_ptr)[0] == RIVER-MSG)
				river_msg_handle(*message_ptr);
			else if((*message_ptr)[0] == SHOWDOWN-MSG)
				showdown_msg_handle(*message_ptr);
			else if((*message_ptr)[0] == POT-WIN-MSG)
				pot_win_msg_handle(*message_ptr);
			else if ((*message_ptr)[0] == GAME-OVER-MSG) {
				game_over_msg_handle(*message_ptr);
				break;
			}
			else
				std::cout << "unknown message type: " << (*message_ptr)[0];
		}
		delete message_ptr;		
	}

	//deallocate the socket resource.
	::fclose(localSocketFileStream);
	::close(localSocket);
	return 0;
}
