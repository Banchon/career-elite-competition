#ifndef HANDPOWER_H
#define HANDPOWER_H

#include "Card.h"
#include <vector>
#include "texasHoldem.h"


class HandPower {
private:
	HandPowerType handPowerType;
	std::vector<Point> tieBreakingInformation; 
public:
	HandPower(HandPowerType handPowerType, std::vector<Point> tieBreakingInformation)
	{
		this->handPowerType = handPowerType;
	//	std::sort(tieBreakingInformation.begin(), tieBreakingInformation.end());
		this->tieBreakingInformation = tieBreakingInformation;
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
		int typeDifference = handPowerType - other.handPowerType;

		if(typeDifference == 0) {
			for(std::vector<Point>::size_type i = 0; i < tieBreakingInformation.size(); i++) {
				int tieDifference = tieBreakingInformation[i] - other.tieBreakingInformation[i];
				if(tieDifference != 0)
					return tieDifference;
			}
		}
		return typeDifference;
	}
};
#endif
