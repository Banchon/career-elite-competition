#ifndef MESSAGEHANDLE_H
#define MESSAGEHANDLE_H

#include <vector>
#include <string>
#include <stdio.h>
#include "texasHoldem.h"

int seat_info_msg_handle(std::vector<std::string>& message, BasicInfo& basicInfo);

int blind_msg_handle(std::vector<std::string>& message, BasicInfo& basicInfo);

int hold_cards_msg_handle(std::vector<std::string>& message, BasicInfo& basicInfo);

int inquire_msg_handle(std::vector<std::string>& message, BasicInfo& basicInfo, FILE *localSocketStream);  //more argument needed to perform better action.

int flop_msg_handle(std::vector<std::string>& message, BasicInfo& basicInfo);

int turn_msg_handle(std::vector<std::string>& message, BasicInfo& basicInfo);

int river_msg_handle(std::vector<std::string>& message, BasicInfo& basicInfo);

int showdown_msg_handle(std::vector<std::string>& message, BasicInfo& basicInfo);

int pot_win_msg_handle(std::vector<std::string>& message, BasicInfo& basicInfo);

int game_over_msg_handle(std::vector<std::string>& message);

int notify_msg_handle(std::vector<std::string>& message, BasicInfo& basicInfo);

#endif
