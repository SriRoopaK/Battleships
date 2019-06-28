#include <stdio.h>

#ifndef _structures_h
#define _structures_h
struct cell {
	char is_deployed;
	int row;
	int col;
	int selected;
	int fired;
};

struct ships {
	char *name;
	int max_cells;
	int rows[5];
	int cols[5];
	int fired;
};
#endif