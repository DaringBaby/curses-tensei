#include "include/renderer.h"
#include "include/maps.h"

int is_wall(int x, int y) {
    if (x < 0 || x >= MAP_W || y < 0 || y >= MAP_H) return 1;
    return sample_map[y][x] == 1;
}

void draw_front_wall(WINDOW *win, int x1, int y1, int x2, int y2, char fill) {
    for (int y = y1; y <= y2; y++) {
        for (int x = x1; x <= x2; x++) {
            char c = fill;
            if (y == y1 || y == y2) c = '-';
            if (x == x1 || x == x2) c = '|';
            if ((x == x1 || x == x2) && (y == y1 || y == y2)) c = '+';
            mvwaddch(win, y, x, c);
        }
    }
}

void draw_side_wall(WINDOW *win, int is_left, int outer_x, int outer_y, int inner_x, int inner_y, char fill) {
    int start_x = is_left ? outer_x : inner_x;
    int end_x   = is_left ? inner_x : outer_x;

    for (int x = start_x; x <= end_x; x++) {
        float t = (float)(x - outer_x) / (float)(inner_x - outer_x);
        int top_y = outer_y + (int)(t * (inner_y - outer_y));
        int bot_y = (GAME_HEIGHT - 1) - top_y;

        for (int y = top_y; y <= bot_y; y++) {
            char c = fill;
            if (y == top_y) c = is_left ? '\\' : '/';
            else if (y == bot_y) c = is_left ? '/' : '\\';
            else if (x == start_x || x == end_x) c = '|';
            mvwaddch(win, y, x, c);
        }
    }
}

void draw_side_opening(WINDOW *win, int is_left, int outer_x, int outer_y, int inner_x, int inner_y, char fill) {
    int start_x = is_left ? outer_x : inner_x;
    int end_x   = is_left ? inner_x : outer_x;

    for (int x = start_x; x <= end_x; x++) {
        for (int y = inner_y; y <= (GAME_HEIGHT - 1) - inner_y; y++) {
            char c = fill;
            if (y == inner_y || y == (GAME_HEIGHT - 1) - inner_y) c = '-';
            if (x == inner_x) c = '|';
            mvwaddch(win, y, x, c);
        }
    }
}

void render_view(WINDOW *win, Player p) {
    werase(win);
    box(win, 0, 0);

    int px[4] = {1,  8, 14, 19};
    int py[4] = {1,  4,  7,  9};
    char shades[3] = {'.', ':', '#'};

    int f_dx = dx[p.dir], f_dy = dy[p.dir];
    int l_dx = dx[(p.dir + 3) % 4], l_dy = dy[(p.dir + 3) % 4];
    int r_dx = dx[(p.dir + 1) % 4], r_dy = dy[(p.dir + 1) % 4];

    for (int d = 2; d >= 0; d--) {
        int cx = p.x + f_dx * d;
        int cy = p.y + f_dy * d;

        int ox = px[d],     oy = py[d];
        int ix = px[d + 1], iy = py[d + 1];

        if (is_wall(cx + l_dx, cy + l_dy)) {
            draw_side_wall(win, 1, ox, oy, ix, iy, shades[d]);
        } else {
            draw_side_opening(win, 1, ox, oy, ix, iy, ' ');
        }

        if (is_wall(cx + r_dx, cy + r_dy)) {
            draw_side_wall(win, 0, GAME_WIDTH - 1 - ox, oy, GAME_WIDTH - 1 - ix, iy, shades[d]);
        } else {
            draw_side_opening(win, 0, GAME_WIDTH - 1 - ox, oy, GAME_WIDTH - 1 - ix, iy, ' ');
        }

        if (is_wall(cx + f_dx, cy + f_dy)) {
            draw_front_wall(win, ix, iy, GAME_WIDTH - 1 - ix, GAME_HEIGHT - 1 - iy, shades[d]);
        }
    }

    wrefresh(win);
}
