#ifndef CARDS_H
#define CARDS_H

#include <string>

enum Point {
	_2 = 2,
	_3 = 3,
	_4 = 4,
	_5 = 5,
	_6 = 6,
	_7 = 7,
	_8 = 8,
	_9 = 9,
	_10 = 10,
	_J = 11,
	_Q = 12,
	_K = 13,
	_A = 14 
};

enum Color {
	SPADES = 0,
	HEARTS = 1,
	CLUBS = 2,
	DIAMONDS = 3
};

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

int str_to_color(const std::string color);
int str_to_point(const std::string point);

#endif
