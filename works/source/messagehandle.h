#ifndef MESSAGEHANDLE_H
#define MESSAGEHANDLE_H

#include <vector>
#include <string>
#include <stdio.h>
#include "cards.h"

int seat_info_msg_handle(std::vector<std::string>& message, BasicInfo& basic_info);

int blind_msg_handle(std::vector<std::string>& message);

int hold_cards_msg_handle(std::vector<std::string>& message);

int inquire_msg_handle(std::vector<std::string>& message, FILE *);  //more argument needed to perform better action.

int flop_msg_handle(std::vector<std::string>& message);

int turn_msg_handle(std::vector<std::string>& message);

int river_msg_handle(std::vector<std::string>& message);

int showdown_msg_handle(std::vector<std::string>& message);

int pot_win_msg_handle(std::vector<std::string>& message);

int game_over_msg_handle(std::vector<std::string>& message);

int notify_msg_handle(std::vector<std::string>& message);

#endif
