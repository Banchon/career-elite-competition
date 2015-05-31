#ifndef TEXASHOLDEM_H
#define TEXASHOLDEM_H

#include <string>
#include <map>
#include "Card.h"

enum HandPowerType {
	HIGH_CARD = 1,
	ONE_PAIR = 2,
	TWO_PAIR = 3,
	THREE_OF_A_KIND = 4,
	STRAIGHT = 5,
	FLUSH = 6,
	FULL_HOUSE = 7,
	FOUR_OF_A_KIND = 8,
	STRAIGHT_FLUSH = 9
};


typedef struct HandStrength {
	int wins;
	int losses;
	int ties;
}HandStrength;

enum BettingDecision {
	FOLD_DECISION = 0,
	CALL_DECISION = 1,
	RAISE_DECISION = 2,
};

enum Action {
	FOLD = 0,
	BLIND = 1,
	CHECK = 2,
	CALL = 3,
	RAISE = 4,
	ALL_IN = 5,
	NULLACTION = 6
};

enum BettingRound {
	PRE_FLOP = 0,
	FLOP = 1,
	TURN = 2,
	RIVER = 3
};
	


typedef struct BasicInfo {
	std::string pid;
	int seat;    //0 stands for button, 1 stands for small blind, 2 stands for big blind .... -1 stands for nothing;
	BettingRound currentBettingRound;
	Action lastSelfAction;
	int jetton; //current jetton.
	int money;   //current money
	Card holeCards[2];
	Card flopCards[3];
	Card turnCard;
	Card riverCard;
	std::map<std::string, Action> lastPlayersAction;
	double billChenValue;
	HandStrength handStrength;
	int leastRaiseJetton;
}BasicInfo;

#endif
