#include <vector>
#include "Card.h"
#include "Deck.h"
#include "texasHoldem.h"
#include "HandPower.h"
#include "HandPowerRank.h"


using std::vector;

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


