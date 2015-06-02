#ifndef DECISION_H
#define DECISION_H

#include <vector>
#include "texasHoldem.h"


BettingDecision decidePreFlop(double billChenValue, int currentPlayerNum, int lastRoundBetIncrement);


BettingDecision decideAfterFlop(HandStrength hs, int numberOfPlayers, int raisePlayerNum, int lastRoundBetIncrement, bool isRiverRound);

#endif
