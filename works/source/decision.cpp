#include <vector>
#include "texasHoldem.h"
#include <cmath>

using std::vector;

#ifdef DEBUG
#include <iostream>
using std::cout;
using std::endl;
#endif


BettingDecision decidePreFlop(double billChenValue, int totalPlayerNum, int currentPlayerNum, int lastRoundBetIncrement, int lastRoundSelfBet)
{
	BettingDecision bettingDecision;
	if(lastRoundSelfBet <= 400) {

	}
	else if(lastRoundSelfBet <= 600) {
		billChenValue -= 1;
	}
	else if(lastRoundSelfBet <= 800) {
		billChenValue -= 2;
	}
	else if(lastRoundSelfBet <= 1000) {
		billChenValue -= 3;
	}
	else {
		billChenValue -= 4;
	}

	//if total player num less than 3, be more aggresive
	if(totalPlayerNum <= 3)
		billChenValue += 2;

	//be careful if the lastRoundBetIncrement is very big.
	if(lastRoundBetIncrement >= 1000) {
		billChenValue -= 1;
		if(currentPlayerNum > 3)
			billChenValue -= 3;
	}
	
	if(billChenValue >= 9)
		bettingDecision = RAISE_DECISION;
	else if(billChenValue >= 6)
		bettingDecision = CALL_DECISION;
	else
		bettingDecision = FOLD_DECISION;


	return bettingDecision;
}



BettingDecision decideAfterFlop(HandStrength hs, int totalPlayerNum, int numberOfPlayers, int raisePlayerNum, int lastRoundBetIncrement, int lastRoundSelfBet, bool isRiverRound)
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
	//be careful when bet too many
	if(lastRoundSelfBet <= 600) {

	}
	else if(lastRoundSelfBet <= 900) {
		p -= 0.1;
	}
	else if(lastRoundSelfBet <= 1200) {
		p -= 0.2;
	}
	else {
		p -= 0.3;
	}
	
	
	if(totalPlayerNum <= 3 )
		p += 0.2;



	
	if (p > 0.8)
		bettingDecision =  RAISE_DECISION;
	else if(p > 0.4)
		bettingDecision = CALL_DECISION;
	else
		bettingDecision = FOLD_DECISION;

	return bettingDecision;
}
