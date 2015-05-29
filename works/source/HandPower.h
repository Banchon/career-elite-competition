#ifndef HANDPOWER_H
#define HANDPOWER_H

#include "cards.h"
#include <vector>
#include <algorithm>

#ifdef TEST
#include <iostream>
using std::cout;
using std::endl;
#endif

class HandPower {
private:
	HandPowerType handPowerType;
	std::vector<Point> tieBreakingInformation; 
public:
	HandPower(HandPowerType handPowerType, std::vector<Point> tieBreakingInformation)
	{
		this.handPowerType = handPowerType;
		this.tieBreakingInformation = std::sort(tieBreakingInformation.cbegin(), tieBreakingInformation.cend());
	}

	HandPowerType getHandPowerType()
	{
		return handPowerType;
	}

	std::vector<Point> getTieBreakingInformation()
	{
		return tieBreakingInformation;
	}

	int compareTo(HandPower other)
	{
		int typeDifference = this.handPowerType - other.handPowerType;

		if(typeDifference == 0) {
			for(int i = 0; i < tieBreakingInformation.size(); i++) {
				int tieDifference = this.tieBreakingInformation[i] - other.tieBreakingInformation[i];
				if(tieDifference != 0)
					return tieDifference;
			}
		}
		return typeDifference;
	}
};
#endif


#ifdef TEST
int main()
{
	std::vector<Point> p1 = {_8, _J, _K, _A, _2};
	std::vector<Point> p2 = {_4, _10, _7, _A, _Q};
	cout << "p1: ";
	for(int i = 0; i < 5; i++) {
		cout << p1[i] << " ";	
	}
	cout << endl;

	cout << "p2: ";
	for(int i = 0; i < 5; i++) {
		cout << p2[i] << " ";
	}
	cout << endl;

	HandPower hp1(HIGH_CARD, p1);
	HandPower hp2(HIGH_CARD, p2);

	std::vector<Point> p1_ = hp1.getTieBreakingInformation();
	std::vector<Point> p2_ = hp2.getTieBreakingInformation();

	cout << "hp1 HandPowerType: " << hp1.getHandPowerType() << endl;
	cout << "hp1 point: ";
	for(int i = 0; i < 5; i++) {
		cout << p1_[i] << " ";
	} 
	cout << endl;

	cout << "hp2 HandPowerType: " << hp2.getHandPowerType() << endl;
	cout << "hp2 point: ";
	for(int i = 0; i < 5; i++) {
		cout << p2_[i] << " ";
	}
	cout << endl;

	cout << "hp1.compareTo(hp2): " << hp1.compareTo(hp2) << endl;

	return 0;
}

#endif