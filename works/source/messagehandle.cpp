#include <vector>
#include <string>
#include <stdio.h>
#include "texasHoldem.h"
#include "Card.h"
#include <map>

#ifdef DEBUG
#include <iostream>
using std::cout;
using std::endl;
#endif

using std::string;
using std::vector;
using std::map;

int freshPlayersState(vector<string>& message, map<string, Action>& playerStates) {
	//fresh the players state.
}

double billChenValue(int hold_cards[][2])
{
	double value = 0.0;

	if(hold_cards[0][1] < hold_cards[1][1]) {
		int temp_color = hold_cards[0][0];
		int temp_point = hold_cards[0][1];
		hold_cards[0][0] = hold_cards[1][0];
		hold_cards[0][1] = hold_cards[1][1];
		hold_cards[1][0] = temp_color;
		hold_cards[1][1] = temp_point;
	}

	if(hold_cards[0][1] <= 10)
		value = (double)hold_cards[0][1] / 2;
	else if(hold_cards[0][1] == 14)
		value = 10;
	else if(hold_cards[0][1] == 13)
		value = 8;
	else if(hold_cards[0][1] == 12)
		value = 7;
	else if(hold_cards[0][1] == 11)
		value = 6;

	if(hold_cards[0][1] == hold_cards[1][1]) {
		value *= 2;

		if(value < 5)
			value = 5;
	}

	//check for suits.
	if(hold_cards[0][0] == hold_cards[1][0]) {
		value += 2;
	}

	int difference = hold_cards[0][1] - hold_cards[1][1];

	if(difference == 0) {
		//do nothing.
	}
	else if(difference == 1) {
		value += 1;
	}
	else if(difference == 2) {
		value -= 1;
	}
	else if(difference == 3) {
		value -= 2;
	}
	else if(difference == 4) {
		value -= 4;
	}
	else {
		value -= 5;
	}

	return value;
}

int seat_info_msg_handle(vector<string>& message, BasicInfo& basic_info)
{
	string pid = basic_info.pid;
	basic_info.total_player = message.size() - 2;
	basic_info.action_state = 0;

	for(vector<string>::size_type i = 0; i < message.size(); i++) {
		
		string::size_type pid_index = message[i].find(pid);

		if(pid_index != string::npos && ( pid_index == 0
			|| (pid_index == message[i].find(":") + 2))) {
			
			basic_info.seat = i - 1;

			string::size_type jetton_index = message[i].find(" ", pid_index) + 1;
			string::size_type jetton_end = message[i].find(" ", jetton_index);
			string::size_type money_index = jetton_end + 1;
			string::size_type money_end = message[i].find(" ", money_index);

			string jetton = message[i].substr(jetton_index, jetton_end - jetton_index);
			string money = message[i].substr(money_index, money_end - money_index);

			basic_info.jetton = std::stoi(jetton);
			basic_info.money = std::stoi(money);
#ifdef DEBUG
			cout << "-----new hand-----" << endl;
			cout << "total players: " << basic_info.total_player << endl;
			cout << "jetton: " << basic_info.jetton << endl;
			cout << "money: " << basic_info.money << endl;
			cout << jetton << ":jetton.length(): " << jetton.length() << endl;
			cout << money << ":money.length(): " << money.length() << endl;
			cout << "------------------" << endl;
#endif

			return 0;
		}		
	}

	return -1;
}

int blind_msg_handle(vector<string>& message, BasicInfo& basic_info)
{
	/*
	if(basic_info.seat == 1)
		basic_info.jetton -= 50;
	if(basic_info.seat == 2)
		basic_info.jetton -= 100;
	*/
	return 0;
}

int hold_cards_msg_handle(vector<string>& message, BasicInfo& basic_info)
{
	basic_info.phase = 0;

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

	basic_info.hold_cards[0][0] = str_to_color(color_1);
	basic_info.hold_cards[1][0] = str_to_color(color_2);
	basic_info.hold_cards[0][1] = str_to_point(point_1);
	basic_info.hold_cards[1][1] = str_to_point(point_2);

	basic_info.hold_cards_value = billChenValue(basic_info.hold_cards);

#ifdef DEBUG
	cout << "-----hold_cards_msg_handle-----" << endl;
	cout << "original hand cards: " << endl;
	cout << color_1 << " " << point_1 << " " << point_1.length() << endl;
	cout << color_2 << " " << point_2 << " " << point_2.length() << endl;
	cout << "hand cards after processed: " << endl;
	cout << basic_info.hold_cards[0][0] << " " << basic_info.hold_cards[0][1] << endl;
	cout << basic_info.hold_cards[1][0] << " " << basic_info.hold_cards[1][1] << endl;
	cout << "hold_cards_value: " << basic_info.hold_cards_value << endl;
	cout << "-------------------------------" << endl;
#endif
	return 0;
}

//more argument needed to perform better action.
//below are extremely stupid all-in method
int inquire_msg_handle(vector<string>& message, BasicInfo& basic_info, FILE *localSocketStream)
{
	if(basic_info.action_state == 0) {
		if(basic_info.phase == 0) {  //pre-flop
			 if(basic_info.hold_cards_value < 8) {
			 	const string fold = "fold \n";
			 	::fputs(fold.c_str(), localSocketStream);
			 	::fflush(localSocketStream);
			 	basic_info.action_state = 2;
			 }
			 else {
			 	const string call = "call \n";
			 	::fputs(call.c_str(), localSocketStream);
			 	::fflush(localSocketStream);
			 }

		}
		else if(basic_info.phase == 1) { //flop
			const string call = "call \n";
			::fputs(call.c_str(), localSocketStream);
			::fflush(localSocketStream);

		}
		else if(basic_info.phase == 2) { //turn
			const string call = "call \n";
			::fputs(call.c_str(), localSocketStream);
			::fflush(localSocketStream);

		}
		else if(basic_info.phase == 3) { //river
			const string call = "call \n";
			::fputs(call.c_str(), localSocketStream);
			::fflush(localSocketStream);
		}
		else {

		}
	}
	else if(basic_info.action_state == 1) { //all-in

	}
	else if(basic_info.action_state == 2) { //fold
	}
	else {

	}

	return 0;
}

int flop_msg_handle(vector<string>& message, BasicInfo& basic_info)
{
	basic_info.phase = 1;
	
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

	basic_info.flop_cards[0][0] = str_to_color(color_1);
	basic_info.flop_cards[1][0] = str_to_color(color_2);
	basic_info.flop_cards[2][0] = str_to_color(color_3);

	basic_info.flop_cards[0][1] = str_to_point(point_1);
	basic_info.flop_cards[1][1] = str_to_point(point_2);
	basic_info.flop_cards[2][1] = str_to_point(point_3);

	return 0;
}

int turn_msg_handle(vector<string>& message, BasicInfo& basic_info)
{
	basic_info.phase = 2;

	string::size_type color_1_end = message[1].find(" ");

	string::size_type point_1_index = color_1_end + 1;
	string::size_type point_1_end = message[1].find(" ", point_1_index);

	string color_1 = message[1].substr(0, color_1_end - 0);
	string point_1 = message[1].substr(point_1_index, point_1_end - point_1_index);

	basic_info.turn_cards[0] = str_to_color(color_1);
	basic_info.turn_cards[1] = str_to_point(point_1);

	return 0;
}

int river_msg_handle(vector<string>& message, BasicInfo& basic_info)
{
	basic_info.phase = 3;

	string::size_type color_1_end = message[1].find(" ");

	string::size_type point_1_index = color_1_end + 1;
	string::size_type point_1_end = message[1].find(" ", point_1_index);

	string color_1 = message[1].substr(0, color_1_end - 0);
	string point_1 = message[1].substr(point_1_index, point_1_end - point_1_index);

	basic_info.river_cards[0] = str_to_color(color_1);
	basic_info.river_cards[1] = str_to_point(point_1);
	
	return 0;
}

int showdown_msg_handle(vector<string>& message, BasicInfo& basic_info)
{
	basic_info.phase = -1;
	return 0;
}

int pot_win_msg_handle(vector<string>& message, BasicInfo& basic_info)
{
	return 0;
}

int game_over_msg_handle(vector<string>& message)
{
	return 0;
}

int notify_msg_handle(vector<string>& message, BasicInfo& basic_info)
{
	return 0;
}
