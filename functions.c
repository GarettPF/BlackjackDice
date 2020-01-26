/*

	Author: Garett Pascual-Folster
	Date: 10/2/2019
	Description:
		Game of blackjack using dice. This program will have
		flexibility with the amount of player, with a max of 5.
		The game is similar to blackjack but instead of using cards
		Dice are used to achieve a score of 21 or close to 21.
		Betting will be implimented and a slightly better GUI.

*/

#include "functions.h"

void play_game(void) {
	for (int p = 0; p < nPlayers; p++) {
		double
			* funds = &Players[p][0],
			* wager = &Players[p][1],
			* score = &Players[p][2];
		int roll = 1, isPlaying = 1, dice = 0, taunt = 0;

		
		do { // get wager amount
			system("cls");
			display_scores();
			printf("Player %d, your up\n", p + 1);
			if (*funds > 199) { chatter(1); }

			printf("\nWhat is the wager amount for player %d\n", p + 1);
			printf("Current funds for P1 = $%.2lf\n", *funds);
			*wager = get_wager_amount();
		} while (!check_wager_amount(*wager, *funds));
		*funds -= *wager;
		printf("Current funds: %.2lf\n\n", *funds);


		do { // roll die till 16 or over
			dice = roll_die();
			printf("Roll %d: %d\n", roll++, dice);
			*score += dice;
		} while (*score < 16);
		printf("\nTotal is %d\n\n", (int)*score);


		// score is already = 21
		if (*score == 21) { isPlaying = 0; }

		// ask for more rolls
		while (isPlaying) {
			char choice = '\0';
			printf("Roll again? (y/n): ");
			scanf(" %c", &choice);

			if (choice == 'y') {
				dice = roll_die();
				printf("Roll %d: %d\n", roll++, dice);
				*score += dice;
				printf("Total is %d\n\n", (int)*score);
				if (*score > 21) {
					// player has bust
					chatter(3);
					isPlaying = 0;
				}
				else if (*score == 21) { isPlaying = 0; }
			} 
			else {
				if (taunt++ == 0) { chatter(4); } // only taunt once
				else { isPlaying = 0; }
			}
		}
		press_enter();
	}

	// check winnings
	game_results();
}

void game_results(void) {
	int score = 0, highest = 0, foundWinner = 0, p;
	double wager;

	system("cls");
	display_scores();
	// check if any score is = 21
	for (p = 0; p < nPlayers; p++) {
		wager = Players[p][1];
		score = (int)Players[p][2];
		if (score == 21) {
			printf("Player %d wins with 21\nAdded %.2lf\n", p + 1, wager * 2);
			Players[p][0] += (wager * 2);
			foundWinner = 1;
			highest = 21;
		}
		else if (score > highest && score < 21) {
			highest = score;
		}
	}

	// if no one scored 21
	if (!foundWinner) {
		if (!check_duplicates(highest)) {
			for (p = 0; p < nPlayers; p++) {
				wager = Players[p][1];
				score = (int)Players[p][2];
				if (score == highest) {
					printf("Player %d wins with %d\nAdded %.2lf\n",
						p + 1, score, wager * 1.5);
					Players[p][0] += (wager * 1.5);
				}
			}
		}
		else {
			// if there are duplicates in scores that are != 21
			printf("No one wins\n");
			for (p = 0; p < nPlayers; p++) {
				if (Players[p][2] == highest) { 
					printf("Player %d gets back %.2lf\n", p + 1, Players[p][1]);
					Players[p][0] += Players[p][1]; 
				}
				else {
					printf("Player %d get nothing\n", p + 1);
				}
			}
		}
	}

	press_enter();
}

void chatter(int type) {
	switch (type) {
	case 1:
		printf("You're up big, nows the time to cash in your chips!\n");
		break;
	case 2:
		printf("Oh, your going for broke, huh?\n");
		break;
	case 3:
		printf("Sorry, you busted!\n");
		break;
	case 4:
		printf("Aw cmon, take a chance!\n\n");
		break;
	}
}

int menu_selection(void) {
	int option = 0;

	do {
		display_menu();
		scanf("%d", &option);
		system("cls");
	} while (option < GAME_RULES || option > EXIT);

	return option;
}

void determine_option(int option) {
	switch (option) {
	case GAME_RULES:
		print_game_rules();
		break;
	case FUNDS:
		display_funds();
		for (int i = 0; i < nPlayers; i++) {
			printf("Enter a bank balance for player %d: ", i + 1);
			Players[i][0] = get_bank_balance();
		}
		break;
	case PLAY_GAME:
		// check if each player has a bank balance
		pregame_check();
		break;
	}
}

void display_menu(void) {
	system("cls");
	printf("------ Welcome to Blackjack Dice ------\n");
	printf("1.    Display game rules\n");
	printf("2.    Add funds to bank balance.\n");
	printf("3.    Play game.\n");
	printf("4.    Exit.\n");

	display_funds();
}

void display_funds(void) {
	printf("\n~BANK ACCOUNTS~\n");
	for (int i = 0; i < nPlayers; i++) {
		printf("Player %d's balance = %.2lf\n", i + 1, Players[i][0]);
	}
}

void display_scores(void) {
	printf("-- SCORES --\n");
	for (int p = 0; p < nPlayers; p++) {
		if ((int)Players[p][2] > 21) {
			printf("Player %d: BUST\n", p + 1);
		}
		else {
			printf("Player %d: %d\n", p + 1,
				(int)Players[p][2]);
		}
	}
	printf("\n");
}

void pregame_check(void) {
	int allGood = 1;
	for (int i = 0; i < nPlayers; i++) {
		if (Players[i][0] == 0) { allGood = 0; }
		Players[i][1] = 0;
		Players[i][2] = 0;
	}

	if (allGood) {
		play_game();
	}
	else {
		printf("All players must have funds\n");
		press_enter();
	}
}

int get_player_amount(void) {
	int n = 0;

	do {
		system("cls");
		printf("Hello welcome to BlackJack Dice\n");
		printf("Before we begin, how many players are there (up to 5): ");
		scanf("%d", &n);
	} while (n < 1 || n > 5);

	return n;
}

void print_game_rules(void) {
	system("cls");
	printf("Rules: \n");

	FILE* rules = fopen("rules.txt", "r");
	while (!feof(rules)) {
		char line[200];
		fscanf(rules, "%200[^\n]\n", line);
		printf("%s\n", line);
	}
	fclose(rules);

	press_enter();
}

double get_bank_balance(void) {
	double amount = 0.0;

	do { // make sure amount is greater than 0
		scanf("%lf", &amount);
	} while (amount <= 0.0);

	return amount;
}

double get_wager_amount(void) {
	double wager = 0.0;

	do { // make sure wager is above 0
		scanf("%lf", &wager);
		printf("\n");
	} while (wager <= 0.0);

	return wager;
}

int check_wager_amount(double wager, double balance) {
	int allGood = 0;

	if (wager <= balance) { //wager should already be > 0
		allGood = 1;
		if (wager == balance) {
			chatter(2);
		}
	}

	return allGood;
}

int roll_die(void) {
	int die_value = 0;
	die_value = rand() % 6 + 1;
	return die_value;
}

int check_duplicates(int high) {
	int score1, score2;
	int isDuplicates = 0;
	for (int i = 0; i < nPlayers; i++) {
		score1 = (int)Players[i][2];
		for (int j = i + 1; j < nPlayers; j++) {
			score2 = (int)Players[j][2];
			if (score1 == score2) {
				if (score1 == high) { isDuplicates = 1; }
			}
		}
	}
	return isDuplicates;
}

void press_enter(void) {
	/* I know we never learned this in class
		but it works tho so idk */
	getchar();

	do {
		printf("\n--- Press Enter to Continue ---");
	} while (getchar() != 10);
}