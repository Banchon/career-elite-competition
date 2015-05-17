testgame : game.o recvmsg.o messagehandle.o
	g++ -o testgame game.o recvmsg.o messagehandle.o
game.o : game.cpp recvmsg.h messagehandle.h
	g++ -c -o game.o game.cpp
recvmsg.o : recvmsg.cpp
	g++ -c -o recvmsg.o recvmsg.cpp
messagehandle.o : messagehandle.cpp
	g++ -c -o messagehandle.o messagehandle.cpp
clean:
	rm *.o testgame
