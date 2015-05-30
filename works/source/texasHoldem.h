#ifndef TEXASHOLDEM_H
#define TEXASHOLDEM_H

#include <string>

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
	ALL_IN = 5
};
	


typedef struct BasicInfo {
	std::string pid;
	int action_state; //-1 not in a game, 0 normal, 1 all-in, 2 fold. 
	int phase;  //0, 1, 2, 3 represent pre-flop, flop, turn, river respectively,  otherwise the phase is -1;
	int jetton;  //current jetton;
	int money;   //current money;
	int seat;    //0 stands for button, 1 stands for small blind, 2 stands for big blind .... -1 stands for nothing;
	int total_player;
	int hold_cards[2][2];
	int flop_cards[3][2];
	int turn_cards[2];
	int river_cards[2];
	double hold_cards_value;
}BasicInfo;

#endif
