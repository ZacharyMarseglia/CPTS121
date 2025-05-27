/*****************************************************************
* Programmer: Zachary Marseglia
* Class: CptS 121, Spring 2024; lab section 4
* Programming Assignment: PA7
* April 13, 2024
* Description:This program implements the classic game of Five Card Draw poker.
* Players are dealt five cards and have the option to discard and redraw cards
* to improve their hand. The program evaluates hand rankings and tracks scores
* for both the player and a computer-controlled dealer. It provides a menu interface
* for starting a new game, viewing rules, and quitting.
*****************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"

int main(void) {
	/* initialize suit array with colors */
	const char* suit[4] = {
		"\033[0;31mHearts\033[0;37m\n",
		"\033[0;31mDiamonds\033[0;37m\n",
		"\033[0;32mClubs\033[0;37m\n",
		"\033[0;35mSpades\033[0;37m\n" };

	/* initialize face array with new lines to make it look like a card */
	const char* face[13] = {
		"\n_____\n|A  |\n| C |\n|  E|\n-----  ",
		"\n_______\n|D    |\n| U   |\n|  E  |\n|  C |\n|    E|\n-------   ", 

		"\n_______\n|T    |\n| H   |\n|  R  |\n|   E |\n|    E|\n-------   ",

		"\n______\n|F   |\n| O  |\n|  U |\n|   R|\n------   ",

		"\n______\n|F   |\n| I  |\n|  V |\n|   E|\n------   ", 

		"\n_____\n|S  |\n| I |\n|  X|\n-----   ",
		"\n_______\n|S    |\n| E   |\n|  V  |\n|   E |\n|    N|\n-------    ", 

		"\n_______\n|E    |\n| I   |\n|  G  |\n|   H |\n|    T|\n-------  ",

		"\n______\n|N   |\n| I  |\n|  N |\n|   E|\n------  ",

		"\n_____\n|T  |\n| E |\n|  N|\n-----   ",

		"\n______\n|J   |\n| A  |\n|  C |\n|   K|\n------   ",

		"\n-------\n|Q    |\n| U   |\n|  E  |\n|   E |\n|    N|\n-------  ",

		"\n______\n|K   |\n| I  |\n|  N |\n|   G|\n------  " };

	// initalize deck array
	int deck[4][13] = { 0 };

	//Card array initialization, size 6 to account for 1-5 index cycling in provided code
	Card playerOneHand[6] = { 0 };
	Card playerTwoHand[6] = { 0 };
	int numHands = 0, playerOneScore = 0, playerTwoScore = 0, numCardsToDraw = 0, compCardsToDraw = 0;
	int rowCount = 3, colCount = 12;
	int running = 1;
	int playerScore = 0, houseScore = 0;
	char input = '\0';

	srand((unsigned)time(NULL)); /* seed random-number generator */


	do {
		printMenu();
		input = handleCharInput();
		if (input == 'N') {
			//New game processing
			while (numHands < 10) {
				clearScreen();
				shuffle(deck);
				deal(deck, face, suit, playerOneHand, playerTwoHand);
				printf("YOUR HAND:\n");
				printHand(face, suit, playerOneHand);

				//Initial evaluation
				playerOneScore = evaluateHand(playerOneHand);
				playerTwoScore = evaluateHand(playerTwoHand);

				printf("Score: %d\n", playerOneScore);
				printf("Would you like to redraw cards? Y/N: ");
				input = handleCharInput();
				if (input == 'Y') {
					do {
						clearScreen();
						printHand(face, suit, playerOneHand);
						printf("How many cards would you like to redraw? (max of 3): ");
						scanf("%d", &numCardsToDraw);
					} while (numCardsToDraw > 3);
					clearScreen();
					printHand(face, suit, playerOneHand);
					drawNCardsPlayer(playerOneHand, playerTwoHand, numCardsToDraw);
					printHand(face, suit, playerOneHand);
					playerOneScore = evaluateHand(playerOneHand);
					printf("Score: %d\n", playerOneScore);
				}
				compCardsToDraw = dealer(playerTwoHand, playerOneScore, playerTwoScore);
				clearScreen();
				printf("The dealer drew %d cards.\n", compCardsToDraw);
				drawNCards(playerTwoHand, playerOneHand, compCardsToDraw);
				playerTwoScore = evaluateHand(playerTwoHand);
				pressKeyToContinue();
				clearScreen();
				if (playerOneScore > playerTwoScore) {
					//player 1 has the better hand
					printf("You won the hand!\n");
					printf("YOUR HAND:\n");
					printHand(face, suit, playerOneHand);
					printf("Score: %d\n", playerOneScore);
					printf("\nDEALER'S HAND:\n");
					printHand(face, suit, playerTwoHand);
					printf("Score: %d\n", playerTwoScore);
					playerScore++;
					printf("\nPlayer Score: %d\tHouse Score: %d\n", playerScore, houseScore);

				}
				else if (playerTwoScore > playerOneScore || playerTwoScore == playerOneScore) {
					//player 2 has the better hand (house always wins)
					printf("The house won the hand.\n");
					printf("YOUR HAND:\n");
					printHand(face, suit, playerOneHand);
					printf("Score: %d\n", playerOneScore);
					printf("\nDEALER'S HAND:\n");
					printHand(face, suit, playerTwoHand);
					printf("Score: %d\n", playerTwoScore);
					houseScore++;
					printf("\nPlayer Score: %d\tHouse Score: %d\n", playerScore, houseScore);
				}

				pressKeyToContinue();
				reinitializeArrays(playerOneHand, playerTwoHand, deck);
				numHands++;
			}
			clearScreen();
		}
		else if (input == 'R') {
			//Rules
			clearScreen();
			printf("Five Card Draw is a classic poker variant that is known for its simplicity and is often one of the first\n");
			printf("versions of poker that players learn. It's less about the psychology and betting strategies typical in\n");
			printf("other poker games like Texas Hold'em and more about making the best five-card hand. Here’s a\n");
			printf("general overview of how Five Card Draw is played:\n");
			printf("\nEach player is dealt five cards face down.\n");
			printf("\nStarting with the player to the left of the big blind, players have the option to fold, call, or\n");
			printf("raise. This continues around the table until all bets are equal.\n");
			printf("\nPlayers have the opportunity to improve their hands by discarding up to five cards and receiving \n");
			printf("new ones. The number of cards a player can discard and draw might be limited to three, \n");
			printf("depending on house rules.\n");
			printf("\nThe draw starts with the player to the dealer's left and moves clockwise around the table.Second Round of Betting\n");
			printf("\nAfter the draw, another round of betting occurs, starting again with the player to the dealer's left. \n");
			printf("\nThis round includes options to check (pass the bet), bet, fold, call, or raise, depending on the actions that preceded.\n");
			printf("\nIf more than one player remains after the second round of betting, a showdown occurs where all players reveal their cards.\n");
			printf("\nThe player with the best five - card poker hand wins the pot.");
			printf("\nThe hands in Five Card Draw are ranked similarly to most other poker games:");
			printf("\nRoyal Flush : A, K, Q, J, 10 all of the same suit.");
			printf("\nStraight Flush : Five consecutive cards of the same suit.");
			printf("\nFour of a Kind : Four cards of the same rank.");
			printf("\nFull House : Three of a kind and a pair.");
			printf("\nFlush: Any five cards of the same suit, not consecutive.");
			printf("\nStraight: Five consecutive cards of different suits.");
			printf("\nThree of a Kind : Three cards of the same rank.");
			printf("\nTwo Pair : Two different pairs.");
			printf("\nPair: Two cards of the same rank.");
			printf("\nHigh Card : If no one has any of the above, the highest card wins.");
			pressKeyToContinue();
			clearScreen();
		}
		else if (input == 'Q') {
			running = 0;
		}
	} while (running);

	return 0;
}