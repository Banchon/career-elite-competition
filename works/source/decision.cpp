#include <vector>
#include "texasHoldem.h"
#include <cmath>

using std::vector;

#ifdef DEBUG
#include <iostream>
using std::cout;
using std::endl;
#endif


BettingDecision decidePreFlop(double billChenValue, int currentPlayerNum, int lastRoundBetIncrement)
{
	BettingDecision bettingDecision;

	//if total player is less than 3, be more aggresive
	if(currentPlayerNum <= 2) {
		billChenValue += 3;
	}
	else if(currentPlayerNum <= 3) {
		billChenValue += 2;
	}
	else {

	}

	//be careful if the lastRoundBetIncrement is very big.
	if(lastRoundBetIncrement >= 1000)
		billChenValue -= 2;
	
	if(billChenValue >= 9)
		bettingDecision = RAISE_DECISION;
	else if(billChenValue >= 6)
		bettingDecision = CALL_DECISION;
	else
		bettingDecision = FOLD_DECISION;


	return bettingDecision;
}



BettingDecision decideAfterFlop(HandStrength hs, int numberOfPlayers, int raisePlayerNum, int lastRoundBetIncrement, bool isRiverRound)
{
	BettingDecision bettingDecision;
	double num = hs.wins + 0.5 * hs.ties;
	double den = hs.wins + hs.losses + hs.ties;

	double p = std::pow(num / den, numberOfPlayers);

	//Decision must depends on the number of players
	
	p = p * (1 + (numberOfPlayers / 20.0));


	//Last round, why not?
	if(isRiverRound == true)
		p += 0.3;

	//Lot of raises, be careful
	if(raisePlayerNum > 3)
		p -= 0.3;

	//lastRoundBetIncrement too high, be careful
	if(lastRoundBetIncrement >= 1000)
		p -= 0.1;

	
	if (p > 0.8)
		bettingDecision =  RAISE_DECISION;
	else if(p > 0.4)
		bettingDecision = CALL_DECISION;
	else
		bettingDecision = FOLD_DECISION;

	return bettingDecision;
}
