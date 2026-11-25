#include "include/gui.h"
#include "include/character.h"
#include "include/curses.h"
#include "include/items.h"
#include "include/player_vars.h"

void print_gui(WINDOW* win1, WINDOW* win2, WINDOW* party_win, WINDOW* quests_win) {
    box(win1, 0, 0);
    box(win2, 0, 0);
    // box(win3, 0, 0);
    box(party_win, 0, 0);
    box(quests_win, 0, 0);

    mvwprintw(win1, 0, (TEXTBOX_WIDTH - titolo.length())/2, titolo.c_str());
    mvwprintw(win2, 0, (ITEM_WIDTH - titolo2.length())/2, titolo2.c_str());
    mvwprintw(party_win, 0, (PARTY_WIDTH - titolo3.length())/2, titolo3.c_str());
    mvwprintw(quests_win, 0, (QUESTS_WIDTH - titolo4.length())/2, titolo4.c_str());
    // mvwprintw(win3, 0, (ITEM_WIDTH - titolo2.length())/2, "Equip");
    draw_inventory(win2);
    wrefresh(win1);
    wrefresh(win2);
    // wrefresh(win3);
    wrefresh(party_win);
    wrefresh(quests_win);
}

void render_minimap(WINDOW *win, Player p) {
    werase(win);
    box(win, 0, 0);
    mvwprintw(win, 0, 2, " AUTOMAP ");

    char dir_chars[4] = {'^', '>', 'v', '<'};

    for (int y = 0; y < MAP_H; y++) {
        for (int x = 0; x < MAP_W; x++) {
            if (x == p.x && y == p.y) {
                wattron(win, A_BOLD | A_REVERSE);
                mvwaddch(win, y + 2, x * 2 + 2, dir_chars[p.dir]);
                wattroff(win, A_BOLD | A_REVERSE);
            } else {
                char c = sample_map[y][x];
                switch (c) {
                    case 0:
                        c = '.';
                        break;
                    case 1:
                        c = '#';
                        break;
                    case 2:
                        c = '.';
                        break;
                }
                mvwaddch(win, y + 2, x * 2 + 2, c);
            }
        }
    }
    mvwprintw(win, MAP_H + 3, 2, "WASD/Arrows: Move");
    mvwprintw(win, MAP_H + 4, 2, "Q: Exit");
    wrefresh(win);
}

void draw_player_team_status(std::vector<Character> party, WINDOW* party_win) {
    for (int i = 0; i < party.size(); i++) {
        wattron(party_win, COLOR_PAIR(4) | A_BOLD);

        if (selected_member == i) {
            wattron(party_win, A_REVERSE);
        }

        mvwprintw(party_win, 1 + i * 2, 1, party[i].get_name().c_str());



        wattroff(party_win, COLOR_PAIR(4) | A_BOLD);
        mvwprintw(party_win, 1 + i * 2, 12, "Lv. %d", party[i].get_level());

        if (selected_member == i) {
            wattroff(party_win, A_REVERSE);
        }
        mvwprintw(party_win, 2 + 2 * i, 2, "HP:%d/%d MP:%d", party[i].get_hp(), party[i].get_max_hp(), party[i].get_mp());
    }
}


void set_text(WINDOW* textbox, std::string message) {
    mvwprintw(textbox, 1, 2, "%s", message.c_str());
    mvwprintw(textbox, TEXTBOX_HEIGHT - 2, TEXTBOX_WIDTH - 12, "[ENTER...]");
    wrefresh(textbox);

    int k;
        while (1) {
            k = getch();
            if (k == '\n' || k == '\r' || k == KEY_ENTER || k == ' ') {
                break;
            }
        }
    wrefresh(textbox);
}

void draw_inventory(WINDOW* inventory_win) {
    int start = (page_offset-1) * item_per_page;
    int end = std::min((int)inventory.size(), page_offset * item_per_page);
    werase(inventory_win);
    box(inventory_win, 0, 0);
    max_item_page = ceil((float)inventory.size() / item_per_page);
    mvwprintw(inventory_win, ITEM_HEIGHT-1, 1, "%d/%d", page_offset, max_item_page);
    for (int i = start; i < end; i++) {
        int row = i - start;
        Item item = get_item_by_id(inventory[i].item_id);

        if (i == selected) {
            wattron(inventory_win, A_REVERSE);
        }

        mvwprintw(inventory_win, 1 + (row * 2), 2, "%-17s", item.name.c_str());

        if (i == selected) {
            wattroff(inventory_win, A_REVERSE);

        }
        mvwprintw(inventory_win, 2 + (row * 2), 16, "x%d", inventory[i].quantity);
    }
    wrefresh(inventory_win);
}

void use_item_on_char(bool all) {
    Item item = get_item_by_id(inventory[selected].item_id);

    int start;
    int end;

    if (all) {
        start = 0;
        end = (int)party.size();
    } else {
        start = selected_member;
        end = selected_member + 1;
    }

    for (int i = start; i < end; i++) {
        switch (item.type) {
            case ItemType::HEALING_HP:
                if (party[i].is_alive()) {
                    party[i].heal(item.amount);
                }
                break;

            case ItemType::HEALING_MP:
                party[i].restore_mp(item.amount);
                break;

            case ItemType::HEALING_BOTH:
                if (party[i].is_alive()) {
                    party[i].heal(item.amount);
                }
                party[i].restore_mp(item.amount);
                break;

            case ItemType::REVIVE:
                if (!party[i].is_alive()) {
                    party[i].heal(item.amount);
                }
                break;

            case ItemType::CURE_STATUS:
                if (item.status == StatusEffect::NONE) {
                    party[i].set_status("Normal");
                } else if (item.status == StatusEffect::POISON && party[i].get_status() == "Poison") {
                    party[i].set_status("Normal");
                } else if (item.status == StatusEffect::PARALYSIS && party[i].get_status() == "Paralysis") {
                    party[i].set_status("Normal");
                } else if (item.status == StatusEffect::SLEEP && party[i].get_status() == "Sleep") {
                    party[i].set_status("Normal");
                } else if (item.status == StatusEffect::CHARM && party[i].get_status() == "Charm") {
                    party[i].set_status("Normal");
                } else if (item.status == StatusEffect::MUTE && party[i].get_status() == "Mute") {
                    party[i].set_status("Normal");
                }
                break;

            default:
                break;
        }
    }
}

void show_item_description(WINDOW* textbox) {
    wclear(textbox);
    Item item = get_item_by_id(inventory[selected].item_id);
    mvwprintw(textbox, 1, 2, item.desc.c_str());
    wrefresh(textbox);
}

void draw_character_status(WINDOW *status) {
    wclear(status);
    box(status, 0, 0);
    mvwprintw(status, 0, (STATUS_WIDTH-6)/2, "STATUS");
    mvwprintw(status, 1, 2, "Name: %s", party[selected_member].get_name().c_str());
    mvwprintw(status, 2, 2, "Level: %d", party[selected_member].get_level());
    mvwprintw(status, 3, 2, "Exp:  %d", party[selected_member].get_exp());
    mvwprintw(status, 4, 2, "Next: %d", party[selected_member].get_exp());
    mvwprintw(status, 5, 2, "HP: %d/%d", party[selected_member].get_hp(), party[selected_member].get_max_hp());
    mvwprintw(status, 6, 2, "MP: %d/%d", party[selected_member].get_mp(), party[selected_member].get_max_mp());
    mvwprintw(status, 7, 2, "Attack: %d", party[selected_member].get_current_attack());
    mvwprintw(status, 8, 2, "Defense: %d", party[selected_member].get_current_defense());
    mvwprintw(status, 9, 2, "Intelligence: %d", party[selected_member].get_current_magic_attack());
    mvwprintw(status, 10, 2, "Magic Res: %d", party[selected_member].get_current_magic_resistance());
    mvwprintw(status, 11, 2, "Speed: %d", party[selected_member].get_current_speed());
    mvwprintw(status, 12, 2, "Luck: %d", party[selected_member].get_current_luck());
    mvwprintw(status, 13, 2, "##### EQUIP #####");
    mvwprintw(status, 14, 2, party[selected_member].get_weapon().c_str());
    mvwprintw(status, 15, 2, party[selected_member].get_gun().c_str());
    mvwprintw(status, 16, 2, party[selected_member].get_bullet().c_str());
    mvwprintw(status, 17, 2, party[selected_member].get_head().c_str());
    mvwprintw(status, 18, 2, party[selected_member].get_body().c_str());
    mvwprintw(status, 19, 2, party[selected_member].get_gloves().c_str());
    mvwprintw(status, 20, 2, party[selected_member].get_legs().c_str());

    wrefresh(status);
    return;
}
