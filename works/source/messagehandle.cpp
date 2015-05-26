#include <vector>
#include <string>
#include <stdio.h>

using std::string;
using std::vector;

string find_msg_line_of_pid(const vector<string>& message, const string pid)
{
	for(vector<string>::iterator it = message.begin(); it != message.end(); it++) {
		if(it->find(pid) != string::npos) {
			//for robust, we should do more check, because the bet, jetton and money field may equal to pid. 
			return *it;
		}
	}

	return "";
}

int seat_info_msg_handle(vector<string>& message, const string pid; int& seat)
{
	for(vector<string>::size_type i = 0; i < message.size(); i++) {
		string::size_type pid_index = message[i].find(pid);

		if(pid_index != string::npos && ( pid_index == message[i].find(":") + 2) 
			|| pid_index == 0))
			seat = i - 1;
	}
	return 0;
}

int blind_msg_handle(vector<string>& message)
{
	return 0;
}

int hold_cards_msg_handle(vector<string>& message)
{
	return 0;
}

//more argument needed to perform better action.
//below are extremely stupid all-in method
int inquire_msg_handle(vector<string>& message, FILE *localSocketStream)
{

	const string all_in = "all_in \n";
	::fputs(all_in.c_str(), localSocketStream);
	::fflush(localSocketStream);
	return 0;
}

int flop_msg_handle(vector<string>& message)
{
	return 0;
}

int turn_msg_handle(vector<string>& message)
{
	return 0;
}

int river_msg_handle(vector<string>& message)
{
	return 0;
}

int showdown_msg_handle(vector<string>& message)
{
	return 0;
}

int pot_win_msg_handle(vector<string>& message)
{
	return 0;
}

int game_over_msg_handle(vector<string>& message)
{
	return 0;
}

int notify_msg_handle(vector<string>& message)
{
	return 0;
}
