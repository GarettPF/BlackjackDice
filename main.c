/*

	Author: Garett Pascual-Folster
	Date: 10/2/2019
	Description:
		Game of blackjack using dice. This program will have
		flexibility with the amount of player, with a max of 5.
		The game is similar to blackjack but instead of using cards
		Dice are used to achieve a score of 21 or close to 21.
		Betting will be implimented and a slightly better GUI.

	10/3/2019:
		Added more functions such as play_game(), menu_selection(),
		determine_option(), display_menu(), get_player_amount().
		Didn't add much to it just did the function declerations and
		comment blocks. Using a way to hold the players stats using
		a 2-dimensional array. this array will be passed around a lot
		through out both the main.c file and functions.c file and functions.
		Using a general game loop in the main.c where the main menu will be.
		Using system("cls") to make output cleaner.

	10/4/2019:
		Added body code for the functions. figured out how
		to use 2-dimensional arrays throughout functions and
		passing it around between files. for print_game_rules()
		played around with catching the "enter" key as an input
		to continue through the code.

	10/7/2019:
		Decided to use global variables for the program. playerStats
		will be global so that it can be shared across the files and
		functions. created global variable nPlayers

	10/9/2019:
		Did some slight tweaks on the algorithms. Mainly check_duplicates,
		play_game, and game_results. made changes to redundent code and
		worked on reducing line lengths on functions. Fixed check_duplicates
		function to work. added functions display_scores and display_funds
		to add some visual aspect to the game. Fixed "GUI".
*/

#include "functions.h"

int main(void) {

	int isPlaying = 1, option = 0;

	// Ask for the number of Players
	nPlayers = get_player_amount();

	// Set random seed
	srand(time(NULL));

	//start menu
	while (isPlaying) {
		option = menu_selection();
		determine_option(option);
		if (option == EXIT) {
			isPlaying = 0;
		}
	}

	printf("Shutting down...\n");

	return 0;
}