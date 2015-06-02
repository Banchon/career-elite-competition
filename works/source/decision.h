#ifndef DECISION_H
#define DECISION_H

#include <vector>
#include "texasHoldem.h"


BettingDecision decidePreFlop(double billChenValue, int totalPlayerNum, int currentPlayerNum, int lastRoundBetIncrement, int lastRoundSelfBet);


BettingDecision decideAfterFlop(HandStrength hs, int totalPlayerNum, int numberOfPlayers, int raisePlayerNum, int lastRoundBetIncrement, int lastRoundSelfBet, bool isRiverRound);

#endif
