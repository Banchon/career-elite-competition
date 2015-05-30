#ifndef DECISION_H
#define DECISION_H

#include "HandPower.h"
#include <vector>
#include "Card.h"
#include "texasHoldem.h"

typedef struct HandStrength {
	int wins;
	int losses;
	int ties;
}HandStrength;

HandStrength HandStrengthEvaluator(HandPower hp, std::vector<Card> playerHoleCards, std::vector<Card> sharedCards);


double calculateHandStrength(HandStrength hs, int numberOfPlayers);


BettingDecision decideAfterFlop(std::vector<Card> playerHoleCards, std::vector<Card> sharedCards, int numberOfPlayers, bool isRiverRound);


#endif
