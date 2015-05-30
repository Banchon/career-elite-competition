#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <random>
#include <algorithm>
#include <vector>

class Deck {
	private:
		std::vector<Card> cards;

	public:
		Deck()
		{
			std::vector<Color> allColor{SPADES, HEARTS, CLUBS, DIAMONDS};
			std::vector<Point> allPoint{_2, _3, _4, _5, _6, _7, _8, _9, _10,
				_J, _Q, _K, _A};
			
			for(std::vector<Color>::iterator it_c = allColor.begin(); it_c != allColor.end(); it_c++) {
				for(std::vector<Point>::iterator it_p = allPoint.begin(); it_p != allPoint.end(); it_p++) {
					Card card(*it_c, *it_p);
					cards.push_back(card);
				}
			}
		}

		std::vector<Card> getCards()
		{
			return cards;
		}

		Card removeTopCard() {
			std::vector<Card>::iterator it = cards.begin();
			if(it == cards.end())
				return Card(NULLCOLOR, NULLPOINT);

			Card card = *it;
			cards.erase(it);
			return card;
		}

		Card removeCard(Card card)
		{
			std::vector<Card>::iterator it;
			it = std::find(cards.begin(), cards.end(), card);

			if(it == cards.end())
				return Card(NULLCOLOR, NULLPOINT);

			cards.erase(it);

			return card;
		}

		std::vector<std::vector<Card> > fromDeckToCouplesOfCard()
		{
			std::vector<std::vector<Card> > couplesOfCard;

			std::vector<Card>::size_type i, j;
			for(i = 0; i < cards.size(); i++) {
				for(j = i + 1; j < cards.size(); j++) {
					std::vector<Card> tmpCards;
					tmpCards.push_back(cards[i]);
					tmpCards.push_back(cards[j]);
					couplesOfCard.push_back(tmpCards);
				}
			}

			return couplesOfCard;
		}
};

#endif
