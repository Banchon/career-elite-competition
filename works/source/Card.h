#ifndef CARD_H
#define CARD_H

#include <string>

enum Point {
	NULLPOINT = 0,
	_2 = 2,
	_3 = 3,
	_4 = 4,
	_5 = 5,
	_6 = 6,
	_7 = 7,
	_8 = 8,
	_9 = 9,
	_10 = 10,
	_J = 11,
	_Q = 12,
	_K = 13,
	_A = 14 
};

enum Color {
	NULLCOLOR = 0,
	SPADES = 1,
	HEARTS = 2,
	CLUBS = 3,
	DIAMONDS = 4
};

Color str_to_color(const std::string color);
Point str_to_point(const std::string point);

class Card {
	private:
		Color color;
		Point point;

	public:
		Card(Color cl, Point pt)
		{
			color = cl;
			point = pt;
		}

		bool equals(Card other)
		{
			return color == other.color && point == other.point;
		}

		int compareTo(Card other)
		{
			return point - other.point;
		}

		Color getColor()
		{
			return color;
		}

		Point getPoint()
		{
			return point;
		}

		bool operator==(Card other) {
			return equals(other);
		}
};
#endif
