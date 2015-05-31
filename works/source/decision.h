#ifndef DECISION_H
#define DECISION_H

#include <vector>
#include "texasHoldem.h"


BettingDecision decideAfterFlop(HandStrength hs, int numberOfPlayers, int raisePlayerNum, bool isRiverRound);

BettingDecision decidePreFlop(double billChenValue, Action lastAction);

#endif
