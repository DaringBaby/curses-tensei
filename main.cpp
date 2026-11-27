#include <string>
#include <vector>
#include <iostream>
#include "include/curses.h"
#include "include/gui.h"
#include "include/renderer.h"
#include "maps.h"
#include "include/player_vars.h"
#include "include/items.h"
using namespace std;

enum game_states {
    FIELD, ITEM_MENU, USE_ITEM_ON_CHAR, SELECT_CHARA_STATUS, STATUS_MENU, EQUIP_SELECTION // others to add
};

int current_state;







int main(int argc, char** argv)
{
    initscr();
    resize_term(32, 105);
    noecho();
    refresh();
    keypad(stdscr, TRUE);
    start_color();
    current_state = game_states::FIELD;
    inventory.clear();
    for (const auto& item : item_db) {
        if (item.type == ItemType::EQUIP) {
            add_item(item.id, 1); //
        } else {
            add_item(item.id, 5); //
        }
    }


    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_WHITE, COLOR_BLACK);


    WINDOW *map_win  = newwin(MAP_H + 6, MAP_W * 2 + 4, 0, 77);
    WINDOW* win1 = newwin(TEXTBOX_HEIGHT, TEXTBOX_WIDTH, 24, 25);
    WINDOW* win2 = newwin(ITEM_HEIGHT, ITEM_WIDTH, 0, 1);
    // WINDOW* win3 = newwin(ITEM_HEIGHT, ITEM_WIDTH, 0, 77);
    WINDOW* game_win = newwin(GAME_HEIGHT, GAME_WIDTH, 0, 25);
    WINDOW* party_win = newwin(PARTY_HEIGHT, PARTY_WIDTH, 19, 1);
    WINDOW* quests_win = newwin(QUESTS_HEIGHT, QUESTS_WIDTH, 16, 77);
    WINDOW* chara_status = newwin(STATUS_HEIGHT, STATUS_WIDTH, 1, 38);

    Player p = {1, 1, 1};
    int ch;



    box(game_win, 0, 0);


    party = create_random_party();

    while (1) {
        draw_player_team_status(party, party_win);
        print_gui(win1, win2, party_win, quests_win);
        render_view(game_win, p);
        render_minimap(map_win, p);
        // set_text(win1, "Hola! que tal");
        if (current_state == game_states::STATUS_MENU) {
                draw_character_status(chara_status);
            }
        else if (current_state == game_states::EQUIP_SELECTION) {
        	draw_character_equippable(chara_status, win1);
        }
        ch = getch();

        if (ch == 'q' || ch == 'Q') break;
        int nx = p.x, ny = p.y;


        if (ch == 'u') {
            selected = -1;
            selected_member = -1;
            selected_equip_slot = -1;
            current_state = game_states::FIELD;
        }
        else if (ch == 'i') {
            selected = 0;
            current_state = game_states::ITEM_MENU;
        }
        else if (ch == 'o') {
            selected_member = 0;
            current_state = game_states::SELECT_CHARA_STATUS;
        }

        // interazione
        switch (current_state) {
        case game_states::FIELD:
            if (ch == '\n' || ch == '\r' || ch == KEY_ENTER || ch == ' ') {
                int event =  check_event_present(0, nx, ny);
                if ( event > 0) {
                    if (check_event(event) == 1) {
                        // chest
                        set_text(win1, "You obtained: " +  get_chest_item(event) + ".");
                    }
                }
            }

            if (ch == 'w' || ch == KEY_UP) {
                nx += dx[p.dir];
                ny += dy[p.dir];
            } else if (ch == 's' || ch == KEY_DOWN) {
                nx -= dx[p.dir];
                ny -= dy[p.dir];
            } else if (ch == 'a' || ch == KEY_LEFT) {
                p.dir = (p.dir + 3) % 4; // gira a sinistra
            } else if (ch == 'd' || ch == KEY_RIGHT) {
                p.dir = (p.dir + 1) % 4; // gira a destra
            }
            break;

        case game_states::ITEM_MENU:
            if (ch == KEY_UP && selected > item_per_page * (page_offset-1)) {
                selected--;
            }
            else if (ch == KEY_DOWN && selected < inventory.size()-1 && selected < (page_offset * item_per_page)-1) {
                selected++;
            }
            else if (ch == 'z' && page_offset > 1) {
                page_offset--;
                selected = (item_per_page * page_offset) - 1;
            }
            else if (ch == 'x' && page_offset < max_item_page) {
                page_offset++;
                selected = (item_per_page * (page_offset-1));
            }
            else if (ch == '\n' && get_item_by_id(inventory[selected].item_id).activable_outside_battle) {
                if (get_item_by_id(inventory[selected].item_id).target_number == TargetNumber::ALL) {
                    use_item_on_char(true);
                    use_item(inventory[selected].item_id);
                    selected = 0;
                    page_offset = 1;
                    current_state = game_states::ITEM_MENU;
                }
                else {
                    current_state = game_states::USE_ITEM_ON_CHAR;
                    selected_member = 0;
                }
            }

            show_item_description(win1);
            break;
        case game_states::USE_ITEM_ON_CHAR:
            if (ch == KEY_UP && selected_member > 0) {
                selected_member--;
            }
            else if (ch == KEY_DOWN && selected_member < party.size()-1) {
                selected_member++;
            }
            else if (ch == '\n') {
                use_item_on_char(false);
                selected_member = -1;
                use_item(inventory[selected].item_id);
                selected = 0;
                page_offset = 1;
                current_state = game_states::ITEM_MENU;
            }
            break;
        case game_states::SELECT_CHARA_STATUS:
            if (ch == KEY_UP && selected_member > 0) {
                selected_member--;
            }
            else if (ch == KEY_DOWN && selected_member < party.size()-1) {
                selected_member++;
            }
            else if (ch == '\n') {
            	selected_equip_slot = 0;
                current_state = game_states::STATUS_MENU;
            }
            break;
        case game_states::STATUS_MENU:
        	if (ch == KEY_UP && selected_equip_slot > 0) {
        		selected_equip_slot--;
        	}
        	else if (ch == KEY_DOWN && selected_equip_slot < 6) {
        		selected_equip_slot++;
        	}
        	else if (ch == '\n') {
        		selected_equip = 0;
        		current_state = game_states::EQUIP_SELECTION;
        	}
            break;
        case game_states::EQUIP_SELECTION:
        	if (ch == KEY_UP && selected_equip > 0) {
        		selected_equip--;
        	}
        	else if (ch == KEY_DOWN && selected_equip < max_equip-1) {
        		selected_equip++;
        	}
        	else if (ch == '\n') {
        		std::vector<int> equippable = get_equippable_ids(selected_equip_slot);
        		if (selected_equip >= 0 && selected_equip <(int)equippable.size()) {
        			equip_item_on_char(selected_member, selected_equip_slot, equippable[selected_equip]);	
        		}
        		current_state = game_states::STATUS_MENU;
        	}
        	else if (ch == 'r') {
        		equip_item_on_char(selected_member, selected_equip_slot, 0);
				current_state = game_states::STATUS_MENU;
        	}
        	break;
        }
        // collisione
        if (!is_wall(nx, ny)) {
            p.x = nx;
            p.y = ny;
        }
    }
    delwin(game_win);
    delwin(map_win);
    endwin();
    return 0;
    getch();
    endwin();
    return 0;
}

// TODO: OPEN CHEST
// EVENT SYSTEM
