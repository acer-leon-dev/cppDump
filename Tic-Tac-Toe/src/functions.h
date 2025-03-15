#pragma once

#ifndef TTT_FUNCTIONS_H
#define TTT_FUNCTIONS_H

#include "config.h"

mode prompt_mode();

void number_input(char* board, int player_pos, char player, char opponent);

void bot_input(char* board, char bot, char opponent);

void print_board(char* board);

bool check_win(char* board, int turn, char player);

bool check_replay(char* board);

#endif