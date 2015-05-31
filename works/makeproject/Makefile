CC = g++
CXXFLAG = -std=c++0x -DDEBUG
LDFLAG =
OUT = ../target/game

vpath %.cpp ../source
vpath %.h ../source

OBJS = game.o recvmsg.o messagehandle.o Card.o decision.o billChenValueEvaluator.o HandStrengthEvaluator.o HandPowerRank.o

$(OUT) : $(OBJS)
	$(CC) $(CXXFLAG) -o $(OUT) $(OBJS) $(LDFLAG)
game.o : game.cpp recvmsg.h messagehandle.h Card.h texasHoldem.h
	$(CC) $(CXXFLAG) -c -o game.o ../source/game.cpp
Card.o : Card.h Card.cpp
	$(CC) $(CXXFLAG) -c -o Card.o ../source/Card.cpp
recvmsg.o : recvmsg.cpp
	$(CC) $(CXXFLAG) -c -o recvmsg.o ../source/recvmsg.cpp
messagehandle.o : messagehandle.cpp texasHoldem.h Card.h billChenValueEvaluator.h HandStrengthEvaluator.h decision.h
	$(CC) $(CXXFLAG) -c -o messagehandle.o ../source/messagehandle.cpp
decision.o : decision.cpp decision.h texasHoldem.h
	$(CC) $(CXXFLAG) -c -o decision.o ../source/decision.cpp
billChenValueEvaluator.o : billChenValueEvaluator.cpp billChenValueEvaluator.h Card.h
	$(CC) $(CXXFLAG) -c -o billChenValueEvaluator.o ../source/billChenValueEvaluator.cpp
HandStrengthEvaluator.o : HandStrengthEvaluator.cpp HandStrengthEvaluator.h Card.h Deck.h texasHoldem.h HandPower.h HandPowerRank.h
	$(CC) $(CXXFLAG) -c -o HandStrengthEvaluator.o ../source/HandStrengthEvaluator.cpp
HandPowerRank.o : HandPowerRank.cpp HandPowerRank.h HandPower.h Card.h texasHoldem.h
	$(CC) $(CXXFLAG) -c -o HandPowerRank.o ../source/HandPowerRank.cpp
clean:
	rm *.o $(OUT)
