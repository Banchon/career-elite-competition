#ifndef HANDSTRENGTHEVALUATOR_H
#define HANDSTRENGTHEVALUATOR_H

#include <vector>
#include "Card.h"
#include "texasHoldem.h"

HandStrength HandStrengthEvaluator(std::vector<Card> playerCards, std::vector<Card> sharedCards);

#endif
