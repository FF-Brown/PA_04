/*
	Author: Nathan Brown
	Created: 10/01/2019
	Modified:
	Description: Terminal version of the game Blackjack Dice for 2-5 players. Function definitions.
*/

#include "mechanics.h"

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
void display_menu(int funds[])
{
	int option = 0;
	int money = 0;
	//Display menu until receiving valid input
begin_menu:
	option = 0;
	while (option < 1 || option > 4)
	{
		printf("\n~~~~~~ MAIN MENU ~~~~~~\n\n");
		printf("1. Display game rules.\n");
		printf("2. Edit player funds.\n");
		printf("3. Begin game.\n");
		printf("4. Exit.\n");
		printf("Select an option by typing the corresponding number.\n");
		scanf("%d", &option);

		//Run process based on input
		switch (option)
		{
		case RULES:
			game_rules();
			display_menu(funds);
			break;
		case FUNDS:
			funds_saved_view();
			money = funds_def();
			arr_reset(funds, money);
			goto begin_menu;//display_menu(funds);
			break;
			//Leave switch and while loop to begin playing game
		case PLAY:
			break;
			//Exit program
		case EXIT:
			exit(0);
			break;
		default:
			break;
		}
		if (option < 1 || option > 4)
			printf("Invalid entry.\n");
	}
}
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
void game_rules(void)
{
	printf("\nBlackjack dice is played with 2-5 people. It is primarily a game of chance but involves some strategy.\nPlayers take turns in order. On a player's turn, he/she rolls one six-sided die. They continue rolling until the sum of the rolls is greater than 21 or they choose to stop rolling. A player has the option to stop rolling after the roll sum reaches 16.\nA player wins by having the greatest sum of all players. However, if that value is greater than 21, that player loses. Therefore, it is a competition to see who can arrive the closest to 21 without going over. The game ends when all players have either gone over 21 or chosen to stop rolling.\n\nAt the beginning of their turn and once before each roll, players have the option to place bets. The amount they win is decided at the end of the game.\nIf a player rolls 21, they get 2x their total bet.\nIf a player has the highest roll in the group but did not roll 21 exactly, they get 1.5x their total bet.\nIf two players tie for highest roll, they both get only 1x their total bet.\nThose who lose the game also lose their bets.\n\nIn this version of the game, you have the option to save a record of each player's funds to continue the same game at a different time.\n");
}
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
void funds_saved_view(void)
{
	int player1 = 0, player2 = 0, player3 = 0, player4 = 0, player5 = 0;
	FILE* iofile = NULL;
	iofile = fopen("funds.dat", "r");
	fscanf(iofile, "%d%d%d%d%d", &player1, &player2, &player3, &player4, &player5);
	fclose(iofile);

	printf("\nIn your save file, players have the following amounts of money:\n\n");
	printf("Player 1: $%d\n", player1);
	printf("Player 2: $%d\n", player2);
	printf("Player 3: $%d\n", player3);
	printf("Player 4: $%d\n", player4);
	printf("Player 5: $%d\n", player5);
}
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
void funds_current_view(int funds[], int i)
{
	printf("$%d available.\n", funds[i]);
}
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
void arr_reset(int arr[], int reset_value)
{
	arr[0] = reset_value;
	arr[1] = reset_value;
	arr[2] = reset_value;
	arr[3] = reset_value;
	arr[4] = reset_value;
}
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
void double_arr_reset(double arr[], int reset_value)
{
	arr[0] = reset_value;
	arr[1] = reset_value;
	arr[2] = reset_value;
	arr[3] = reset_value;
	arr[4] = reset_value;
}
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
int funds_def(void)
{
	int new_def = 0;

	while (new_def < 1)
	{
		printf("How much money would you like players to start with?\n$");
		scanf("%d", &new_def);
		if (new_def < 1)
			printf("Invalid input.\n");
	}
	return new_def;
}
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
int bet_initial(void)
{
	int bet = 0;
	while (bet < 1)
	{
		printf("How much would you like to bet?\n$");
		scanf("%d", &bet);
		if (bet < 1)
			printf("Invalid entry.\n");
	}
	return bet;
}
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
int bet_sub(void)
{
	int bet = 0;
	printf("How much would you like to bet? You may choose to bet $0.\n$");
	scanf("%d", &bet);
	if (bet < 0)
	{
		printf("Invalid entry.\n");
		while (bet < 0)
		{
			printf("How much would you like to bet? You may choose to bet $0.\n$");
			scanf("%d", &bet);
			if (bet < 0)
				printf("Invalid entry.\n");
		}
	}

	return bet;

}
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
bool bet_check(int current_bet, int player_funds)
{
	bool validity = false;
	if (current_bet <= player_funds)
		validity = true;
	else
		validity = false;
	return validity;
}
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
int roll_die(void)
{
	int roll = rand() % 6 + 1;
	return roll;
}
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
char old_money(int funds[])
{
	char option = '\0';
	int money_check = 0;
	int starting_funds = 0;

	//Check to see if a previous game's money values are stored in data file.
	FILE* iofile = NULL;
	iofile = fopen("funds.dat", "r+");
	fscanf(iofile, "%d", &money_check);


	//If no funds differ from default (which is -1 to avoid confusion with case where Player 1 lost all their money and saved $0), prompt user for new starting values
	if (money_check < 0)
	{
		starting_funds = funds_def();
		arr_reset(funds, starting_funds);
	}

	//Otherwise...
	else if (money_check >= 0)
	{
		while (option != 'y' && option != 'n') //Keep money from last game?
		{
			funds_saved_view();
			printf("\nWould you like to retain the funds from the end of your last game? (y/n)\n");
			scanf(" %c", &option);
			if (option != 'y' && option != 'n') //In case typo
				printf("Invalid entry.\n");
		}
		//If yes, import from file
		if (option == 'y') 
		{
			for (int k = 0; k < 5; k++)
			{
				fscanf(iofile, "%d", &funds[k]);
			}
		}
		//If no, reset all data
		else if (option == 'n')
		{
			fprintf(iofile, "%d\n%d\n%d\n%d\n%d\n", -1, -1, -1, -1, -1);
			arr_reset(funds, -1);
			//And ask for new starting data
			starting_funds = funds_def();
			arr_reset(funds, starting_funds);
		}
	}
	fclose(iofile);
	return option;
}
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
int game_intro(void)
{
	int player_count = 0;

	//Prompt for number of players
	while (2 > player_count || 5 < player_count)
	{
		printf("Please enter the number of players (2-5): ");
		scanf("%d", &player_count);
		if (2 > player_count || 5 < player_count)
			printf("Invalid entry.\n");
	}

	return player_count;
}
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
int max_roll(int rolls[])
{
	int max = rolls[0];
	for (int i = 1; i < 5; i++)
	{
		if (rolls[i] > max && rolls[i] <= 21)
			max = rolls[i];
	}
	return max;
}
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
char roll_check(int rolls[], int i)
{
	char cont = 'y';
	if (21 == rolls[i])
	{
		printf("Congratulations! You have rolled a perfect 21!\n");
		cont = 'n';
	}
	else if (rolls[i] > 21)
	{
		printf("Sorry! You went over 21. You lose!\n");
		cont = 'n';
	}
	else if (rolls[i] >= 16)
	{
		do
		{
			printf("You are at %d and may choose to end your turn. Would you like to continue rolling? (y/n)\n", rolls[i]);
			scanf(" %c", &cont);
			if (cont != 'y' && cont != 'n')
				printf("Invalid entry.\n");
		} while (cont != 'y' && cont != 'n');

	}
	else
		printf("You are at %d.\n", rolls[i]);
	return cont;
}
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
int multi(int rolls[], double multiplier[], int max)
{
	int winners = 0;
	for (int i = 0; i < 5; i++)
	{
		if (rolls[i] != max)
			multiplier[i] = 0;
		else if (rolls[i] == 21)
		{
			multiplier[i] = 2;
			winners++;
		}
		else if (rolls[i] == max)
		{
			multiplier[i] = 1.5;
			winners++;
		}
	}
	return winners;
}
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
void tie_fighter(double multiplier[], int tie[], int bets[], int funds[], int winners, int max)
{
	int j = 0;
	for (int i = 0; i < 5; i++)
	{
		if (multiplier[i] > 0)
		{
			multiplier[i] = 1.0;
			tie[j] = i + 1;
			j++;
		}
	}

	if (winners == 2)
	{
		printf("We have a 2-way tie! Both Player %d and Player %d rolled %d!\n", tie[0], tie[1], max);
		for (int i = 0; i < winners; i++)
		{
			funds[tie[i]] += bets[tie[i]];
		}
	}
	else if (winners == 3)
	{
		printf("We have a 3-way tie! Player %d, Player %d, and Player %d all rolled %d!\n", tie[0], tie[1], tie[2], max);
		for (int i = 0; i < winners; i++)
		{
			funds[tie[i]] += bets[tie[i]];
		}
	}
	else if (winners == 4)
	{
		printf("We have a 4-way tie!! Player %d, Player %d, Player %d, and Player %d all rolled %d!\n", tie[0], tie[1], tie[2], tie[3], max);
		for (int i = 0; i < winners; i++)
		{
			funds[tie[i]] += bets[tie[i]];
		}
	}
	else if (winners == 5)
	{
		printf("We have a 5-way tie!!!! All players rolled %d!\n", max);
		for (int i = 0; i < winners; i++)
		{
			funds[tie[i]] += bets[tie[i]];
		}

	}
	printf("All players who tied get their bets back but do not win any extra money.\n");
}
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
void chicken_dinner(double multiplier[], int bets[], int rolls[], int funds[])
{
	int winner = 0, winnings = 0;
	for (int i = 0; i < 5; i++)
	{
		if (multiplier[i] > 0)
		{
			winner = i + 1;
			break;
		}
	}
	//In case somehow this variable gets set to 0, which should never happen
	if (winner == 0)
		exit(7331);
	winnings = bets[winner - 1] * multiplier[winner - 1];
	printf("\nThe congratulations go to Player %d, with a roll of %d!\n", winner, rolls[winner - 1]);
	printf("Since you bet $%d, you win $%d!\n", bets[winner - 1], winnings);
	funds[winner - 1] += winnings;
}
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
void die_graphic(int single_die)
{
	if (single_die == 6)
	{
		printf("\n ______________\n");
		printf("|              |\n");
		printf("|    0    0    |\n");
		printf("|              |\n");
		printf("|    0    0    |\n");
		printf("|              |\n");
		printf("|    0    0    |\n");
		printf("|______________|\n\n");
		//How the graphic should display
		/*
			 ____________
			|			 |
			|	0	 0	 |
			|	0	 0	 |
			|	0	 0	 |
			|____________|
		*/
	}
	else if (single_die == 5)
	{

		printf("\n ______________\n");
		printf("|              |\n");
		printf("|   0     0    |\n");
		printf("|              |\n");
		printf("|      0       |\n");
		printf("|              |\n");
		printf("|   0     0    |\n");
		printf("|______________|\n\n");

		//How the graphic should display
		/*
			 ____________
			|			 |
			|  0	 0	 |
			|	  0	     |
			|  0	 0	 |
			|____________|
		*/
	}
	else if (single_die == 4)
	{
		printf("\n ______________\n");
		printf("|              |\n");
		printf("|   0     0    |\n");
		printf("|              |\n");
		printf("|              |\n");
		printf("|              |\n");
		printf("|   0     0    |\n");
		printf("|______________|\n\n");
		//How the graphic should display
		/*
			 ____________
			|			 |
			|	0	 0	 |
			|		 	 |
			|	0	 0	 |
			|____________|
		*/
	}
	else if (single_die == 3)
	{
		printf("\n ______________\n");
		printf("|              |\n");
		printf("|         0    |\n");
		printf("|              |\n");
		printf("|      0       |\n");
		printf("|              |\n");
		printf("|   0          |\n");
		printf("|______________|\n\n");
		//How the graphic should display
		/*
			 ____________
			|			 |
			|   	 0	 |
			|	  0	     |
			|  0	 	 |
			|____________|
		*/
	}
	else if (single_die == 2)
	{
		printf("\n ______________\n");
		printf("|              |\n");
		printf("|         0    |\n");
		printf("|              |\n");
		printf("|              |\n");
		printf("|              |\n");
		printf("|   0          |\n");
		printf("|______________|\n\n");
		//How the graphic should display
		/*
			 ____________
			|			 |
			|   	 0	 |
			|	  	     |
			|  0	 	 |
			|____________|
		*/
	}
	else if (single_die == 1)
	{
		printf("\n ______________\n");
		printf("|              |\n");
		printf("|              |\n");
		printf("|              |\n");
		printf("|      0       |\n");
		printf("|              |\n");
		printf("|              |\n");
		printf("|______________|\n\n");
		//How the graphic should display
			/*
				 ____________
				|			 |
				|   	 	 |
				|	  0	     |
				|   	 	 |
				|____________|
			*/
	}
}
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
void save_data(int funds[])
{
	char save = '\0';
	while (save != 'y' && save != 'n')
	{
		printf("\nWould you like to save your data for later? (y/n)\n");
		scanf(" %c", &save);
		if (save != 'y' && save != 'n') //In case typo
			printf("Invalid entry.\n");
	}

	FILE* iofile = NULL;
	iofile = fopen("funds.dat", "w");
	if (save == 'y') //If yes, save to file
	{
		fprintf(iofile, "%d\n%d\n%d\n%d\n%d\n", funds[0], funds[1], funds[2], funds[3], funds[4]);

		printf("Player funds saved to file for next game.\n");
	}
	else if (save == 'n') //If no, overwrite file with -1
	{
		fprintf(iofile, "%d\n%d\n%d\n%d\n%d\n", -1, -1, -1, -1, -1);
		arr_reset(funds, -1);
	}
	fclose(iofile);

}
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
void bank_totals(int funds[], int player_count)
{
	printf("\nFinal bank totals: \n");
	for (int i = 0; i < 5; i++)
	{
		printf("Player %d: ", i + 1);
		funds_current_view(funds, i);

	}
}