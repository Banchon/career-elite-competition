#include "Card.h"
#include <string>

using std::string;

Color str_to_color(const string color)
{
	if(color == "SPADES")
		return SPADES;
	else if(color == "HEARTS")
		return HEARTS;
	else if(color == "CLUBS")
		return CLUBS;
	else if(color == "DIAMONDS")
		return DIAMONDS;
	else
		return NULLCOLOR;
}


Point str_to_point(const string point)
{
	if(point == "2")
		return _2;
	else if(point == "3")
		return _3;
	else if(point == "4")
		return _4;
	else if(point == "5")
		return _5;
	else if(point == "6")
		return _6;
	else if(point == "7")
		return _7;
	else if(point == "8")
		return _8;
	else if(point == "9")
		return _9;
	else if(point == "10")
		return _10;
	else if(point == "J")
		return _J;
	else if(point == "Q")
		return _Q;
	else if(point == "K")
		return _K;
	else if(point == "A")
		return _A;
	else 
		return NULLPOINT;
}

bool operator<(Card card1, Card card2)
{
	int point1 = card1.point;
	int point2 = card2.point;

	return point1 < point2;
}
