#include "Deck.h"
#include "Card.h"
#include <vector>
#include <iostream>

using std::vector;
using std::vector;
using std::cout;
using std::endl;

int main()
{
	Deck deck;


//	for(vector<Card>::iterator it = cards.begin(); it != cards.end(); it++)
//		cout << it->getColor() << " " << it->getPoint() << endl;
	Card topCard = deck.removeTopCard();

	Card card(DIAMONDS, _8);
	deck.removeCard(card);

	cout << topCard.getColor() << " " << topCard.getPoint() << endl;

	cout << endl;

	vector<Card> cards = deck.getCards();
	for(vector<Card>::iterator it = cards.begin(); it != cards.end(); it++)
		cout << it->getColor() << " " << it->getPoint() << endl;
	cout << endl;
	vector<vector<Card> > couplesOfCard = deck.fromDeckToCouplesOfCard();
	for(vector<vector<Card> >::iterator it = couplesOfCard.begin(); it != couplesOfCard.end(); it++) {
		std::cout << (*it)[0].getColor() << " " << (*it)[0].getPoint() << "   "
			<<(*it)[1].getColor() << " " << (*it)[1].getPoint() << endl;
	}

	return 0;
}

