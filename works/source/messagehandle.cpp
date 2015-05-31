#include <vector>
#include <string>
#include <stdio.h>
#include "texasHoldem.h"
#include "Card.h"
#include <map>
#include "billChenValueEvaluator.h"
#include "HandStrengthEvaluator.h"
#include "decision.h"

#ifdef DEBUG
#include <iostream>
using std::cout;
using std::endl;
#endif

using std::string;
using std::vector;
using std::map;

#ifdef DEBUG
int printMessage(vector<string>& message)
{
	for(vector<string>::iterator it = message.begin(); it != message.end(); it++)
	{
		cout << *it;
	}

	return 0;
}

int printLastPlayersAction(map<string, Action>& lastPlayersAction)
{
	for(map<string, Action>::iterator it = lastPlayersAction.begin(); it != lastPlayersAction.end(); it++) {
		cout << (it->first) << " " << (it->second) << endl;
	}

	return 0;
}

int printHandStrength(HandStrength hs)
{
	cout << hs.wins << " " << hs.losses << " " << hs.ties << endl;
	return 0;
}
#endif

int freshLastPlayersAction(vector<string>& inquireMessage, map<string, Action>& lastPlayersAction) 
{
	//fresh the players state.
	for(vector<string>::size_type i = 1; i < (inquireMessage.size() - 2); i++) {
		string pid;
		string::size_type pid_index = 0;
		string::size_type pid_end = inquireMessage[i].find(" ");
		pid = inquireMessage[i].substr(pid_index, pid_end - pid_index);
		
		string strAction;
		string::size_type strAction_end = inquireMessage[i].rfind(" ");
		string::size_type strAction_index = inquireMessage[i].rfind(" ", strAction_end - 1) + 1;
		strAction = inquireMessage[i].substr(strAction_index, strAction_end - strAction_index);

		Action action;
		if(strAction == "fold")
			action = FOLD;
		else if(strAction == "blind")
			action = BLIND;
		else if(strAction == "check")
			action = CHECK;
		else if(strAction == "call")
			action = CALL;
		else if(strAction  == "raise")
			action = RAISE;
		else if(strAction == "all_in")
			action = ALL_IN;
		else
			action = NULLACTION;

		lastPlayersAction[pid] = action;
	}
	
	return 0;
}

int getLastRoundBetIncrement(vector<string>& inquireMessage, const string selfpid)
{
	int lastSelfBet = 0;
	
	//find biggestBet
	int biggestBet = 0;

	for(vector<string>::size_type i = 1; i < (inquireMessage.size() - 2); i++) {
		string bet;
		//find the bet index
		string::size_type bet_index = 0;
		for(int j = 0; j < 3; j++)
			bet_index = inquireMessage[i].find(" ", bet_index) + 1;
		//find the bet end
		string::size_type bet_end = inquireMessage[i].find(" ", bet_index);

		bet = inquireMessage[i].substr(bet_index, bet_end - bet_index);

		int betNum = std::stoi(bet);

		if(i == (inquireMessage.size() -3))
			lastSelfBet = betNum;
				
		if(betNum > biggestBet)
			biggestBet = betNum;
	}

	string pid;
	string::size_type pid_index = 0;
	string::size_type pid_end = inquireMessage[inquireMessage.size() - 3].find(" ");
	pid = inquireMessage[inquireMessage.size() - 3].substr(pid_index, pid_end - pid_index);

	if(pid == selfpid)
		return (biggestBet - lastSelfBet);
	else
		return biggestBet;
}
	

int getCurrentPlayerNum(map<string, Action>& lastPlayersAction) 
{
	int currentPlayerNum = 0;
	for(map<string, Action>::iterator it = lastPlayersAction.begin(); it != lastPlayersAction.end(); it++) {
		if(it->second != FOLD && it->second != NULLACTION)
			currentPlayerNum++;
	}

	return currentPlayerNum;
}

int getRaisePlayerNum(map<string, Action>& lastPlayersAction)
{
	int raisePlayerNum = 0;

	for(map<string, Action>::iterator it = lastPlayersAction.begin(); it != lastPlayersAction.end(); it++) {
		if(it->second == RAISE || it->second == ALL_IN)
			raisePlayerNum++;
	}

	return raisePlayerNum;
}


int seat_info_msg_handle(vector<string>& message, BasicInfo& basicInfo)
{
	Card nullCard;
	map<string, Action> nullMap;
	string selfpid = basicInfo.pid;

	basicInfo.currentBettingRound = PRE_FLOP;
	basicInfo.lastSelfAction = NULLACTION;
	basicInfo.holeCards[0] = nullCard;
	basicInfo.holeCards[1] = nullCard;
	basicInfo.flopCards[0] = nullCard;
	basicInfo.flopCards[1] = nullCard;
	basicInfo.flopCards[2] = nullCard;
	basicInfo.turnCard = nullCard;
	basicInfo.riverCard = nullCard;
	basicInfo.lastPlayersAction = nullMap;
	basicInfo.billChenValue = 0.0;
	basicInfo.handStrength.wins = 0;
	basicInfo.handStrength.ties = 0;
	basicInfo.handStrength.losses = 1;
	basicInfo.leastRaiseJetton = 0;

	for(vector<string>::size_type i = 1; i < message.size() - 1; i++) {
		string pid;
		string::size_type pid_index = 0;

		string::size_type colon_index = message[i].find(":");
		if(colon_index != string::npos)
			pid_index = colon_index + 2;

		string::size_type pid_end = message[i].find(" ", pid_index);
		pid = message[i].substr(pid_index, pid_end - pid_index);
		
		basicInfo.lastPlayersAction[pid] = NULLACTION;

		
		if(pid == selfpid) {

			basicInfo.seat = i - 1;

			string::size_type jetton_index = message[i].find(" ", pid_index) + 1;
			string::size_type jetton_end = message[i].find(" ", jetton_index);
			string::size_type money_index = jetton_end + 1;
			string::size_type money_end = message[i].find(" ", money_index);

			string jetton = message[i].substr(jetton_index, jetton_end - jetton_index);
			string money = message[i].substr(money_index, money_end - money_index);

			basicInfo.jetton = std::stoi(jetton);
			basicInfo.money = std::stoi(money);
		}
	}

#ifdef DEBUG
		cout << endl;
		cout << endl;
		cout << "---------------------new hand----------------------" << endl;
		printMessage(message);
		cout << "seat_info_msg_handle: " << endl;
		printLastPlayersAction(basicInfo.lastPlayersAction);
		cout << "seat: " << basicInfo.seat << endl;
		cout << "jetton: " << basicInfo.jetton << endl;
		cout << "money: " << basicInfo.money << endl;
#endif
		return 0;
}


int blind_msg_handle(vector<string>& message, BasicInfo& basicInfo)
{
	for(vector<string>::size_type i = 1; i < message.size() - 1; i++) {
		string blind;
		string::size_type blind_index = message[i].find(" ") + 1;
		string::size_type blind_end = message[i].find(" ", blind_index);

		blind = message[i].substr(blind_index, blind_end - blind_index);

		int blindBet = std::stoi(blind);
		if(basicInfo.leastRaiseJetton < blindBet)
			basicInfo.leastRaiseJetton = blindBet;
	}
#ifdef DEBUG
	printMessage(message);
	cout << "blind_msg_handle: " << endl;
	cout << "leastRaiseJetton: " << basicInfo.leastRaiseJetton << endl;
#endif
	return 0;
}


int hold_cards_msg_handle(vector<string>& message, BasicInfo& basicInfo)
{
	string::size_type color_1_end = message[1].find(" ");
	string::size_type color_2_end = message[2].find(" ");
	string::size_type point_1_index = color_1_end + 1;
	string::size_type point_2_index = color_2_end + 1;
	string::size_type point_1_end = message[1].find(" ", point_1_index);
	string::size_type point_2_end = message[2].find(" ", point_2_index);

	string color_1 = message[1].substr(0, color_1_end - 0);
	string point_1 = message[1].substr(point_1_index, point_1_end - point_1_index);

	string color_2 = message[2].substr(0, color_2_end - 0);
	string point_2 = message[2].substr(point_2_index, point_2_end - point_2_index);

	basicInfo.holeCards[0] = Card(str_to_color(color_1), str_to_point(point_1));
	basicInfo.holeCards[1] = Card(str_to_color(color_2), str_to_point(point_2));

	basicInfo.billChenValue = billChenValueEvaluator(basicInfo.holeCards);

#ifdef DEBUG
	printMessage(message);
	cout << "hold_cards_msg_handle: " << endl;
	for(int i = 0; i < 2; i++) {
		(basicInfo.holeCards[i]).print();
	}
	cout << "billChenValue: " << basicInfo.billChenValue << endl;
#endif	
	return 0;
}

int inquire_msg_handle(vector<string>& message, BasicInfo& basicInfo, FILE *localSocketStream)
{

	freshLastPlayersAction(message, basicInfo.lastPlayersAction);

	map<string, Action>::iterator it = (basicInfo.lastPlayersAction).find(basicInfo.pid);
	if(it != (basicInfo.lastPlayersAction).end())
		basicInfo.lastSelfAction = it->second;

#ifdef DEBUG
	printMessage(message);
	cout << "inquire_msg_handle: " << endl;
	printLastPlayersAction(basicInfo.lastPlayersAction);
	cout << "lastSelfAction: " << basicInfo.lastSelfAction << endl;	
#endif
	
	//send a message when last action is neither ALL_IN or FOLD
	if((basicInfo.lastSelfAction != ALL_IN)  && (basicInfo.lastSelfAction != FOLD)) {

		int lastRoundBetIncrement = getLastRoundBetIncrement(message, basicInfo.pid);
		int currentPlayerNum = getCurrentPlayerNum(basicInfo.lastPlayersAction);
		int raisePlayerNum = getRaisePlayerNum(basicInfo.lastPlayersAction);
		bool isRiverRound = (basicInfo.currentBettingRound == RIVER);
		
		BettingDecision bettingDecision;
		
		//pre_flop decision
		if(basicInfo.currentBettingRound == PRE_FLOP)
			bettingDecision = decidePreFlop(basicInfo.billChenValue, currentPlayerNum, lastRoundBetIncrement);
		
		//After flop decision
		else {
			
			bettingDecision = decideAfterFlop(basicInfo.handStrength, currentPlayerNum, raisePlayerNum, lastRoundBetIncrement, isRiverRound);
		}
		
		string sMessage;
		switch(bettingDecision) {
			case FOLD_DECISION:
				sMessage = "fold \n";
				break;
			case CALL_DECISION:
				sMessage = "call \n";
				break;
			case RAISE_DECISION:
				sMessage = "raise ";
				sMessage.append(std::to_string(basicInfo.leastRaiseJetton));
				sMessage.append(" \n");
				break;
			default:
				break;
		}

		::fputs(sMessage.c_str(), localSocketStream);
		::fflush(localSocketStream);
	}

	return 0;
}

int flop_msg_handle(vector<string>& message, BasicInfo& basicInfo)
{
	basicInfo.currentBettingRound = FLOP;
	
	string::size_type color_1_end = message[1].find(" ");
	string::size_type color_2_end = message[2].find(" ");
	string::size_type color_3_end = message[3].find(" ");

	string::size_type point_1_index = color_1_end + 1;
	string::size_type point_2_index = color_2_end + 1;
	string::size_type point_3_index = color_3_end + 1;

	string::size_type point_1_end = message[1].find(" ", point_1_index);
	string::size_type point_2_end = message[2].find(" ", point_2_index);
	string::size_type point_3_end = message[3].find(" ", point_3_index);

	string color_1 = message[1].substr(0, color_1_end - 0);
	string point_1 = message[1].substr(point_1_index, point_1_end - point_1_index);

	string color_2 = message[2].substr(0, color_2_end - 0);
	string point_2 = message[2].substr(point_2_index, point_2_end - point_2_index);

	string color_3 = message[3].substr(0, color_3_end - 0);
	string point_3 = message[3].substr(point_3_index, point_3_end - point_3_index);

	basicInfo.flopCards[0] = Card(str_to_color(color_1), str_to_point(point_1));
	basicInfo.flopCards[1] = Card(str_to_color(color_2), str_to_point(point_2));
	basicInfo.flopCards[2] = Card(str_to_color(color_3), str_to_point(point_3));

	//evalute HandStrength
	vector<Card> holeCards;
	for(int i = 0; i < 2; i++)
		holeCards.push_back(basicInfo.holeCards[i]);
	vector<Card> sharedCards;
	for(int i = 0; i < 3; i++)
		sharedCards.push_back(basicInfo.flopCards[i]);

	basicInfo.handStrength = HandStrengthEvaluator(holeCards, sharedCards);

#ifdef DEBUG
	printMessage(message);
	cout << "flop_msg_handle: " << endl;
	for(int i = 0; i < 3; i++)
		(basicInfo.flopCards[i]).print();
	cout << "currentBettingRound: " << basicInfo.currentBettingRound << endl;
	printHandStrength(basicInfo.handStrength);
#endif
	return 0;
}

int turn_msg_handle(vector<string>& message, BasicInfo& basicInfo)
{
	basicInfo.currentBettingRound = TURN;

	string::size_type color_1_end = message[1].find(" ");

	string::size_type point_1_index = color_1_end + 1;
	string::size_type point_1_end = message[1].find(" ", point_1_index);

	string color_1 = message[1].substr(0, color_1_end - 0);
	string point_1 = message[1].substr(point_1_index, point_1_end - point_1_index);

	basicInfo.turnCard = Card(str_to_color(color_1), str_to_point(point_1));

	//evaluate HandStrength
	vector<Card> holeCards;
	for(int i = 0; i < 2; i++)
		holeCards.push_back(basicInfo.holeCards[i]);

	vector<Card> sharedCards;
	for(int i = 0; i < 3; i++)
		sharedCards.push_back(basicInfo.flopCards[i]);

	sharedCards.push_back(basicInfo.turnCard);

	basicInfo.handStrength = HandStrengthEvaluator(holeCards, sharedCards);		

#ifdef DEBUG
	printMessage(message);
	cout << "turn_msg_handle: " << endl;
	(basicInfo.turnCard).print();
	cout << "currentBettingRound: " << basicInfo.currentBettingRound << endl;
	printHandStrength(basicInfo.handStrength);
#endif
	return 0;
}

int river_msg_handle(vector<string>& message, BasicInfo& basicInfo)
{
	basicInfo.currentBettingRound = RIVER;

	string::size_type color_1_end = message[1].find(" ");

	string::size_type point_1_index = color_1_end + 1;
	string::size_type point_1_end = message[1].find(" ", point_1_index);

	string color_1 = message[1].substr(0, color_1_end - 0);
	string point_1 = message[1].substr(point_1_index, point_1_end - point_1_index);

	basicInfo.riverCard = Card(str_to_color(color_1), str_to_point(point_1));
	
	//evaluate HandStrength
	vector<Card> holeCards;
	for(int i = 0; i < 2; i++)
		holeCards.push_back(basicInfo.holeCards[i]);

	vector<Card> sharedCards;
	for(int i = 0; i < 3; i++)
		sharedCards.push_back(basicInfo.flopCards[i]);

	sharedCards.push_back(basicInfo.turnCard);
	sharedCards.push_back(basicInfo.riverCard);

	basicInfo.handStrength = HandStrengthEvaluator(holeCards, sharedCards);		
#ifdef DEBUG
	printMessage(message);
	cout << "river_msg_handle: " << endl;
	(basicInfo.riverCard).print();
	cout << "currentBettingRound: " << basicInfo.currentBettingRound << endl;
	printHandStrength(basicInfo.handStrength);
#endif
	return 0;
}

int showdown_msg_handle(vector<string>& message, BasicInfo& basicInfo)
{
#ifdef DEBUG
	printMessage(message);
#endif
	return 0;
}

int pot_win_msg_handle(vector<string>& message, BasicInfo& basicInfo)
{
#ifdef DEBUG
	printMessage(message);
#endif
	return 0;
}

int game_over_msg_handle(vector<string>& message)
{
#ifdef DEBUG
	printMessage(message);
#endif
	return 0;
}

int notify_msg_handle(vector<string>& message, BasicInfo& basicInfo)
{
#ifdef DEBUG
	printMessage(message);
#endif
	return 0;
}
