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

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

/*
	Function: display_menu()
	Date Created: 10/01/2019
	Last Modified: 10/06/2019 Added funds option back in
	Description: Displays game menu. Redisplays until receiving valid input. Calls other functions based on input.
	Input parameters: funds[]
	Returns: None
	Preconditions: funds[] initialized and available
	Postconditions: Secondary menu displayed, playing game, or exited program.
*/
void display_menu(int funds[]);
/*
	Function: game_rules()
	Date Created: 10/02/2019
	Last Modified:
	Description: Displays the rules of the game.
	Input parameters: None
	Returns: None
	Preconditions: None
	Postconditions: Rules displayed, main menu brought up.
*/
void game_rules(void);
/*
	Function: funds_current_view
	Date Created: 10/07/2019
	Last Modified:
	Description: Outputs a single player's current funds to the screen
	Input parameters: funds[] and i
	Returns: None
	Preconditions: funds[] and i available
	Postconditions: Output printed to screen
*/
void funds_current_view(int funds[], int i);
/*
	Function: funds_saved_view()
	Date Created: 10/02/2019
	Last Modified: 10/07/2019 Changed to saved_view only
	Description: Retrieves data for player money from file, outputs to screen
	Input parameters: None
	Returns: None
	Preconditions: File containing player data available but not open
	Postconditions: Info output to screen
*/
void funds_saved_view(void);
/*
	Function: arr_reset()
	Date Created: 10/02/2019
	Last Modified: 10/07/2019 Changed to arr_reset() instead of funds_reset()
	Description: Changes all values in funds[] to specified value
	Input parameters: Any array arr[] and reset_value
	Returns: None
	Preconditions: Array available. Reset value chosen.
	Postconditions: Array reset
*/
void arr_reset(int arr[], int reset_value);
/*
	Function: double_arr_reset()
	Date Created: 10/06/2019
	Last Modified:
	Description: Changes all values in funds[] to specified value
	Input parameters: Any double array arr[] and reset_value
	Returns: None
	Preconditions: Array available. Reset value chosen.
	Postconditions: Array reset
*/
void double_arr_reset(double arr[], int reset_value);
/*
	Function: funds_def()
	Date Created: 10/01/2019
	Last Modified: 10/02/2019 Nerfed due to conflicts
					10/06/2019 Fixed.
	Description: Allows player to change default value for player funds
	Input parameters: None
	Returns: None
	Preconditions: None
	Postconditions: Default fund value set
*/
int funds_def(void);
/*
	Function: bet_initial()
	Date Created: 10/01/2019
	Last Modified: 10/06/2019 No longer calls bet_check. No longer has input parameters.
	Description: Accepts player's first bet. Mandatory.
	Input parameters: None
	Returns: Bet amount (int)
	Preconditions: Turn begun, money in funds[]
	Postconditions: Bet returned
*/
int bet_initial(void);
/*
	Function: bet_sub()
	Date Created: 10/01/2019
	Last Modified: 10/02/2019 Filled in
	Description: Takes subsequent (after first roll) bets from player. Optional.
	Input parameters: None
	Returns: Bet value (int)
	Preconditions: Initial bet taken
	Postconditions: Bet value returned
*/
int bet_sub(void);
/*
	Function: bet_check()
	Date Created: 10/01/2019
	Last Modified: 10/02/2019 Fleshed out
	Description: Compares funds to bet to confirm that they have enough money to make a given bet.
	Input parameters: Current bet and funds[i]
	Returns: True/False
	Preconditions: Player number established and available. Bet available. Funds[] available
	Postconditions: T/F returned
*/
bool bet_check(int current_bet, int player_funds);
/*
	Function: roll_die()
	Date Created: 10/01/2019
	Last Modified:
	Description: Generates a random integer 1-6
	Input parameters: None
	Returns: Integer die roll
	Preconditions: srand() called once previously to seed with time(NULL)
	Postconditions: Die roll returned
*/
int roll_die(void);
/*
	Function: old_money()
	Date Created: 10/01/2019
	Last Modified: 10/03/2019
					10/06-07/2019 Holy crap so much work.
	Description: Checks data file to see if funds have been changed. Asks player whether to retain save file. Acts based on answer. See further comments for more detail.
	Input parameters: funds[]
	Returns: y/n
	Preconditions: Data file must exist but not be open.
	Postconditions:	If player chooses, funds reset. Otherwise, no change made.
*/
char old_money(int funds[]);
/*
	Function: game_intro()
	Date Created: 10/01/2019
	Last Modified: 10/02/2019 Fleshed out
	Description: Begins the game. Prompts for number of players.
	Input parameters: None
	Returns: Number of players (int)
	Preconditions: None
	Postconditions: Number of players set for the course of the game.
*/
int game_intro(void);
/*
	Function: max_roll()
	Date Created: 10/02/2019
	Last Modified:
	Description: Determines which roll was the highest
	Input parameters: Sum of rolls as array
	Returns: Highest roll, winner #
	Preconditions: Game over. Roll sums available.
	Postconditions: Max roll returned.
*/
int max_roll(int rolls[]);
/*
	Function: roll_check()
	Date Created: 10/07/2019
	Last Modified:
	Description: Responds to certain values of roll sums. Tells the player how much they've rolled.
	Input parameters: rolls[] and i (1 lower than current player number)
	Returns: y/n whether to continue rolling
	Preconditions: Player has rolled
	Postconditions: Responds with various messages depending on value. Determines whether to roll again.
*/
char roll_check(int rolls[], int i);
/*
	Function: multi()
	Date Created: 10/07/2019
	Last Modified:
	Description: Assigns 0, 1.5, or 2 as multipliers for player's bet. Counts to determine if there has been a tie.
	Input parameters: rolls[], multiplier[], max roll
	Returns: Number of 'winners'
	Preconditions: Game over. Max roll calculated
	Postconditions: Multipliers assigned. Tie discerned.
*/
int multi(int rolls[], double multiplier[], int max);
/*
	Function: tie_fighter() Pun intended.
	Date Created: 10/06/2019
	Last Modified:
	Description: Acts if there has been a tie. Changes multipliers from 1.5 or 2 to 1. Alerts player to the tie. Ends the game.
	Input parameters: multiplier[], tie[], bets[], funds[], winners, max roll
	Returns: None
	Preconditions: Game is over. Max calculated. Winners calculated. Multipliers assigned 0, 1.5, or 2.
	Postconditions: All final values calculated.
*/
void tie_fighter(double multiplier[], int tie[], int bets[], int funds[], int winners, int max);
/*
	Function: chicken_dinner() As in, "winner winner"
	Date Created: 10/06/2019
	Last Modified:
	Description: Triggered if only one winner. Game-ending calculations and announcements.
	Input parameters: multiplier[], bets[], rolls[], funds[] (basically all player info arrays)
	Returns: None
	Preconditions: Game is over. Mulipliers, winners, and max rolls calculated.
	Postconditions: Player alerted to win status. Winnings calculated.
*/
void chicken_dinner(double multiplier[], int bets[], int rolls[], int funds[]);
/*
	Function: die_graphic()
	Date Created: 10/06/2019
	Last Modified:
	Description: Displays the image of a die when player rolls
	Input parameters: Roll value
	Returns: None
	Preconditions: Player has just rolled
	Postconditions: Die displayed
*/
void die_graphic(int single_die);
/*
	Function: save_data()
	Date Created: 10/07/2019
	Last Modified:
	Description: Allows player to save game data for a later rematch.
	Input parameters: funds[]
	Returns: None
	Preconditions: Game is over, winner has been chosen and announced
	Postconditions: DATA IS EITHER SAVED OR ALL OVERWRITTEN.
*/
void save_data(int funds[]);
/*
	Function: bank_totals()
	Date Created: 10/07/2019
	Last Modified:
	Description: Displays how much money players ended the game with. Limits list to participating players
	Input parameters: funds[], number of players
	Returns: None
	Preconditions: Game over. Winnings calculated
	Postconditions: All final total funds displayed.
*/
void bank_totals(int funds[], int player_count);