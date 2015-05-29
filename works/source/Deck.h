#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <list>
#include <algorithm>
#include <random>
#include <chrono>

class Deck {
	private:
		std::list<Card> cards;

	public:
		Deck()
		{
			for(Color color = SPADES; color <= DIAMONDS; color++) {
				for(Point point = _2; point <= _A; point++) {
					Card card(color, point);
					cards.push_back(card);
				}
			}

			unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
			std::shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));
		}

		std::list<Card> getCards()
		{
			return cards;
		}

		Card removeTopCard() {
			std::list<Card>::iterator it = cards.begin();
			if(it == cards.end())
				return Card(NULLCOLOR, NULLPOINT);

			Card card = *it;
			cards.pop_front();
			return card;
		}

		Card removeCard() {



