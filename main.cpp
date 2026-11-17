#include <string>
#include <vector>
#include "include/curses.h"
#include "include/gui.h"
#include "include/renderer.h"
#include "maps.h"
using namespace std;







int main(int argc, char** argv)
{




    initscr();
    resize_term(32, 105);
    noecho();
    refresh();
    keypad(stdscr, TRUE);
    start_color();

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

    Player p = {1, 1, 1};
    int ch;



    box(game_win, 0, 0);


    vector<Character> party = create_random_party();

    while (1) {
        draw_player_team_status(party, party_win);
        print_gui(win1, win2, party_win, quests_win);
        render_view(game_win, p);
        render_minimap(map_win, p);

        ch = getch();
        if (ch == 'q' || ch == 'Q') break;

        int nx = p.x, ny = p.y;
        if (ch == 'w' || ch == KEY_UP) {
            nx += dx[p.dir];
            ny += dy[p.dir];
        } else if (ch == 's' || ch == KEY_DOWN) {
            nx -= dx[p.dir];
            ny -= dy[p.dir];
        } else if (ch == 'a' || ch == KEY_LEFT) {
            p.dir = (p.dir + 3) % 4; // Gira a sinistra
        } else if (ch == 'd' || ch == KEY_RIGHT) {
            p.dir = (p.dir + 1) % 4; // Gira a destra
        }

        // Collisione
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
