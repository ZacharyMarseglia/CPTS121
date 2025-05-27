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
#define HAND_SIZE 6
#define FACE_TYPES 13
#define SUIT_TYPES 4

typedef struct {
	int faceIndex;
	int suitIndex;
} Card;

//Function Prototypes
void shuffle(int wDeck[][13]);
void deal(const int wDeck[][13], const char* wFace[], const char* wSuit[], Card hand[], Card handTwo[]);
void printHand(const char* wFace[], const char* wSuit[], Card hand[]);
void calcNumTimes(Card hand[], int numTimes[13]);
int CardsPair(Card hand[], int numTimes[13]);
int TwoCardsPair(Card hand[], int numTimes[13]);
int ThreeOfAKind(Card hand[], int numTimes[13]);
int FourOfAKind(Card hand[], int numTimes[13]);
void calcCountSuit(Card hand[], int suitCount[4]);
int CardsFlush(Card hand[], int suitCount[4]);
int CardsStraight(Card hand[], int numTimes[13]);
void printMenu(void);
char handleCharInput(void);
void clearScreen(void);
int evaluateHand(Card hand[]);
void pressKeyToContinue(void);
void reinitializeArrays(Card handOne[], Card handTwo[], int deck[4][13]);
int dealer(Card hand[], int playerOneScore, int playerTwoScore);
void drawNCards(Card hand[], Card handTwo[], int n);
void drawNCardsPlayer(Card hand[], Card handTwo[], int n);
int DuplicateCard(int desiredFace, int desiredSuit, Card handOne[], Card handTwo[]);
void generateCard(int* face, int* suit);
#pragma once
