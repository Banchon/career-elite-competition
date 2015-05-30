#include <vector>
#include <map>
#include <algorithm>
#include "HandPower.h"
#include "Card.h"
#include "texasHoldem.h"

using std::vector;
using std::map;

map<Point, vector<Card> > getPointGroup(vector<Card> cards)
{
	map<Point, vector<Card> > retMap;
	for(vector<Card>::iterator it = cards.begin(); it != cards.end(); it++) {
		retMap[it->getPoint()].push_back(*it);
	}
	return retMap;
}

map<Color, vector<Card> > getColorGroup(vector<Card> cards)
{
	map<Color, vector<Card> > retMap;
	for(vector<Card>::iterator it = cards.begin(); it != cards.end(); it++) {
		retMap[it->getColor()].push_back(*it);
	}
	return retMap;
}

vector<Card> getCardsSortedByPoint(vector<Card> cards)
{
	vector<Card> retVec = cards;
	std::sort(retVec.begin(), retVec.end());
	return retVec;
}

Color getFlush(map<Color, vector<Card> > colorGroup) {
	for(map<Color, vector<Card> >::iterator it = colorGroup.begin(); it != colorGroup.end(); it++) {
		if((it->second).size() >= 5)
			return it->first;
	}
	return NULLCOLOR;
}

Point getStraightNumber(vector<Point> points)
{
	Point straightPoint = NULLPOINT;
	int straightCount = 1;
	int prePoint = NULLPOINT;

	std::sort(points.begin(), points.end());

	for(vector<Point>::iterator it = points.begin(); it != points.end(); it++) {
		if(*it == prePoint + 1) {
			straightCount++;
			if(straightCount >= 5) {
				straightPoint = *it;
			}
		}
		else {
			straightCount = 1;
		}

		prePoint = *it;
	}

	return straightPoint;
}

Point getStraightFlushPoint()

HandPower HandPowerRank(vector<Card>& cards)
{
	map<Point, vector<Card> > pointGroup = getPointGroup(cards);
	map<Color, vector<Card> > colorGroup = getColorGroup(cards);
	vector<Card> cardsSortedByPoint = getCardsSortedByPoint(cards);

	Point straightFlushPoint = getStraightFlushPoint(colorGroup);

	//Straight flush
	if(straightFlushPoint != NULLPOINT) {
		vector<Point> vec;
		vec.push_back(straightFlushPoint);
		return HandPower(STRAIGHT_FLUSH, vec);
	}

	Point cardPointForFour = getCardPointForCount(4, pointGroup);

	//Four of a kind
	if(cardPointForFour != NULLPOINT) {
		



