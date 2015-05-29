#ifndef MESSAGEHANDLE_H
#define MESSAGEHANDLE_H

#include <vector>
#include <string>
#include <stdio.h>
#include "texasHoldem.h"

int seat_info_msg_handle(std::vector<std::string>& message, BasicInfo& basic_info);

int blind_msg_handle(std::vector<std::string>& message, BasicInfo& basic_info);

int hold_cards_msg_handle(std::vector<std::string>& message, BasicInfo& basic_info);

int inquire_msg_handle(std::vector<std::string>& message, BasicInfo& basic_info, FILE *localSocketStream);  //more argument needed to perform better action.

int flop_msg_handle(std::vector<std::string>& message, BasicInfo& basic_info);

int turn_msg_handle(std::vector<std::string>& message, BasicInfo& basic_info);

int river_msg_handle(std::vector<std::string>& message, BasicInfo& basic_info);

int showdown_msg_handle(std::vector<std::string>& message, BasicInfo& basic_info);

int pot_win_msg_handle(std::vector<std::string>& message, BasicInfo& basic_info);

int game_over_msg_handle(std::vector<std::string>& message);

int notify_msg_handle(std::vector<std::string>& message, BasicInfo& basic_info);

#endif
