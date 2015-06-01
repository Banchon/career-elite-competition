#ifdef TEST

#include "cards.h"
#include <vector>
#include "HandPower.h"
#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;
using std::sort;

int main()
{
	std::vector<Point> p1;
	p1.push_back(_8);
	p1.push_back(_J);
	p1.push_back(_K);
	p1.push_back(_A);
	p1.push_back(_2);

	std::vector<Point> p2;
	p2.push_back(_4);
	p2.push_back(_10);
	p2.push_back(_7);
	p2.push_back(_A);
	p2.push_back(_Q);

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

	sort(p1.begin(), p1.end());
	sort(p2.begin(), p2.end());

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
