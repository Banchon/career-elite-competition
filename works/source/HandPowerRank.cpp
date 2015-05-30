#include <vector>
#include <map>
#include <algorithm>
#include "HandPower.h"
#include "Card.h"
#include "texasHoldem.h"

using std::vector;
using std::map;

vector<Point> cardsToCardPoint(vector<Card> cards);

map<Point, vector<Card> > getPointGroup(vector<Card> cards);

map<Color, vector<Card> > getColorGroup(vector<Card> cards);

vector<Card> getCardsSortedByPoint(vector<Card> cards);

Color getFlush(map<Color, vector<Card> > colorGroup);

Point getStraightPoint(vector<Point> points);

Point getStraightFlushPoint(map<Color, vector<Card> > colorGroup);

Point getCardPointForCount(unsigned count, map<Point, vector<Card> > pointGroup);

vector<Point> calculateSameKindTie(int sameKindCount, Point sameKindCardPoint, vector<Card> cardsSortedByPoint);

vector<Point> getFullHouse(map<Point, vector<Card> > pointGroup);

vector<Point> bestCardsPointInVector(vector<Card> cards);

vector<Point> calculateFlushTie(Color flushColor, map<Color, vector<Card> > colorGroup);

Point getStraight(map<Point, vector<Card> > pointGroup);

vector<Point> getPairs(map<Point, vector<Card> > pointGroup);

vector<Point> calculateTwoPairsTie(vector<Point> pairsCardPoint, vector<Card> cardsSortedByPoint);






vector<Point> cardsToCardPoint(vector<Card> cards)
{
	vector<Point> cardPoints;
	for(vector<Card>::iterator it = cards.begin(); it != cards.end(); it++) {
		cardPoints.push_back(it->getPoint());
	}

	return cardPoints;
}



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



Color getFlush(map<Color, vector<Card> > colorGroup) 
{
	for(map<Color, vector<Card> >::iterator it = colorGroup.begin(); it != colorGroup.end(); it++) {
		if((it->second).size() >= 5)
			return it->first;
	}
	return NULLCOLOR;
}



Point getStraightPoint(vector<Point> points)
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



Point getStraightFlushPoint(map<Color, vector<Card> > colorGroup)
{
	Color flushColor = getFlush(colorGroup);
	if(flushColor == NULLCOLOR) {
		return NULLPOINT;
	}

	vector<Card> cards = colorGroup[flushColor];
	vector<Point> cardPoints = cardsToCardPoint(cards);

	return getStraightPoint(cardPoints);
}

Point getCardPointForCount(unsigned count, map<Point, vector<Card> > pointGroup) 
{
	for(map<Point, vector<Card> >::iterator it = pointGroup.begin(); it != pointGroup.end(); it++) {
		if((it->second).size() == count)
			return it->first;
	}

	return NULLPOINT;
}



vector<Point> calculateSameKindTie(int sameKindCount, Point sameKindCardPoint, vector<Card> cardsSortedByPoint) 
{
	vector<Point> tieBreakingInformation;
	tieBreakingInformation.push_back(sameKindCardPoint);

	int left = 5 - sameKindCount;

	for(int i = cardsSortedByPoint.size() - 1; i >= 0; i--) {
		Card card = cardsSortedByPoint[i];

		if(card.getPoint() != sameKindCardPoint && left > 0) {
			tieBreakingInformation.push_back(card.getPoint());
			left--;
		}

	}

	return tieBreakingInformation;
}



vector<Point> getFullHouse(map<Point, vector<Card> > pointGroup)
{
	vector<Point> fullHouseCardPoints;
	vector<Point> cardPoints;
	for(map<Point, vector<Card> >::iterator it = pointGroup.begin(); it != pointGroup.end(); it++) {
		cardPoints.push_back(it->first);
	}

	std::sort(cardPoints.begin(), cardPoints.end());
	std::reverse(cardPoints.begin(), cardPoints.end());

	for(vector<Point>::iterator it = cardPoints.begin(); it != cardPoints.end(); it++) {
		if(pointGroup[*it].size() >= 3) {
				fullHouseCardPoints.push_back(*it);
				break;
				}
	}

	if(fullHouseCardPoints.size() > 0) {
		for(vector<Point>::iterator it = cardPoints.begin(); it != cardPoints.end(); it++) {
			if((pointGroup[*it].size() >= 2) && (*it != fullHouseCardPoints[0])) {
				fullHouseCardPoints.push_back(*it);
				break;
			}
		}
	}

	return fullHouseCardPoints;
}



vector<Point> bestCardsPointInVector(vector<Card> cards)
{
	vector<Point> cardPoints = cardsToCardPoint(cards);
	std::sort(cardPoints.begin(), cardPoints.end());
	std::reverse(cardPoints.begin(), cardPoints.end());

	vector<Point> retVec;
	int pointNum = 0;
	for(vector<Point>::iterator it = cardPoints.begin(); it != cardPoints.end(); it++) {
		retVec.push_back(*it);
		pointNum++;
		if(pointNum == 5)
			break;
	}

	return retVec;
}



vector<Point> calculateFlushTie(Color flushColor, map<Color, vector<Card> > colorGroup)
{
	vector<Card> cards = colorGroup[flushColor];
	return bestCardsPointInVector(cards);
}



Point getStraight(map<Point, vector<Card> > pointGroup)
{
	vector<Point> cardPoints;
	for(map<Point, vector<Card> >::iterator it = pointGroup.begin(); it != pointGroup.end(); it++) {
		cardPoints.push_back(it -> first);
	}

	return getStraightPoint(cardPoints);
}



vector<Point> getPairs(map<Point, vector<Card> > pointGroup)
{
	vector<Point> pairsCardPoint;
	for(map<Point, vector<Card> >::iterator it = pointGroup.begin(); it != pointGroup.end(); it++) {
		if((it->second).size() == 2) {
			pairsCardPoint.push_back(it->first);
		}
	}

	std::sort(pairsCardPoint.begin(), pairsCardPoint.end());
	std::reverse(pairsCardPoint.begin(), pairsCardPoint.end());

	vector<Point> retVec;
	int pairNum = 0;
	for(vector<Point>::iterator it = pairsCardPoint.begin(); it != pairsCardPoint.end(); it++) {
		retVec.push_back(*it);
		pairNum++;
		if(pairNum == 2)
			break;
	}

	return retVec;
}



vector<Point> calculateTwoPairsTie(vector<Point> pairsCardPoint, vector<Card> cardsSortedByPoint) 
{
	vector<Point> tieBreakingInformation = pairsCardPoint;

	for(int i = cardsSortedByPoint.size() - 1; i >= 0; i--) {
		if(std::find(pairsCardPoint.begin(), pairsCardPoint.end(), cardsSortedByPoint[i].getPoint()) == pairsCardPoint.end()) {
			tieBreakingInformation.push_back(cardsSortedByPoint[i].getPoint());
			return tieBreakingInformation;
		}
	}

	return tieBreakingInformation;
}


HandPower HandPowerRank(vector<Card> cards)
{
	map<Point, vector<Card> > pointGroup = getPointGroup(cards);
	map<Color, vector<Card> > colorGroup = getColorGroup(cards);
	vector<Card> cardsSortedByPoint = getCardsSortedByPoint(cards);

	//Straight flush
	Point straightFlushPoint = getStraightFlushPoint(colorGroup);
	if(straightFlushPoint != NULLPOINT) {
		vector<Point> vec;
		vec.push_back(straightFlushPoint);
		return HandPower(STRAIGHT_FLUSH, vec);
	}

	//Four of a kind
	Point cardPointForFour = getCardPointForCount(4, pointGroup);
	if(cardPointForFour != NULLPOINT) {
		vector<Point> vec = calculateSameKindTie(4, cardPointForFour, cardsSortedByPoint);
		return HandPower(FOUR_OF_A_KIND, vec);
	}

	//Full House
	vector<Point> fullHouseCardPoints = getFullHouse(pointGroup);
	if(fullHouseCardPoints.size() == 2) {
		return HandPower(FULL_HOUSE, fullHouseCardPoints);
	}

	//Flush
	Color flushColor = getFlush(colorGroup);
	if(flushColor != NULLCOLOR) {
		return HandPower(FLUSH, calculateFlushTie(flushColor, colorGroup));
	}

	//Straight
	Point straightPoint = getStraight(pointGroup);
	if(straightPoint != NULLPOINT) {
		vector<Point> vec;
		vec.push_back(straightPoint);
		return HandPower(STRAIGHT, vec);
	}
		
	//Three of a kind
	Point cardPointForThree = getCardPointForCount(3, pointGroup);
	if(cardPointForThree != NULLPOINT) {
		return HandPower(THREE_OF_A_KIND, calculateSameKindTie(3, cardPointForThree, cardsSortedByPoint));
	}


	//Pair(s)
	Point cardPointForTwo = getCardPointForCount(2, pointGroup);
	if(cardPointForTwo != NULLPOINT) {
		vector<Point> pairsCardPoint = getPairs(pointGroup);

		//Two pair
		if(pairsCardPoint.size() == 2) {
			return HandPower(TWO_PAIR, calculateTwoPairsTie(pairsCardPoint, cardsSortedByPoint));
		}

		//One pair
		if(pairsCardPoint.size() == 1) {
			return HandPower(ONE_PAIR, calculateSameKindTie(2, cardPointForTwo, cardsSortedByPoint));
		}
	}

	//High card
	return HandPower(HIGH_CARD, bestCardsPointInVector(cardsSortedByPoint));
	
}

