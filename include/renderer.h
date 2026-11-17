#pragma once
#include "curses.h"
#include "gui.h"

inline int dx[4] = {0, 1, 0, -1};
inline int dy[4] = {-1, 0, 1, 0};

int is_wall(int x, int y);
void draw_front_wall(WINDOW *win, int x1, int y1, int x2, int y2, char fill);
void draw_side_wall(WINDOW *win, int is_left, int outer_x, int outer_y, int inner_x, int inner_y, char fill);
void draw_side_opening(WINDOW *win, int is_left, int outer_x, int outer_y, int inner_x, int inner_y, char fill);
void render_view(WINDOW *win, Player p);
