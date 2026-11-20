#pragma once

#include <string>
#include "curses.h"
#include "maps.h"
#include "character.h"
#include "player_vars.h"
#include <cmath>
using namespace std;

#define GAME_WIDTH 48
#define GAME_HEIGHT 24

#define TEXTBOX_WIDTH 48
#define TEXTBOX_HEIGHT 5

#define ITEM_WIDTH 20
#define ITEM_HEIGHT 19

#define PARTY_WIDTH 20
#define PARTY_HEIGHT 10

#define QUESTS_WIDTH 24
#define QUESTS_HEIGHT 13

#define MAP_H 10
#define MAP_W 10

typedef struct {
    int x, y;
    int dir;
} Player;


inline string titolo = "Textbox";
inline string titolo2 = "Items";
inline string titolo3 = "Party";
inline string titolo4 = "Quests";

inline int page_offset = 1;
inline int item_per_page = 8;
inline int max_item_page;
inline int selected = 0;

void print_gui(WINDOW* win1, WINDOW* win2, WINDOW* party_win, WINDOW* quests_win);
void render_minimap(WINDOW *win, Player p);
void draw_player_team_status(std::vector<Character> party, WINDOW* party_win);
void set_text(WINDOW* textbox, std::string message);
void draw_inventory(WINDOW* inventory_win);
