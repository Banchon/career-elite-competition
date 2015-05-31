#include "Card.h"

double billChenValueEvaluator(Card holeCards[2])
{
	double value = 0.0;

	if(holeCards[0] < holeCards[1])  {
		Card tempCard = holeCards[0];
		holeCards[0] = holeCards[1];
		holeCards[1] = tempCard;
	}

	if(holeCards[0].getPoint() <= _10)
		value = (double)holeCards[0].getPoint() / 2;
	else if(holeCards[0].getPoint() == _A)
		value = 10;
	else if(holeCards[0].getPoint() == _K)
		value = 8;
	else if(holeCards[0].getPoint() == _Q)
		value = 7;
	else if(holeCards[0].getPoint() == _J)
		value = 6;

	if(holeCards[0].getPoint() == holeCards[1].getPoint()) {
		value *= 2;

		if(value < 5)
			value = 5;
	}

	//check for suits.
	if(holeCards[0].getColor() == holeCards[1].getColor()) {
		value += 2;
	}

	int difference = (int)(holeCards[0].getPoint()) - (int)(holeCards[1].getPoint());

	if(difference == 0) {
		//do nothing.
	}
	else if(difference == 1) {
		value += 1;
	}
	else if(difference == 2) {
		value -= 1;
	}
	else if(difference == 3) {
		value -= 2;
	}
	else if(difference == 4) {
		value -= 4;
	}
	else {
		value -= 5;
	}

	return value;
}
