#include <stdio.h>
#include "initials.h"
void display_board_for_game(struct cell** board, char *player)
{
	printf("\n>Enemy's board\n");
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
				else {
					printf("%d ", board[i][j].selected);
				}
			}
			printf("\n");
	}
}
int check_for_fire(struct cell** board, struct ships* ships, int r, int c, char **name)
{
	int fire = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < ships[i].max_cells; j++)
		{
			if (ships[i].rows[j] == r && ships[i].cols[j] == c)
			{
				fire = 1;
				*name = ships[i].name;
				return fire;
			}
		}
	}
	return fire;
}
int if_ship_sunk(struct cell** board, struct ships* ships, char **name)
{
	int i,count=0,sunk=0;
	for (i = 0; i < 4; i++)
	{
		if (strcmp(*name, ships[i].name) == 0)
			break;
	}
	for (int j = 0; j < ships[i].max_cells; j++)
	{
		if (board[ships[i].rows[j]][ships[i].cols[j]].fired == 1)
			count++;
	}
	if (count == ships[i].max_cells) {
		ships[i].fired = 1;
		sunk = 1;
		return sunk;
	}
	return sunk;
}
int if_game_over(struct cell** board, struct ships* ships, char* player)
{
	int count = 0,game_over=0;
	for (int i = 0; i < 5; i++)
	{
		if (ships[i].fired == 1)
			count++;
	}
	if (count == 5)
	{
		printf("\n>Holla Commander!! You destoyed the enemy by sinking all his ships...");
		printf("\n>It's time to celebrate %s :) :) :)", player);
		game_over = 1;
		return game_over;
	}
	return game_over;
}
void play_game(struct cell** board1, struct cell** board2, struct ships* ships1, struct ships* ships2, char* player1, char* player2)
{
	int row, col,fire,sunk,game_over;
	char **name=(char *)malloc(sizeof(char)*20);
	while (1)
	{
	p1: printf("\n>%s's turn: ", player1);
		printf("\n>Choose a position to fire the enemy");
		display_board_for_game(board2, player2);
		printf("\n>Enter row: ");
		scanf("%d", &row);
		printf(">Enter column: ");
		scanf("%d", &col);
		board2[row][col].selected = 1;
		fire=check_for_fire(board2, ships2, row,col,name);
		board2[row][col].fired = fire;
		if (fire == 1) {
			printf("\n>Hurray it's a fire");
			sunk=if_ship_sunk(board2, ships2, name);
			if (sunk == 1) {
				printf("\n>%s's %s sunk :) :) :)", player2, *name);
				game_over=if_game_over(board2, ships2, player1);
				if (game_over == 1)
					return;
			}
			goto p1;
		}
	p2: printf("\n>%s's turn", player2);
		printf("\n>Choose a position to fire the enemy");
		display_board_for_game(board1, player1);
		printf(">Enter row: ");
		scanf("%d", &row);
		printf(">Enter column: ");
		scanf("%d", &col);
		board1[row][col].selected = 1;
		fire = check_for_fire(board1, ships1,row,col,name);
		board1[row][col].fired = fire;
		if (fire == 1) {
			printf("\n>Hurray it's a fire");
			sunk=if_ship_sunk(board1, ships1, name);
			if (sunk == 1) {
				printf("\n>%s's %s sunk :) :) :)", player1, *name);
				game_over=if_game_over(board1, ships1, player2);
				if (game_over == 1)
					return;
			}
			goto p2;
		}
	}

}
int main() {
	printf("Welcome to the Battleships :). If you win all the ships of your enemy, you win.");
	printf("\nThe game needs 2 players. Each player gets 5 ships to deploy on your board of ocean :D.");
	struct cell** board_player1 = (struct cell**)malloc(sizeof(struct cell) * 10);
	init_board(board_player1);
	struct ships* ships_player1 = (struct ships*)malloc(sizeof(struct ships) * 5);
	init_ships(ships_player1);
	char* player_name1 = (char*)malloc(sizeof(char) * 20);
	printf("\n\n>Player1 :)\n");
	player_name1 = player_details();
	display_board(board_player1, ships_player1, player_name1);
	deploy_ships(board_player1, ships_player1, player_name1);
	system("cls");
	struct cell** board_player2 = (struct cell**)malloc(sizeof(struct cell) * 10);
	init_board(board_player2);
	struct ships* ships_player2 = (struct ships*)malloc(sizeof(struct ships) * 5);
	init_ships(ships_player2);
	char* player_name2 = (char*)malloc(sizeof(char) * 20);
	printf(">Player2 :)\n");
	player_name2=player_details();
	display_board(board_player2, ships_player2, player_name2);
	deploy_ships(board_player2, ships_player2, player_name2);
	system("cls");
	play_game(board_player1, board_player2, ships_player1, ships_player2, player_name1, player_name2);
}