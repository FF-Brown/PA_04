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
	int funds[5] = { DEFAULT_FUNDS, DEFAULT_FUNDS, DEFAULT_FUNDS, DEFAULT_FUNDS, DEFAULT_FUNDS };
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

	srand(time(NULL));

	//Gameplay
	display_menu();
	player_count = game_intro();

	for (int i = PLAYER1; i <= player_count; i++)
	{
		turn_flow(i, funds[i - 1], &bets[i - 1], &rolls[i - 1], &funds[i - 1]);
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
				one_win = i + 1;
		}
		winnings = bets[one_win] * multiplier[one_win];
		printf("The congratulations go to Player %d, with a roll of %d!\n", one_win, rolls[one_win]);
		printf("Since you bet %d, you win $%d!\n", bets[one_win], winnings);
		funds[one_win] += winnings;
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
		scanf("%d", &play_again);
		if (play_again == 'y')
			display_menu();
		else if (play_again == 'n')
			exit(0);
		else
			printf("Invalid input.\n");
	}

	return 0;
}