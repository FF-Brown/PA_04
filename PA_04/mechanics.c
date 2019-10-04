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
	Last Modified:
	Description: Displays game menu. Redisplays until receiving valid input. Calls other functions based on input. May remove switch and place in main. Haven't decided yet.
	Input parameters: None
	Returns: None
	Preconditions: None
	Postconditions: Secondary menu displayed, playing game, or exited program.
*/
void display_menu(void)
{
	int option = 0;
	//Display menu until receiving valid input
	while (option < 1 || option > 4)
	{
		printf("\n~~~~~~ MAIN MENU ~~~~~~\n\n");
		printf("1. Display game rules.\n");
		printf("2. View and edit funds.\n");
		printf("3. Begin game.\n");
		printf("4. Exit.\n");
		printf("Select an option by typing the corresponding number.\n");
		scanf("%d", &option);

		//Run process based on input
		switch (option)
		{
		case RULES:
			game_rules();
			break;
		case FUNDS:
			funds_menu();
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
	display_menu();
}
/*
	Function: funds_menu()
	Date Created: 10/01/2019
	Last Modified: 10/02/2019 Removed display_menu() call
	Description: Display options for editing funds.
	Input parameters: None
	Returns: None
	Preconditions: Generally only called from another menu option
	Postconditions: Activates other menu option
*/
void funds_menu(void)
{
	int option = 0;
	while (option < 1 || option > 4)
	{
		printf("\n~~~~~~ FUNDS MENU ~~~~~~\n\n");
		printf("1. View current player funds.\n");
		printf("2. Change default starting funds.\n");
		printf("3. Reset player funds.\n");
		printf("4. Return to main menu.\n");
		printf("Select an option by typing the corresponding number.\n");
		scanf("%d", &option);

		//Run process based on input
		switch (option)
		{
		case VIEW_FUNDS:
			funds_view();
			funds_menu();
			break;
		case EDIT_DEFAULT:
			funds_def();
			funds_menu();
			break;
		case RESET_FUNDS:
			funds_reset();
			funds_menu();
			break;
			//Return to main
		case MAIN:
			display_menu();
			break;
		default:
			break;
		}
	}
}
/*
	Function: funds_view()
	Date Created: 10/02/2019
	Last Modified:
	Description: Retrieves data for player money from file, outputs to screen
	Input parameters: None
	Returns: None
	Preconditions: File containing player data available but not open
	Postconditions: Info output to screen
*/
void funds_view(void)
{
	int player1 = 0, player2 = 0, player3 = 0, player4 = 0, player5 = 0;
	FILE* iofile = NULL;
	iofile = fopen("funds.dat", "r");
	fscanf(iofile, "%d%d%d%d%d", &player1, &player2, &player3, &player4, &player5);
	fclose(iofile);

	printf("\nCurrently, players have the following amounts of money:\n\n");
	printf("Player 1: %d\n", player1);
	printf("Player 2: %d\n", player2);
	printf("Player 3: %d\n", player3);
	printf("Player 4: %d\n", player4);
	printf("Player 5: %d\n", player5);
}
/*
	Function: funds_reset()
	Date Created: 10/02/2019
	Last Modified:
	Description: Calls funds_view() and then gives option to reset player funds to default value.
	Input parameters: None
	Returns: None
	Preconditions: Data file with player funds available but not open
	Postconditions: Either funds reset or message displayed that they were not changed
*/
void funds_reset(void)
{
	char option = '\0';
	//Display current funds value and option to reset.
	funds_view();
	while ('y' != option && 'n' != option)
	{
		printf("Reset funds for all players? (y/n)\n");
		scanf(" %c", &option);
		if ('y' == option)
		{
			FILE* iofile = NULL;
			iofile = fopen("funds.dat", "w");
			fprintf(iofile, "%d\n%d\n%d\n%d\n%d\n", DEFAULT_FUNDS, DEFAULT_FUNDS, DEFAULT_FUNDS, DEFAULT_FUNDS, DEFAULT_FUNDS);
			fclose(iofile);
		}
		else if (option == 'n')
			printf("Funds remain unchanged.\n");
		else
		{
			printf("Invalid input.\n");
		}
	}
}
/*
	Function: funds_def()
	Date Created: 10/01/2019
	Last Modified: 10/02/2019 Nerfed due to conflicts
	Description: Meant to allow player to change default value for player funds
	Input parameters: None
	Returns: None
	Preconditions: Default fund value set
	Postconditions: Default fund value either changed or player changed their mind
*/
void funds_def(void)
{
	printf("This option is currently unavailable.\n");
	//char option = '\0';
	//int funds_new_def = 0;
	////printf("Display default funds value and option to edit.\n");
	//printf("By default, players begin the game with $%d\n", DEFAULT_FUNDS);
	//while (option != 'y' && option != 'n')
	//{
	//	printf("Would you like to adjust the starting amount? (y/n)\n");
	//	scanf(" %c", &option);
	//	if ('y' == option)
	//	{
	//		printf("New starting amount: $");
	//		scanf("%d", &funds_new_def);
	//	}
	//	else if ('n' == option)
	//		printf("Starting amount remains unchanged.\n");
	//	else
	//		printf("Invalid input.\n");
	//}
}
/*
	Function: funds_store()
	Date Created: 10/01/2019
	Last Modified: 10/02/2019 Began building
	Description: Allows user to store game data at the end of a round to continue with the same info at a later date.
	Input parameters: Player funds as integers
	Returns: None
	Preconditions: Fund values available for use
	Postconditions: Fund values stored to player data file
*/
void funds_store(void)
{
	//Save values of current funds to file
	return;
}
/*
	Function: bet_initial()
	Date Created: 10/01/2019
	Last Modified:
	Description: Accepts player's first bet. Mandatory.
				 Calls bet_check to verify player has enough money.
	Input parameters: Player (int)
	Returns: Bet amount (int)
	Preconditions: Turn begun, player specified
	Postconditions: Bet logged
*/
int bet_initial(void)
{
	int bet = 0;
	while (bet < 1)
	{
		printf("How much would you like to bet?\n");
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
	Preconditions: Player number established and available
	Postconditions: Bet value returned
*/
int bet_sub(void)
{
	int bet = 0;
	printf("How much would you like to bet? You may choose to bet $0.\n");
	scanf("%d", &bet);
	if (bet < 0)
	{
		printf("Invalid entry.\n");
		while (bet < 0)
		{
			printf("How much would you like to bet? You may choose to bet $0.\n");
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
	Input parameters: Current bet and funds
	Returns: True/False
	Preconditions: Player number established and available
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
	Function: turn_flow()
	Date Created: 10/01/2019
	Last Modified: 10/02/2019 Massive overhaul
	Description: Controls each player's turn flow. Does most of the function calling. This allows for the repetition of the order of actions without errors or variance.
	Input parameters: Player number (int), player funds (int)
	Returns: None (pointers used due to multiple return values)
	Preconditions: Number of players established, funds available
	Postconditions: One turn completed. Bet total, roll sum, and updated funds for player returned.
*/
void turn_flow(int player_number, int player_funds, int* bets, int* rolls, int* funds)
{
	int bet_total = 0, current_bet = 0;
	int single_die = 0;
	int roll_sum = 0;
	char cont = 'y';
	bool check = false;

	//Get inital bet (mandatory) and run bet_check(). Add bet to total, subtract from funds.
	printf("\nBest of luck, Player %d!\n", player_number);
	while (check == false)
	{
		current_bet = bet_initial();
		check = bet_check(current_bet, player_funds);
		if (check == false)
			printf("You do not have enough money. Please place a lower bet.\n");
	}
	check = false;
	bet_total += current_bet;
	player_funds -= current_bet;

	//First roll. Simplified version of subsequent rolls.
	single_die = roll_die();
	roll_sum = single_die;
	printf("You rolled a %d. ", single_die);
	printf("You are at %d.\n", roll_sum);

	while (cont == 'y')
	{
		//Offer to take a bet. Call check_bet(). Add to bet_total and subtract from player_funds
		while (!check)
		{
			current_bet = bet_sub();
			check = bet_check(current_bet, player_funds);
			if (!check)
				printf("You do not have enough money. Please place a lower bet.\n");
		}
		check = false;
		bet_total += current_bet;
		player_funds -= current_bet;

		//Roll die. Add to sum. If 16+, offer to stop rolling.
		single_die = roll_die();
		roll_sum += single_die;
		printf("You rolled a %d. ", single_die);
		if (21 == roll_sum)
		{
			printf("Congratulations! You have rolled a perfect 21!\n");
			cont = 'n';
		}
		else if (roll_sum > 21)
		{
			printf("Sorry! You went over 21. You lose!\n");
			cont = 'n';
		}
		else if (roll_sum >= 16)
		{
			do
			{
				printf("You are at %d and may choose to end your turn. Would you like to continue rolling? (y/n)\n", roll_sum);
				scanf(" %c", &cont);
				if (cont != 'y' && cont != 'n')
					printf("Invalid entry.\n");
			} while (cont != 'y' && cont != 'n');

		}
		else
			printf("You are at %d.\n", roll_sum);

	}
	//Return bet total, roll sum, player funds
	*bets = bet_total;
	*rolls = roll_sum;
	*funds = player_funds;
	//printf("Total roll count: %d\n", roll_sum);
	//printf("Total bet: %d\n", bet_total);
	//printf("Total remaining funds: %d\n", player_funds);
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
	Description: Checks data file to see if funds have been changed. If so, asks player whether to use those values or reset them to the default value.
	Input parameters: None
	Returns: None
	Preconditions: Data file must exist but not be open.
	Postconditions:	If player chooses, funds reset. Otherwise, no change made.
*/
void old_money(void)
{
	char option = '\0';
	int money_check1 = 0, money_check2 = 0, money_check3 = 0, money_check4 = 0, money_check5 = 0;

	//Check to see if a previous game's money values are stored in data file.
	FILE* iofile = NULL;
	iofile = fopen("funds.dat", "r");
	fscanf(iofile, "%d%d%d%d%d", &money_check1, &money_check2, &money_check3, &money_check4, &money_check5);
	//fscanf(iofile, "%d", &money_check1);
	//If any funds differ from default, prompt user to save or overwrite these values.
	if (money_check1 != DEFAULT_FUNDS || money_check2 != DEFAULT_FUNDS || money_check3 != DEFAULT_FUNDS || money_check4 != DEFAULT_FUNDS || money_check5 != DEFAULT_FUNDS)
	{
		while (option != 'y' && option != 'n')
		{
			printf("Would you like to retain the funds from the end of your last game? (y/n)\n");
			scanf(" %c", &option);
			if (option == 'n')
				funds_reset();
		}
	}
	fclose(iofile);
}
/*
	Function: game_intro()
	Date Created: 10/01/2019
	Last Modified: 10/02/2019 Fleshed out
	Description: Begins the game. Checks to see if data file holds any values other than defaults. If so, asks user whether they want to use those values or not. Prompts for number of players.
	Input parameters: None
	Returns: Number of players (int)
	Preconditions: Data file exists for player funds but is not open
	Postconditions: Player funds possibly reset to default. Number of players set for the course of the game.
*/
int game_intro(void)
{
	int player_count = 0;
	printf("Welcome to Blackjack Dice!\n\n");
	old_money();

	printf("Each player begins with $%d. If you have not read the rules, please do so before playing.\n\nBegin.\n", DEFAULT_FUNDS);

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
		if (rolls[i] > max)
			max = rolls[i];
	}
	return max;
}
