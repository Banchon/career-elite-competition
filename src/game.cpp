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

int main(int argc, char *argv[])
{
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

	FILE* localSocketStream = fdopen(localSocket, "r+");
	if(localSocketStream == NULL) {
		std::cout << "error: fdopen() fail." << std::endl;
		return -1;
	}

	std::string regmsg = "reg: ";
	regmsg.append(argv[5]);
	regmsg.append(" boo \n");
	std::cout << regmsg.c_str();


	//TCP connection has already established.
	
	
	//TODO send the registration message.
	






	//TODO interact with the game server.



	return 0;
}
