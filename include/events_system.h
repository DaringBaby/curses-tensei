#pragma once
#include "maps.h"
#include "items.h"
#include "player_vars.h"
int check_event(int event_id);          // 0: person, 1: chest
bool check_opened_chest(int chest_id);
int check_event_present(int map_id, int p_x, int p_y);
std::string get_chest_item(int chest_id);
