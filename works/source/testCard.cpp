#include "Card.h"
#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

int main()
{
	string cl1 = "CLUBS";
	string pt1 = "A";

	string cl2 = "DIAMONDS";
	string pt2 = "K";

	Color cl1_ = str_to_color(cl1);
	Color cl2_ = str_to_color(cl2);
	Point pt1_ = str_to_point(pt1);
	Point pt2_ = str_to_point(pt2);

	Card card1(cl1_, pt1_);
	Card card2(cl2_, pt2_);

	cout << "card1: " << card1.getColor() << " " << card1.getPoint() << endl;
	cout << "card2: " << card2.getColor() << " " << card2.getPoint() << endl;
	cout << "card1.compareTo(card2): " << card1.compareTo(card2) << endl;

	cout << "card1 == card2: " << std::boolalpha << (card1 == card2) << endl;
	
	Card card3(card1.getColor(), card1.getPoint());
	cout << "card1 == card3: " << (card1 == card3) << endl;

	return 0;
}
