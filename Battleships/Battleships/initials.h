#include <stdio.h>
#include "structures.h"
#ifndef _initials_h
#define _initials_h
void init_board(struct cell** board);
void init_ships(struct ships* ships);
void assign_ships(struct cell** board, int row, int col, struct ships* ships, int ship_index, int end_row, int end_col);
void display_board(struct cell** board, struct ships* ships, char* player_name);
char* player_details();
void find_ends(struct cell** board, int row, int col, struct ships* ships, int ship_index);
void deploy_ships(struct cell** board, struct ships* ships, char* player_name);
#endif
