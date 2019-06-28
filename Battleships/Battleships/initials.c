#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

void init_board(struct cell** board)
{
	for (int i = 0; i < 10; i++)
	{
		struct cell* row = (struct cell*)malloc(sizeof(struct cell) * 10);
		for (int j = 0; j < 10; j++)
		{
			row[j].row = i;
			row[j].col = j;
			row[j].selected = 0;
			row[j].fired = 0;
			row[j].is_deployed = 'N';
		}
		board[i] = row;
	}
}
void init_ships(struct ships* ships_list)
{
	ships_list[0].name = "Aircraftcarrier";
	ships_list[1].name = "Battleship";
	ships_list[2].name = "Frigate";
	ships_list[3].name = "Submarine";
	ships_list[4].name = "Minesweeper";
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			ships_list[i].rows[j] = -1;
			ships_list[i].cols[j] = -1;
		}
		ships_list[i].fired = 0;
		if (i == 0)
		{
			ships_list[i].max_cells = 5;
		}
		else if (i == 1)
		{
			ships_list[i].max_cells = 4;
		}
		else if (i == 2 || i == 3)
		{
			ships_list[i].max_cells = 3;
		}
		else if (i == 4) {
			ships_list[i].max_cells = 2;
		}

	}
}
int assign_ships(struct cell** board, int row, int col, struct ships* ships, int ship_index, int end_row, int end_col)
{
	int index, flag=1;
	if (end_row == row)
	{
		if (end_col > col)
		{
			index = col + 1;
			for (int i = 1; i < ships[ship_index].max_cells; i++)
			{
				ships[ship_index].rows[i] = row;
				ships[ship_index].cols[i] = index;
				if (board[row][index].is_deployed != 'N') {
					printf("\n>>Deploying collision. Choose another endpoint");
					flag = 0;
					return flag;
				}
				board[row][index].is_deployed = ships[ship_index].name[0];
				index++;
			}
		}
		else
		{
			index = col - 1;
			for (int i = 1; i < ships[ship_index].max_cells; i++)
			{
				ships[ship_index].rows[i] = row;
				ships[ship_index].cols[i] = index;
				if (board[row][index].is_deployed != 'N') {
					printf("\n>>Deploying collision. Choose another endpoint");
					flag = 0;
					return flag;
				}
				board[row][index].is_deployed = ships[ship_index].name[0];
				index--;
			}
		}
	}
	else
	{
		if (end_row > row)
		{
			index = row + 1;
			for (int i = 1; i < ships[ship_index].max_cells; i++)
			{
				ships[ship_index].rows[i] = index;
				ships[ship_index].cols[i] = col;
				if (board[index][col].is_deployed != 'N') {
					printf("\n>>Deploying collision. Choose another endpoint");
					flag = 0;
					return flag;
				}
				board[index][col].is_deployed = ships[ship_index].name[0];
				index++;
			}
		}
		else
		{
			index = row - 1;
			for (int i = 1; i < ships[ship_index].max_cells; i++)
			{
				ships[ship_index].rows[i] = index;
				ships[ship_index].cols[i] = col;
				if (board[index][col].is_deployed != 'N') {
					printf("\n>>Deploying collision. Choose another endpoint");
					flag = 0;
					return flag;
				}
				board[index][col].is_deployed = ships[ship_index].name[0];
				index--;
			}
		}

	}
	return flag;
}
void display_board(struct cell** board, struct ships* ships, char* player_name)
{
	printf(">Here's your board, %s\n", player_name);
	printf("     ");
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", i);
	}
	printf("\n");
	printf("\n");
	for (int i = 0; i < 10; i++)
	{
		printf("%d    ", i);
		for (int j = 0; j < 10; j++)
		{
			if (board[i][j].fired == 1)
				printf("F ");
			else if (board[i][j].is_deployed != 'N')
				printf("%c ", board[i][j].is_deployed);
			else {
				printf("%d ", board[i][j].selected);
			}
		}
		printf("\n");
	}
}
char* player_details()
{
	char* player_name = (char*)malloc(sizeof(char) * 20);
	printf(">Enter player name: ");
	scanf("%s", player_name);
	printf(">Welcome aboard %s :)...Have a nice time playing..\n", player_name);
	return player_name;
}

void find_ends(struct cell** board, int row, int col, struct ships* ships, int ship_index)
{
	int end_rows[4], end_cols[4], menu_index = 1, i;
	int response, flag = 0, index, no_collision;
	end_rows[0] = row;  end_cols[0] = col + ships[ship_index].max_cells - 1;
	end_rows[1] = row; end_cols[1] = col - ships[ship_index].max_cells + 1;
	end_rows[2] = row - ships[ship_index].max_cells + 1; end_cols[2] = col;
	end_rows[3] = row + ships[ship_index].max_cells - 1; end_cols[3] = col;
choose:
	for (i = 0; i < 4; i++)
	{
		if ((end_rows[i] < 0 || end_rows[i]>9) || (end_cols[i] < 0 || end_cols[i]>9))
			continue;
		printf("\n>>%d = Row: %d <==> Column: %d", menu_index, end_rows[i], end_cols[i]);
		printf("\n>>Enter 1 if you want to choose the above endpoint...Enter '0 to check for other endpoints: ");
		scanf("%d", &response);
		if (response == 1)
		{
			no_collision=assign_ships(board, row, col, ships, ship_index, end_rows[i], end_cols[i]);
			if (no_collision == 0)
				continue;
			flag = 1;
			break;
		}
		menu_index++;
	}
	if (flag == 0)
	{
		printf("\n>>No endpoint chosen :( Ship hasn't been deployed. Please choose endpoint");
		goto choose;
	}
	return;
}
void deploy_ships(struct cell** board, struct ships* ships, char* player_name)
{
	for (int ship = 0; ship < 5; ship++)
	{
		int row, col;
		char* name;
	deploy: printf("\n>Deploying ship %s", ships[ship].name);
		printf("\n>>Enter first row: ");
		scanf("%d", &row);
		printf(">>Enter first column: ");
		scanf("%d", &col);
		if (row < 0 || row >9)
		{
			printf("\n>>Row number should be in the range of 0-9...Please re-deploy your %s accordingly :( ", ships[ship].name);
			goto deploy;
		}
		else if (col < 0 || col>9)
		{
			printf("\n>>Column number should be in the range of 0-9...Please re-deploy your %s accordingly :( ", ships[ship].name);
			goto deploy;
		}
		ships[ship].rows[0] = row;
		ships[ship].cols[0] = col;
		name = ships[ship].name;
		if (board[row][col].is_deployed != 'N')
		{
			printf(">>\nDeployment Collision. Choose another startpoint");
			goto deploy;
		}
		board[row][col].is_deployed = name[0];
		find_ends(board, row, col, ships, ship);
		display_board(board, ships, player_name);
	}
}