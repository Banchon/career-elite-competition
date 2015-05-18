CC = g++
CXXFLAG =
LDFLAG =
OUT = ../target/game

vpath %.cpp ../source
vpath %.h ../source

$(OUT) : game.o recvmsg.o messagehandle.o
	$(CC) $(CXXFLAG) -o $(OUT) game.o recvmsg.o messagehandle.o $(LDFLAG)
game.o : game.cpp recvmsg.h messagehandle.h
	$(CC) $(CXXFLAG) -c -o game.o ../source/game.cpp
recvmsg.o : recvmsg.cpp
	$(CC) $(CXXFLAG) -c -o recvmsg.o ../source/recvmsg.cpp
messagehandle.o : messagehandle.cpp
	$(CC) $(CXXFLAG) -c -o messagehandle.o ../source/messagehandle.cpp
clean:
	rm *.o $(OUT)
