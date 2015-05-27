CC = g++
CXXFLAG = -std=c++0x
LDFLAG =
OUT = ../target/game

vpath %.cpp ../source
vpath %.h ../source

$(OUT) : game.o recvmsg.o messagehandle.o cards.o
	$(CC) $(CXXFLAG) -o $(OUT) game.o recvmsg.o messagehandle.o cards.o $(LDFLAG)
game.o : game.cpp recvmsg.h messagehandle.h cards.h
	$(CC) $(CXXFLAG) -c -o game.o ../source/game.cpp
cards.o : cards.cpp cards.h
	$(CC) $(CXXFLAG) -c -o cards.o ../source/cards.cpp
recvmsg.o : recvmsg.cpp
	$(CC) $(CXXFLAG) -c -o recvmsg.o ../source/recvmsg.cpp
messagehandle.o : messagehandle.cpp cards.h
	$(CC) $(CXXFLAG) -c -o messagehandle.o ../source/messagehandle.cpp
clean:
	rm *.o $(OUT)
