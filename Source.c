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
#include <stdio.h>
#include <stdint.h>
#include "Header.h"

// Function to shuffle a deck of cards
void shuffle(int wDeck[][13])
{
	int row = 0;    // Initialize row index
	int column = 0; // Initialize column index
	int card = 0;   // Initialize card counter

	// For each of the 52 cards, randomly select a slot in the deck
	for (card = 1; card <= 52; card++)
	{
		// Choose a new random location until an unoccupied slot is found
		do
		{
			row = rand() % 4; // Randomly select a row
			column = rand() % 13;// Randomly select a column
		} while (wDeck[row][column] != 0); // Repeat until empty slot is found

		// Place the card number in the chosen slot of the deck
		wDeck[row][column] = card;
	}
}

// Function to deal cards from the deck to two hands

void deal(const int wDeck[][13], const char* wFace[], const char* wSuit[], Card hand[], Card handTwo[])
{
	int row = 0;    // Initialize row index
	int column = 0; // Initialize column index
	int card = 0;   // Initialize card counter
	int i = 1;      // Initialize index for hand arrays

	// Deal 10 cards
	for (card = 1; card <= 10; card++)
	{
		// Loop through rows of wDeck
		for (row = 0; row <= 3; row++)
		{
			// Loop through columns of wDeck for current row
			for (column = 0; column <= 12; column++)
			{
				// If slot contains current card, assign to a hand
				if (wDeck[row][column] == card)
				{
					// Assign card to appropriate hand
					if (card % 2 == 0) {
						// Assign card to the first hand
						hand[i].suitIndex = row;
						hand[i].faceIndex = column;
						i++;
					}
					else {
						// Assign card to the second hand
						handTwo[i].suitIndex = row;
						handTwo[i].faceIndex = column;
					}
				}
			}
		}
	}
}

// Function to print a hand of cards
// No return value, parameters include string arrays wFace and wSuit, and an array of Cards.

void printHand(const char* wFace[], const char* wSuit[], Card hand[]) {
	// Iterate through the hand
	for (int i = 1; i <= 5; i++) {
		// Print each card in the hand
		printf("%d: %5s of %-8s%c", i, wFace[hand[i].faceIndex], wSuit[hand[i].suitIndex], i % 2 == 0 ? '\n' : '\t');
	}
}


// Function to calculate the number of occurrences of each face card in a hand
// No return value, parameters include an array of Card objects (hand) and an array of integers (numTimes).
// Populates the numTimes array with the specific count of each face card.
void calcNumTimes(Card hand[], int numTimes[13]) {
	//Reinitializes array
	for (int i = 0; i < FACE_TYPES; i++) {
		numTimes[i] = 0;
	}

	// Populate numTimes array with count of every specific face card
	for (int i = 1; i < HAND_SIZE; i++) {
		switch (hand[i].faceIndex) {
		case 1: // Ace
			numTimes[0]++;
			break;
		case 2: // Deuce
			numTimes[1]++;
			break;
		case 3: // Three
			numTimes[2]++;
			break;
		case 4: // Four
			numTimes[3]++;
			break;
		case 5: // Five
			numTimes[4]++;
			break;
		case 6: // Six
			numTimes[5]++;
			break;
		case 7: // Seven
			numTimes[6]++;
			break;
		case 8: // Eight
			numTimes[7]++;
			break;
		case 9: // Nine
			numTimes[8]++;
			break;
		case 10: // Ten
			numTimes[9]++;
			break;
		case 11: // Jack
			numTimes[10]++;
			break;
		case 12: // Queen
			numTimes[11]++;
			break;
		case 13: // King
			numTimes[12]++;
			break;
		}
	}
}

// Function CardsPair: 
// Checks if the hand contains a pair of cards with the same face value.
// Returns an integer: 1 if a pair is found, 0 otherwise.
// Parameters: array of Card objects (hand) and an array of integers (numTimes).
// Prerequisite: calcNumTimes has been called to populate numTimes.
int CardsPair(Card hand[], int numTimes[FACE_TYPES]) {
	// Two of the same face indices in hand array
	// Iterate through all possible options for face values (indices 0-12)
	for (int i = 0; i < FACE_TYPES; i++) {
		if (numTimes[i] == 2) {
			return 1;
		}
	}
	return 0;
}
// Function TwoCardsPair: 
// Checks if the hand contains two pairs of cards with the same face value.
// Returns an integer: 1 if two pairs are found, 0 otherwise.
// Parameters: array of Card objects (hand) and an array of integers (numTimes).
// Prerequisite: calcNumTimes has been called to populate numTimes.
// This function essentially performs the same logic as CardsPair twice, using an additional count variable for tracking.
int TwoCardsPair(Card hand[], int numTimes[FACE_TYPES]) {
	int count = 0;
	// Two of the same face indices in hand array... twice
	for (int i = 0; i < FACE_TYPES; i++) {
		if (numTimes[i] == 2) {
			count++;
		}
	}
	if (count == 2) {
		return 1;
	}
	return 0;
}

// Function ThreeOfAKind: 
// Checks if the hand contains a three-of-a-kind (3 cards with the same face value).
// Returns an integer: 1 if three-of-a-kind is found, 0 otherwise.
// Parameters: array of Card objects (hand) and an array of integers (numTimes).
// Prerequisite: calcNumTimes has been called to populate numTimes.
int ThreeOfAKind(Card hand[], int numTimes[FACE_TYPES]) {
	// Iterate through all possible options for face values (indices 0-12)
	for (int i = 0; i < FACE_TYPES; i++) {
		if (numTimes[i] == 3) {
			return 1;
		}
	}
	return 0;
}

// Function FourOfAKind: 
// Checks if the hand contains a four-of-a-kind (4 cards with the same face value).
// Returns an integer: 1 if four-of-a-kind is found, 0 otherwise.
// Parameters: array of Card objects (hand) and an array of integers (numTimes).
// Prerequisite: calcNumTimes has been called to populate numTimes.
int FourOfAKind(Card hand[], int numTimes[FACE_TYPES]) {
	// Iterate through all possible options for face values (indices 0-12)
	for (int i = 0; i < FACE_TYPES; i++) {
		if (numTimes[i] == 4) {
			return 1;
		}
	}
	return 0;
}

// Function calcCountSuit: 
// Populates the suitCount array with the count of each suit in the hand.
// Parameters: array of Card objects (hand) and an array of integers (suitCount).
// This function has no return value.
// For example, suitCount at index 0 will contain 5 if all 5 cards in the hand are hearts.
void calcCountSuit(Card hand[], int suitCount[SUIT_TYPES]) {
	// Reinitializes the suitCount array
	for (int i = 0; i < SUIT_TYPES; i++) {
		suitCount[i] = 0;
	}

	// Iterate through the hand to count suits
	for (int i = 1; i < HAND_SIZE; i++) {
		// Count each suit occurrence
		switch (hand[i].suitIndex) {
		case 0: // Hearts
			suitCount[0]++;
			break;
		case 1: // Diamonds
			suitCount[1]++;
			break;
		case 2: // Clubs
			suitCount[2]++;
			break;
		case 3: // Spades
			suitCount[3]++;
			break;
		}
	}
}

// Function CardsFlush: 
// Returns an integer indicating if the hand contains a flush (all cards of the same suit).
// Parameters: array of Card objects (hand) and array of integers (suitCount).
// Prerequisite: calcCountSuit has been called to populate suitCount.
// Returns 1 if a flush is found, 0 otherwise.
int CardsFlush(Card hand[], int suitCount[4]) {
	//Hand contains 5 of the same suit
	for (int i = 0; i < SUIT_TYPES; i++) {
		if (suitCount[i] == 5) {
			return 1;
		}
	}
	return 0;
}

// Function CardsStraight: 
// Returns an integer indicating if the hand contains a straight (five consecutive face values).
// Parameters: array of Card objects (hand) and array of integers (numTimes).
// Prerequisite: calcNumTimes has been called to populate numTimes.
// Returns 1 if a straight is found, 0 otherwise.
int CardsStraight(Card hand[], int numTimes[13]) {
	int count = 0;
	//Hand is of 5 consecutive face values
	//There should be a row of five 1's in numTimes consecutively
	for (int i = 0; i < FACE_TYPES; i++) {
		if (numTimes[i] == 1) {
			count++;
		}
		else if (numTimes[i] == 0 && count == 5) {
			return 1;
		}
		else {
			count = 0;
		}
	}

	if (count == 5) {
		return 1;
	}

	return 0;
}

// Function printMenu: 
// Prints out the menu options using printf functions.
// No return value, no parameters.
void printMenu(void) {
	printf(" 5 Card Draw\n");
	printf(" N:New Game/Start\n");
	printf(" R:Rules\n");
	printf(" Q:Quit/Exit\n");
}

// Function handleCharInput: 
// Reads a character input from the user using a scanf call.
// Returns the character read from the user.
// No parameters.
char handleCharInput(void) {
	char in = '\0';
	scanf(" %c", &in);
	in = toupper(in);
	return in;
}

// Function clearScreen: 
// Clears the screen using a system call. (Windows-specific.)
// No return value, no parameters.
void clearScreen(void) {
	system("cls");
}

// Function evaluateHand: 
// Evaluates the parameter hand and generates and returns a point matrix based on aspects of the hand.
// Returns an integer representing the points scored by the hand.
// Parameter: array of Card objects (hand).
int evaluateHand(Card hand[]) {
	int points = 0;
	int numTimes[13], suitCount[4];
	calcNumTimes(hand, numTimes);
	calcCountSuit(hand, suitCount);
	//A pair is worth 1, two pairs is worth 2, three of a kind is worth 3, straight is worth 4, flush 5, four of a kind 6
	if (CardsPair(hand, numTimes))
		points++;
	if (TwoCardsPair(hand, numTimes) && CardsPair(hand, numTimes))
		points++;
	if (ThreeOfAKind(hand, numTimes))
		points += 3;
	if (CardsStraight(hand, numTimes))
		points += 4;
	if (CardsFlush(hand, suitCount))
		points += 5;
	if (FourOfAKind(hand, numTimes))
		points += 6;
	return points;
}

// Function pressKeyToContinue: 
// Pauses program execution using a system call. (Windows-specific.)
// No return value, no parameters.
void pressKeyToContinue(void) {
	system("pause");
}

//Function reinitializeArrays, no return, parameters arrays of Card objects handOne and handTwo, 2D array of integers deck
//Resets all values of arrays back to 0.
void reinitializeArrays(Card handOne[], Card handTwo[], int deck[4][13]) {
	for (int i = 0; i < 6; i++) {
		handOne[i].faceIndex = 0;
		handOne[i].suitIndex = 0;
		handTwo[i].faceIndex = 0;
		handTwo[i].suitIndex = 0;
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			deck[i][j] = 0;
		}
	}
}

//Function dealer, return integer, parameters array of Card objects hands, integers playerOneScore and playerTwoScore.
//Prerequisite: evaluateHand called on both hands and stored.
//Determines how many cards the dealer needs to pull based on current hand score.
int dealer(Card hand[], int playerOneScore, int playerTwoScore) {
	if (playerTwoScore <= playerOneScore) {
		if (playerTwoScore < 3) {
			//draw 1 card
			return 1;
		}
		else if (playerTwoScore < 2) {
			//draw 2 cards
			return 2;
		}
		else if (playerTwoScore < 1) {
			//draw 3 cards
			return 3;
		}
	}
	return 0;
}

// Function drawNCards: 
// Generates random cards and indices for the dealer to draw cards. This process repeats n times.
// No return value.
// Parameters: arrays of Card objects (hand and handTwo) and an integer (n) specifying the number of cards to draw.
void drawNCards(Card hand[], Card handTwo[], int n) {
	int usedIndices[6] = { 0 };
	int randIndex = 0, generating = 0, creatingCard = 0, face = 0, suit = 0;
	//Generate random index to place card in
	for (int i = 0; i < n; i++) {
		generating = 1;
		while (generating) {
			randIndex = rand() % 5 + 1;
			for (int j = 1; j < 6; j++) {
				if (randIndex == j && usedIndices[randIndex] == 1) {
					generating = 1;
					break;
				}
				generating = 0;
			}
		}

		creatingCard = 1;
		while (creatingCard) {
			generateCard(&face, &suit);
			if (DuplicateCard(face, suit, hand, handTwo) == 0) {
				creatingCard = 0;
			}
		}
		usedIndices[randIndex] = 1;
		hand[randIndex].faceIndex = face;
		hand[randIndex].suitIndex = suit;
	}
}

// Function drawNCardsPlayer: 
// Generates a random card to be drawn, requests which card to be drawn, and replaces the respective card in the hand.
// No return value.
// Parameters: arrays of Card objects (hand and handTwo) and an integer (n) specifying the number of cards to draw.
void drawNCardsPlayer(Card hand[], Card handTwo[], int n) {
	int input = 0, face = 0, suit = 0, generating = 0;
	for (int i = 0; i < n; i++) {
		generating = 1;
		while (generating) {
			generateCard(&face, &suit);
			if (DuplicateCard(face, suit, hand, handTwo) == 0) {
				generating = 0;
			}
		}
		printf("What card would you like to redraw? 1-5: ");
		scanf("%d", &input);
		switch (input) {
		case 1:
			hand[1].faceIndex = face;
			hand[1].suitIndex = suit;
			break;
		case 2:
			hand[2].faceIndex = face;
			hand[2].suitIndex = suit;
			break;
		case 3:
			hand[3].faceIndex = face;
			hand[3].suitIndex = suit;
			break;
		case 4:
			hand[4].faceIndex = face;
			hand[4].suitIndex = suit;
			break;
		case 5:
			hand[5].faceIndex = face;
			hand[5].suitIndex = suit;
			break;
		}
	}
}

// Function DuplicateCard: 
// Checks if the desiredFace and desiredSuit integers are already present in handOne and handTwo arrays.
// Returns 1 if the card is already in the hands, 0 otherwise.
// This is necessary because the D&D starter code does not modify the deck once a card has been dealt.
// Returns an integer.
// Parameters: integers desiredFace and desiredSuit representing the face and suit of the card, and arrays of Card objects (handOne and handTwo).
int DuplicateCard(int desiredFace, int desiredSuit, Card handOne[], Card handTwo[]) {
	//Check through first hand
	for (int i = 1; i < 6; i++) {
		if ((handOne[i].faceIndex == desiredFace && handOne[i].suitIndex == desiredSuit) || (handTwo[i].faceIndex == desiredFace && handTwo[i].suitIndex == desiredSuit)) {
			return 1;
		}
	}
	return 0;
}

// Function generateCard: 
// Generates a random card by assigning random numbers to the face and suit pointers.
// No return value.
// Parameters: pointers to integers face and suit.
void generateCard(int* face, int* suit) {
	*face = rand() % 13;
	*suit = rand() % 4;
}