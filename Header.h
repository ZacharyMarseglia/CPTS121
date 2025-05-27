#define _CRT_SECURE_NO_WARNINGS
#ifndef Header_H
#define Header_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define HORIZONTAL 0
#define VERTICAL 1
#define NUM_ROWS 10
#define NUM_COLS 10
#define CARRIER_LENGTH 5
#define BATTLESHIP_LENGTH 4
#define SUBMARINE_LENGTH 3
#define CRUISER_LENGTH 3
#define DESTROYER_LENGTH 2

typedef struct {
	int numHits, numMisses, totalShots;
	double hitsMisses;
} Stats;
// Function Prototypes
void initializeBoard(char board[10][10], int num_rows, int num_columns);
void printBoard(char board[10][10], int num_rows, int num_columns);
int generateDirection(void);
void generateStartingPoint(int direction, int ship_length, int* row, int* column);
void placeShip(char board[][NUM_COLS], int numRows, int numCols, int ship_length, char ship_symbol, int direction, int row_start, int col_start);
int detectCollision(char board[][NUM_COLS], int direction, int ship_length, int row, int col);
int selectWhoStartsFirst(void);
void manuallyPlaceShips(char board[][NUM_COLS]);
int checkPlacement(char board[][NUM_COLS], int coords[], int shipSize);
void bubbleSort(int array[], int size); 
int isWinner(char board[][NUM_COLS]);
void updateBoard(char board[][NUM_COLS], int xPos, int yPos, int wasHit);
int checkShot(char board[][NUM_COLS], int xPos, int yPos, char* token);
int checkIfSunkShip(char board[][NUM_COLS], char shipToken);
void outputCurrentMove(FILE* outfile, int currentPlayer, int xPos, int yPos, int wasHit, int wasSunk);
void outputStats(FILE* outfile, Stats playerOne, Stats playerTwo);
#endif
#pragma once
