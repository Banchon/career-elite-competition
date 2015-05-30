#include "decision.h"
#include <vector>
#include "Card.h"
#include "HandPower.h"
#include "Deck.h"
#include "HandPowerRank.h"
#include "texasHoldem.h"
#include <cmath>

using std::vector;

#ifdef TEST
#include <iostream>
using std::cout;
using std::endl;
#endif

HandStrength HandStrengthEvaluator(vector<Card> playerHoleCards, vector<Card> sharedCards)
{
	HandStrength handStrength;
	handStrength.wins = 0;
	handStrength.losses = 0;
	handStrength.ties = 0;

	vector<Card> playerCards;
	Deck deck;

	for(vector<Card>::iterator it = playerHoleCards.begin(); it != playerHoleCards.end(); it++) {
		playerCards.push_back(*it);
		deck.removeCard(*it);
	}

	for(vector<Card>::const_iterator it = sharedCards.begin(); it != sharedCards.end(); it++) {
		playerCards.push_back(*it);
		deck.removeCard(*it);
	}

	HandPower playerRank = HandPowerRank(playerCards);

	vector<vector<Card> > couplesOfCard = deck.fromDeckToCouplesOfCard();

	for(vector<vector<Card> >::iterator it = couplesOfCard.begin(); it != couplesOfCard.end(); it++) {
		vector<Card> opponentCards = *it;

		for(vector<Card>::iterator it_sc = sharedCards.begin(); it_sc != sharedCards.end(); it_sc++) {
			opponentCards.push_back(*it_sc);
		}

		HandPower opponentRank = HandPowerRank(opponentCards);

		int result = playerRank.compareTo(opponentRank);
		if(result > 0)
			handStrength.wins++;
		else if(result < 0)
			handStrength.losses++;
		else
			handStrength.ties++;
	}

	return handStrength;
}


double calculateHandStrength(HandStrength hs, int numberOfPlayers)
{
	double num = hs.wins + 0.5 * hs.ties;
	double den = hs.wins + hs.losses + hs.ties;

//	double power = std::ceil(numberOfPlayers / 3);
#ifdef TEST
	cout << "num / den : " << (num / den) << endl;
#endif

	return std::pow(num / den, numberOfPlayers);
}

BettingDecision decideAfterFlop(vector<Card> playerHoleCards, vector<Card> sharedCards, int numberOfPlayers, bool isRiverRound)
{
	HandStrength hs = HandStrengthEvaluator(playerHoleCards, sharedCards);

	double p = calculateHandStrength(hs, numberOfPlayers);

#ifdef TEST
	cout << "first p: " << p << endl;
	cout << "numberOfPlayers: " << numberOfPlayers << endl;
#endif

	//Decision must depends on the number of players
	
	p = p * (1 + (numberOfPlayers / 20.0));


	//Last round, why not?
	if(isRiverRound == true)
		p += 0.3;

	//Lot of raises, be careful
	//
	//
	//
#ifdef TEST
	cout << "second p: " << p << endl;
#endif
	
	if (p > 0.8)
		return RAISE_DECISION;
	else if(p > 0.4)
		return CALL_DECISION;
	else
		return FOLD_DECISION;
}
	
