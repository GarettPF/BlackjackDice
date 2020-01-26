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
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GAME_RULES 1
#define FUNDS 2
#define PLAY_GAME 3
#define EXIT 4

// sorry since global variables are looked down upon

/* each player has funds [n][0], wager [n][1], score [n][2]
n = player number */
double Players[5][3];

// number of players
int nPlayers;

/*
Function: play_game;
Description: This is where the main game play will take place;
	@param void;
	@return void;
*/
void play_game(void);

/*
Function: game_results;
Description: This is where the winner is determine
			and where funds are changed;
	@param void;
	@return void;
*/
void game_results(void);

/*
Function: chatter;
Description: Function to create chatter amongst players;
	@param type		type of taunt;
	@return void;
*/
void chatter(int type);

/*
Function: menu_selection;
Description: Takes user input and get's the option that they choose;
	@param void;
	@return integer of menu selection;
*/
int menu_selection(void);

/*
Function: determine_option;
Description: get's user selection and determines what to do
			based on users selection;
	@param option			user's int selection;
	@return void;
*/
void determine_option(int option);

/*
Function: display_menu;
Description: Displays the option menu in the beginning of the game;
	@param void;
	@return void;
*/
void display_menu(void);

/*
Function: display_funds;
Description: Displays current funds of all players;
	@param void;
	@return void;
*/
void display_funds(void);

/*
Function: display_scores;
Description: literally displays scores;
	@param void;
	@return void;
*/
void display_scores(void);

/*
Function: pregame_check;
Description: before the game starts, makes sure that the players
			each have a fund in their bank account;
	@param: void;
	@return void;
*/
void pregame_check(void);

/*
Function: get_player_amount;
Description: prompts user for the amount of players playing
			then optimize the game to the amount;
	@param void;
	@return n amount of players;
*/
int get_player_amount(void);


/*
Function: print_game_rules;
Description: Prints out the rules of Blackjack Dice Game;
	@param void;
	@return void;
*/
void print_game_rules(void);

/*
Function: get_bank_balance;
Description: Prompts the player for an initial bank balance
			from which wagering will be added or subtracted.
			The player entered bank balance is return;
	@param void;
	@return players entered bank balance;
*/
double get_bank_balance(void);

/*
Function: get_wager_amount;
Description: Prompts the player for a wager on a particular
			roll. the wager is returned;
	@param void;
	@return The wager;
*/
double get_wager_amount(void);

/*
Function: check_wager_amount;
Description: Checks to make sure wager is within the limits
			of the player's available balance. If the wager
			exceeds the players allowable balance. 0 is return.
			Otherwise 1 is returned;
	@param wager	Wager entered;
	@param balance	Players balance;
	@return			Boolean if within limits;
*/
int check_wager_amount(double wager, double balance);

/*
Function: roll_die;
Description: Rolls a die;
	@param void;
	@return a random number between 1 - 6;
*/
int roll_die(void);

/*
Function: check_duplicates;
Description: checks if there is multiples of the same score;
	@param high			highest score thats != 21;
	@return				true or false;
*/
int check_duplicates(int high);

/*
Function: press_enter;
Description: waits for user to press enter;
	@param void;
	@return void;
*/
void press_enter(void);