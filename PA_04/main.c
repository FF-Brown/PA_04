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
	int bet_p1 = 0, bet_p2 = 0, bet_p3 = 0, bet_p4 = 0, bet_p5 = 0;
	char cont = 'y';
	int funds[5] = { 0 };
	int bets[5] = { 0, 0, 0, 0, 0 };
	int rolls[5] = { 0, 0, 0, 0, 0 };
	int winner[5] = { 0, 0, 0, 0, 0 };
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

	srand(time(NULL));

	//Gameplay
	game_start:
	display_menu(funds);
	player_count = game_intro();
	starting_funds = funds_def();
	funds_reset(funds, starting_funds);

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

			//Roll die. Add to sum. If 16+, offer to stop rolling.
			single_die = roll_die();
			rolls[i] += single_die;
			printf("You rolled a %d. ", single_die);
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

		}

		printf("Total roll count: %d\n", rolls[i]);
		printf("Total bet: %d\n", bets[i]);
		printf("Total remaining funds: %d\n", funds[i]);
	}

	//At this point, game is over.

	//Find max value rolled by any player
	max = max_roll(rolls);
	//Assign bet multipliers according to whether the player rolled the highest number (not concerned with ties here)
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

	//If tie, change multipliers of winners to 1 and display the tied players and their roll
	if (winners > 1)
	{
		int j = 0;
		for (int i = 0; i < 5; i++)
		{
			if (multiplier[i] > 0)
			{
				multiplier[i] = 1;
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
		printf("Since you bet %d, you win $%d!\n", bets[one_win - 1], winnings);
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