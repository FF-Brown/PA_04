/*
	Author: Nathan Brown
	Created: 10/01/2019
	Modified: A lot.
	Description: Terminal version of the game Blackjack Dice for 2-5 players.
*/

#include "mechanics.h"

int main(void)
{
	int player_count = 0;
	int die_roll = 0;
	char cont = 'y';
	int funds[5] = { 0 };
	int bets[5] = { 0, 0, 0, 0, 0 };
	int rolls[5] = { 0, 0, 0, 0, 0 };
	int winners = 0;
	double multiplier[5] = { 0, 0, 0, 0, 0 };
	int max = 0;
	char play_again = '\0';
	int one_win = 0;
	int tie[5] = { 0, 0, 0, 0, 0 };
	int winnings = 0;
	int starting_funds = 0;
	int bet_total = 0, current_bet = 0;
	int single_die = 0;
	int roll_sum = 0;
	bool check = false;

	// ____________
	//|			 |
	//|	0	 0	 |
	//|	0	 0	 |
	//|	0	 0	 |
	//|____________|

	srand(time(NULL));

	//Gameplay
	game_start:
	display_menu(funds);
	if (funds[0] == 0)
	{
		starting_funds = funds_def();
		funds_reset(funds, starting_funds);
	}
	player_count = game_intro();

	//Repeat once for each player
	for (int i = 0; i < player_count; i++)
	{
		//Get inital bet (mandatory) and run bet_check(). Add bet to total, subtract from funds.
		printf("\nBest of luck, Player %d!\n", i+1);
		while (check == false)
		{
			current_bet = bet_initial();
			check = bet_check(current_bet, funds[i]);
			if (check == false)
				printf("You do not have enough money. Please place a lower bet.\n");
		}
		check = false;
		bets[i] += current_bet;
		funds[i] -= current_bet;

		//First roll. Simplified version of subsequent rolls.
		single_die = roll_die();
		rolls[i] = single_die;
		printf("You rolled a %d. ", single_die);
		printf("You are at %d.\n", rolls[i]);

		cont = 'y';
		while (cont == 'y')
		{
			//Offer to take a bet. Call check_bet(). Add to bet_total and subtract from player_funds
			while (!check)
			{
				current_bet = bet_sub();
				check = bet_check(current_bet, funds[i]);
				if (!check)
					printf("You do not have enough money. Please place a lower bet.\n");
			}
			check = false;
			bets[i] += current_bet;
			funds[i] -= current_bet;

			//Roll die. Add to sum. If >=21, force end turn. If >=16, offer to stop rolling.
			single_die = roll_die();
			rolls[i] += single_die;
			printf("You rolled a %d. ", single_die);
			cont = roll_check(rolls, i);

		}

		//Print out final turn info
		printf("Total roll count: %d\n", rolls[i]);
		printf("Total bet: $%d\n", bets[i]);
		printf("Total remaining funds: $%d\n", funds[i]);
	}

	//At this point, game is over.

	//Find max value rolled by any player
	max = max_roll(rolls);
	//Assign bet multipliers according to whether the player rolled the highest number (not concerned with ties here)
	//At the same time, determine "number of winners (whether or not there was a tie)
	winners = multi(rolls, multiplier, winners, max);
	//If tie, change multipliers of winners to 1 and display the tied players and their roll
	if (winners > 1)
		tie_fighter(multiplier, tie, bets, funds, winners, max);

	//If only one winner, tell that player that they won
	else if (winners == 1)
	{
		for (int i = 0; i < 5; i++)
		{
			if (multiplier[i] > 0)
			{
				one_win = i + 1;
				break;
			}
		}
		winnings = bets[one_win - 1] * multiplier[one_win - 1];
		printf("The congratulations go to Player %d, with a roll of %d!\n", one_win, rolls[one_win - 1]);
		printf("Since you bet $%d, you win $%d!\n", bets[one_win - 1], winnings);
		funds[one_win - 1] += winnings;
	}


	//Save player funds to data file for next time
	FILE* iofile = NULL;
	iofile = fopen("funds.dat", "w");
	fprintf(iofile, "%d\n%d\n%d\n%d\n%d\n", funds[0], funds[1], funds[2], funds[3], funds[4]);
	fclose(iofile);

	//End game or loop back to menu
	printf("\nGreat game!!\n");
	while (play_again != 'y' && play_again != 'n')
	{
		printf("Would you like to play again? (y/n)\n");
		scanf(" %c", &play_again);
		if (play_again == 'y')
			goto game_start;
		else if (play_again == 'n')
			exit(0);
		else
			printf("Invalid input.\n");
	}

	return 0;
}