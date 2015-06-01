#include <iostream>
#include "Card.h"
#include "HandPower.h"
#include "HandPowerRank.h"
#include <vector>

using std::cout;
using std::endl;
using std::vector;

int main() {

	//Straight flush
	//Ac, Kc, Qc, Jc, 10c, Kd, Ks
	vector<Card> straightFlush;	
	unsigned point_ = _A;
	for(unsigned i = 0; i < 5; i++) {
		Card card(CLUBS, (Point)(point_ - i));
		straightFlush.push_back(card);
	}
	
	{
		Card card1(DIAMONDS, _K);
		straightFlush.push_back(card1);

		Card card2(SPADES, _K);
		straightFlush.push_back(card2);
	}

	//Four of a Kind
	//9h, 9s, 9c, 9d, Ks, Jd, 8s
	vector<Card> fourOfAKind;
	{
		Card card1(HEARTS, _9);
		Card card2(SPADES, _9);
	   	Card card3(CLUBS, _9);
	   	Card card4(DIAMONDS, _9);
	   	Card card5(SPADES, _K);
	   	Card card6(DIAMONDS, _J);
		Card card7(SPADES, _8);

		fourOfAKind.push_back(card1);
		fourOfAKind.push_back(card2);
		fourOfAKind.push_back(card3);
		fourOfAKind.push_back(card4);
		fourOfAKind.push_back(card5);
		fourOfAKind.push_back(card6);
		fourOfAKind.push_back(card7);
	}

	//Full house
	//Jh, Js, Jd, 10h, 10s, 9h, 8d
	vector<Card> fullHouse;
	
	{
		Card card1(HEARTS, _J);
		Card card2(SPADES, _J);
	   	Card card3(DIAMONDS, _J);
	   	Card card4(HEARTS, _10);
	   	Card card5(SPADES, _10);
	   	Card card6(HEARTS, _9);
		Card card7(DIAMONDS, _8);

		fullHouse.push_back(card1);
		fullHouse.push_back(card2);
		fullHouse.push_back(card3);
		fullHouse.push_back(card4);
		fullHouse.push_back(card5);
		fullHouse.push_back(card6);
		fullHouse.push_back(card7);
	}

	//FLUSH
	//10s, 7s, 3s, Ks, 8h, 8s, Js;
	vector<Card> flush;
	
	{
		Card card1(SPADES, _10);
		Card card2(SPADES, _7);
	   	Card card3(SPADES, _3);
	   	Card card4(SPADES, _K);
	   	Card card5(HEARTS, _8);
	   	Card card6(SPADES, _8);
		Card card7(SPADES, _J);

		flush.push_back(card1);
		flush.push_back(card2);
		flush.push_back(card3);
		flush.push_back(card4);
		flush.push_back(card5);
		flush.push_back(card6);
		flush.push_back(card7);
	}

	//Straight
	//Ks, Jh, 10s, 8d, 9c, 7c, Kd
	vector<Card> straight;
	
	{
		Card card1(SPADES, _10);
		Card card2(HEARTS, _J);
	   	Card card3(SPADES, _10);
	   	Card card4(DIAMONDS, _8);
	   	Card card5(CLUBS, _9);
	   	Card card6(CLUBS, _7);
		Card card7(DIAMONDS, _K);

		straight.push_back(card1);
		straight.push_back(card2);
		straight.push_back(card3);
		straight.push_back(card4);
		straight.push_back(card5);
		straight.push_back(card6);
		straight.push_back(card7);
	}

	//Three of a kind
	//Qs, Qh, Qc, 10d, 9h, 6c, As

	vector<Card> threeOfAKind;
	
	{
		Card card1(SPADES, _Q);
		Card card2(HEARTS, _Q);
	   	Card card3(CLUBS, _Q);
	   	Card card4(DIAMONDS, _10);
	   	Card card5(HEARTS, _9);
	   	Card card6(CLUBS, _6);
		Card card7(SPADES, _A);

		threeOfAKind.push_back(card1);
		threeOfAKind.push_back(card2);
		threeOfAKind.push_back(card3);
		threeOfAKind.push_back(card4);
		threeOfAKind.push_back(card5);
		threeOfAKind.push_back(card6);
		threeOfAKind.push_back(card7);
	}

	//Two pairs
	//Qs, Qh, 10c, 9d, 10h, Kc, Ks
	vector<Card> twoPairs;
	
	{
		Card card1(SPADES, _Q);
		Card card2(HEARTS, _Q);
	   	Card card3(CLUBS, _10);
	   	Card card4(DIAMONDS, _9);
	   	Card card5(HEARTS, _10);
	   	Card card6(CLUBS, _K);
		Card card7(SPADES, _K);

		twoPairs.push_back(card1);
		twoPairs.push_back(card2);
		twoPairs.push_back(card3);
		twoPairs.push_back(card4);
		twoPairs.push_back(card5);
		twoPairs.push_back(card6);
		twoPairs.push_back(card7);
	}

	//One pair
	//Ks, Kh, 10c, 9d, 8h, Ac, 2s
	vector<Card> onePair;
	
	{
		Card card1(SPADES, _K);
		Card card2(HEARTS, _K);
	   	Card card3(CLUBS, _10);
	   	Card card4(DIAMONDS, _9);
	   	Card card5(HEARTS, _8);
	   	Card card6(CLUBS, _A);
		Card card7(SPADES, _2);

		onePair.push_back(card1);
		onePair.push_back(card2);
		onePair.push_back(card3);
		onePair.push_back(card4);
		onePair.push_back(card5);
		onePair.push_back(card6);
		onePair.push_back(card7);
	}

	//High card
	//Ks, 3h, 10c, 9d, 8h, Ac, 2s
	vector<Card> highCard;
	
	{
		Card card1(SPADES, _K);
		Card card2(HEARTS, _3);
	   	Card card3(CLUBS, _10);
	   	Card card4(DIAMONDS, _9);
	   	Card card5(HEARTS, _8);
	   	Card card6(CLUBS, _A);
		Card card7(SPADES, _2);

		highCard.push_back(card1);
		highCard.push_back(card2);
		highCard.push_back(card3);
		highCard.push_back(card4);
		highCard.push_back(card5);
		highCard.push_back(card6);
		highCard.push_back(card7);
	}

	vector<HandPower> hpVec;

	hpVec.push_back(HandPowerRank(straightFlush));
	hpVec.push_back(HandPowerRank(fourOfAKind));
	hpVec.push_back(HandPowerRank(fullHouse));
	hpVec.push_back(HandPowerRank(flush));
	hpVec.push_back(HandPowerRank(straight));
	hpVec.push_back(HandPowerRank(threeOfAKind));
	hpVec.push_back(HandPowerRank(twoPairs));
	hpVec.push_back(HandPowerRank(onePair));
	hpVec.push_back(HandPowerRank(highCard));


	for(vector<HandPower>::iterator it = hpVec.begin(); it != hpVec.end(); it++)
	{
		cout << "HandPowerType: " << it->getHandPowerType() << endl;
		cout << "tieBreakingInformation: " ;
		vector<Point> tieBreakingInformation = it->getTieBreakingInformation();
		for(vector<Point>::iterator it_tbi = tieBreakingInformation.begin(); it_tbi != tieBreakingInformation.end(); it_tbi++)
		{
			cout << *it_tbi << " ";
		}

		cout << endl;
		cout << endl;
	}

	return 0;
}

