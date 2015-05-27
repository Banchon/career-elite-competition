#ifndef CARDS_H
#define CARDS_H

enum Point {
	_2 = 2;
	_3 = 3;
	_4 = 4;
	_5 = 5;
	_6 = 6;
	_7 = 7;
	_8 = 8;
	_9 = 9;
	_10 = 10;
	_J = 11;
	_Q = 12;
	_K = 13;
	_A = 14; 
};

enum Color {
	SPADES = 0;
	HEARTS = 1;
	CLUBS = 2;
	DIAMONDS = 3;
};

typedef struct BasicInfo {
	string pid;
	int phase;  //0, 1, 2, 3 represent pre-flop, flop, turn, river respectively,  otherwise the phase is -1;
	int jetton;  //current jetton;
	int money;   //current money;
	int seat;    //0 stands for button, 1 stands for small blind, 2 stands for big blind .... -1 stands for nothing;
	int hold_cards[2][2];
}BasicInfo;

#endif