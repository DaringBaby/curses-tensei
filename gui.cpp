#include "include/gui.h"
#include "include/curses.h"

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
                mvwaddch(win, y + 2, x * 2 + 2, sample_map[y][x] ? '#' : '.');
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
        mvwprintw(party_win, 1 + i * 2, 1, party[i].get_name().c_str());
        wattroff(party_win, COLOR_PAIR(4) | A_BOLD);
        mvwprintw(party_win, 1 + i * 2, 12, "Lv. %d", party[i].get_level());
        mvwprintw(party_win, 2 + 2 * i, 2, "HP:%d/%d MP:%d", party[i].get_hp(), party[i].get_max_hp(), party[i].get_mp());
    }
}
