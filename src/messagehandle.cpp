#include <vector>
#include <string>
#include <stdio.h>

using std::string;
using std::vector;

int seat_info_msg_handle(std::vector<std::string>& message)
{
	return 0;
}

int blind_msg_handle(std::vector<std::string>& message)
{
	return 0;
}

int hold_cards_msg_handle(std::vector<std::string>& message)
{
	return 0;
}

//more argument needed to perform better action.
//below are extremely stupid all-in method
int inquire_msg_handle(std::vector<std::string>& message, FILE *localSocketStream)
{

	const string all_in = "all_in \n";
	::fputs(all_in.c_str(), localSocketStream);
	::fflush(localSocketStream);
	return 0;
}

int flop_msg_handle(std::vector<std::string>& message)
{
	return 0;
}

int turn_msg_handle(std::vector<std::string>& message)
{
	return 0;
}

int river_msg_handle(std::vector<std::string>& message)
{
	return 0;
}

int showdown_msg_handle(std::vector<std::string>& message)
{
	return 0;
}

int pot_win_msg_handle(std::vector<std::string>& message)
{
	return 0;
}
int game_over_msg_handle(std::vector<std::string>& message)
{
	return 0;
}
