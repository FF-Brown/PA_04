/*
	Author: Nathan Brown
	Created: 10/01/2019
	Modified:
	Description: Terminal version of the game Blackjack Dice for 2-5 players. Function declarations.
*/

#define RULES 1
#define FUNDS 2
#define PLAY 3
#define EXIT 4
#define VIEW_FUNDS 1
#define EDIT_DEFAULT 2
#define RESET_FUNDS 3
#define MAIN 4
#define DEFAULT_FUNDS 500
#define PLAYER1 1
#define PLAYER2 2
#define PLAYER3 3
#define PLAYER4 4
#define PLAYER5 5


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

void display_menu(int funds[]);
void game_rules(void);
void funds_view(void);
void arr_reset(int arr[], int reset_value);
void double_arr_reset(double arr[], int reset_value);
int funds_def(void);
void funds_store(void);
int bet_initial(void);
int bet_sub(void);
bool bet_check(int current_bet, int player_funds);
int roll_die(void);
char old_money(int funds[]);
int game_intro(void);
int max_roll(int rolls[]);
char roll_check(int rolls[], int i);
int multi(int rolls[], double multiplier[], int max);
void tie_fighter(double multiplier[], int tie[], int bets[], int funds[], int winners, int max);
void chicken_dinner(double multiplier[], int bets[], int rolls[], int funds[]);
void die_graphic(int single_die);