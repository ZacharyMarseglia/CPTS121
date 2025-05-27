#include "header.h"


// Initializes all cells of the provided game board to '~' representing water.
void initializeBoard(char board[10][10], int num_rows, int num_columns) {
	for (int i = 0; i < num_rows; i++) {
		for (int j = 0; j < num_columns; j++) {
			board[i][j] = '~'; 
		}
	}
}

//Outputs the contents of the provided game board with row and column indices.
void printBoard(char board[10][10], int num_rows, int num_columns) {
	for (int i = 0; i < num_rows; i++) {
		if (i == 0) {
			printf("    0  1  2  3  4  5  6  7  8  9\n");
		}
		for (int j = 0; j < num_columns; j++) {
			if (j == 0) {
				printf(" %d ", i);
			}
			printf(" %c ", board[i][j]);
		}
		printf("\n");
	}
}

//Generates a random number 0-1, 0 being horizontal, 1 vertical, returns it.
int generateDirection(void) {
	return rand() % 2;
}

//Generates a random starting point for a ship based on the specified direction, ship length, row, and column.
void generateStartingPoint(int direction, int ship_length, int* row, int* column) {
	if (direction == HORIZONTAL) {
		*row = rand() % NUM_ROWS;
		*column = rand() % (NUM_COLS - ship_length + 1);
	}
	else if (direction == VERTICAL) {
		*column = rand() % NUM_COLS;
		*row = rand() % (NUM_ROWS - ship_length + 1);
	}
}
// Places a ship symbol on the game board starting from the specified row and column based on the given direction.
void placeShip(char board[][NUM_COLS], int numRows, int numCols, int ship_length, char ship_symbol, int direction, int row_start, int col_start) {
	if (direction == HORIZONTAL) {
		for (int i = 0; i < ship_length; i++) {
			board[row_start][col_start + i] = ship_symbol;
		}
	}
	else if (direction == VERTICAL) {
		for (int i = 0; i < ship_length; i++) {
			board[row_start + i][col_start] = ship_symbol;
		}
	}
}


//Checks if there is a collision for ship placement at the specified row and column based on the given direction.
//Returns 1 if valid placement, 0 if not.
int detectCollision(char board[][NUM_COLS], int direction, int ship_length, int row, int col) {
	if (direction == HORIZONTAL) {
		for (int i = 0; i < ship_length; i++) {
			if (board[row][col + i] != '~') { 
				return 0; // Invalid placement as soon as a collision is detected
			}
		}
	}
	else if (direction == VERTICAL) {
		for (int i = 0; i < ship_length; i++) {
			if (board[row + i][col] != '~') { // Changed from '-' to '~'
				return 0; // Invalid placement as soon as a collision is detected
			}
		}
	}
	return 1; // Valid placement if no collision detected
}


//Returns 0 if player 1 starts, 1 if player 2 (computer) starts.
int selectWhoStartsFirst(void) {
	return rand() % 2;
}

// Allows the player to manually place each ship on the game board by inputting row and column coordinates.
// Provides prompts for each ship and ensures valid placement according to the game rules.
void manuallyPlaceShips(char board[][NUM_COLS]) {
	int row = 0, col = 0;
	int carrierCoords[CARRIER_LENGTH * 2] = { 0 }, battleshipCoords[BATTLESHIP_LENGTH * 2] = { 0 },
		submarineCoords[SUBMARINE_LENGTH * 2] = { 0 }, cruiserCoords[CRUISER_LENGTH * 2] = { 0 }, destroyerCoords[DESTROYER_LENGTH * 2] = { 0 };
carrierPlacement:
	printf("Please enter the cells you would like to place the carrier in:\n");
	int count = 0;
	for (int i = 0; i < (CARRIER_LENGTH * 2); i += 2) {
		printf("Row #%d: ", ++count);
		scanf("%d", &row);
		printf("Col #%d: ", count);
		scanf("%d", &col);
		if ((row >= 0 && row <= 9) && (col >= 0 && col <= 9)) {
			carrierCoords[i] = row;
			carrierCoords[i + 1] = col;
		}
		else {
			printf("Invalid row/column values!\n");
			goto carrierPlacement;
		}
	}
	if (checkPlacement(board, carrierCoords, CARRIER_LENGTH) == 0) {
		printf("That placement isn't valid! Please try again.\n");
		goto carrierPlacement;
	}
	//Carrier initialization/placement on board
	for (int i = 0; i < (CARRIER_LENGTH * 2); i += 2) {
		board[carrierCoords[i]][carrierCoords[i + 1]] = 'C';
	}
	printBoard(board, NUM_ROWS, NUM_COLS);

battleshipPlacement:
	count = 0;
	printf("Please enter the cells you would like to place the battleship in:\n");
	for (int i = 0; i < (BATTLESHIP_LENGTH * 2); i += 2) {
		printf("Row #%d: ", ++count);
		scanf("%d", &row);
		printf("Col #%d: ", count);
		scanf("%d", &col);
		if ((row >= 0 && row <= 9) && (col >= 0 && col <= 9)) {
			battleshipCoords[i] = row;
			battleshipCoords[i + 1] = col;
		}
		else {
			printf("Invalid row/column values!\n");
			goto battleshipPlacement;
		}
	}
	if (checkPlacement(board, battleshipCoords, BATTLESHIP_LENGTH) == 0) {
		printf("That placement isn't valid! Please try again.\n");
		goto battleshipPlacement;
	}
	//Battleship initialization/placement on board
	for (int i = 0; i < (BATTLESHIP_LENGTH * 2); i += 2) {
		board[battleshipCoords[i]][battleshipCoords[i + 1]] = 'B';
	}
	printBoard(board, NUM_ROWS, NUM_COLS);

submarinePlacement:
	count = 0;
	printf("Please enter the cells you would like to place the submarine in:\n");
	for (int i = 0; i < SUBMARINE_LENGTH * 2; i += 2) {
		printf("Row #%d: ", ++count);
		scanf("%d", &row);
		printf("Col #%d: ", count);
		scanf("%d", &col);
		if ((row >= 0 && row <= 9) && (col >= 0 && col <= 9)) {
			submarineCoords[i] = row;
			submarineCoords[i + 1] = col;
		}
		else {
			printf("Invalid row/column values!\n");
			goto submarinePlacement;
		}
	}
	if (checkPlacement(board, submarineCoords, SUBMARINE_LENGTH) == 0) {
		printf("That placement isn't valid! Please try again.\n");
		goto submarinePlacement;
	}
	//Submarine initialization/placement on board
	for (int i = 0; i < (SUBMARINE_LENGTH * 2); i += 2) {
		board[submarineCoords[i]][submarineCoords[i + 1]] = 'S';
	}
	printBoard(board, NUM_ROWS, NUM_COLS);

cruiserPlacement:
	count = 0;
	printf("Please enter the cells you would like to place the cruiser in:\n");
	for (int i = 0; i < CRUISER_LENGTH * 2; i += 2) {
		printf("Row #%d: ", ++count);
		scanf("%d", &row);
		printf("Col #%d: ", count);
		scanf("%d", &col);
		if ((row >= 0 && row <= 9) && (col >= 0 && col <= 9)) {
			cruiserCoords[i] = row;
			cruiserCoords[i + 1] = col;
		}
		else {
			printf("Invalid row/column values!\n");
			goto cruiserPlacement;
		}
	}
	if (checkPlacement(board, cruiserCoords, CRUISER_LENGTH) == 0) {
		printf("That placement isn't valid! Please try again.\n");
		goto cruiserPlacement;
	}
	//Cruiser initialization/placement on board
	for (int i = 0; i < (CRUISER_LENGTH * 2); i += 2) {
		board[cruiserCoords[i]][cruiserCoords[i + 1]] = 'R';
	}
	printBoard(board, NUM_ROWS, NUM_COLS);

destroyerPlacement:
	count = 0;
	printf("Please enter the cells you would like to place the destroyer in:\n");
	for (int i = 0; i < DESTROYER_LENGTH * 2; i += 2) {
		printf("Row #%d: ", ++count);
		scanf("%d", &row);
		printf("Col #%d: ", count);
		scanf("%d", &col);
		if ((row >= 0 && row <= 9) && (col >= 0 && col <= 9)) {
			destroyerCoords[i] = row;
			destroyerCoords[i + 1] = col;
		}
		else {
			printf("Invalid row/column values!\n");
			goto destroyerPlacement;
		}
	}
	if (checkPlacement(board, destroyerCoords, DESTROYER_LENGTH) == 0) {
		printf("That placement isn't valid! Please try again.\n");
		goto destroyerPlacement;
	}
	//Destroyer initialization/placement on board
	for (int i = 0; i < (DESTROYER_LENGTH * 2); i += 2) {
		board[destroyerCoords[i]][destroyerCoords[i + 1]] = 'D';
	}
}

// Checks if the provided ship coordinates are valid for placement on the game board.
// Ensures that the ship occupies either a single row or a single column and that the cells are contiguous.
// Returns 1 if the placement is valid, 0 otherwise.
int checkPlacement(char board[][NUM_COLS], int coords[], int shipSize) {
	int rows_valid = 1, cols_valid = 1, count = 0;
	int row_check = coords[0];
	int col_check = coords[1];
	int row_coords[100] = { 0 };
	int col_coords[100] = { 0 };

	//Row checking
	for (int i = 0; i < shipSize * 2; i += 2) {
		row_coords[count] = coords[i];
		if (coords[i] != row_check) {
			rows_valid = 0;
		}
		count++;
	}

	//Column checking
	count = 0;
	for (int i = 1; i < shipSize * 2; i += 2) {
		col_coords[count] = coords[i];
		if (coords[i] != col_check) {
			cols_valid = 0;
		}
		count++;
	}

	if ((rows_valid && !cols_valid)) {
		//Check column values are in sequence by sorting
		bubbleSort(col_coords, shipSize);
		for (int i = 1; i < shipSize; i++) {
			if ((col_coords[i] > col_coords[i - 1] + 1) || board[row_coords[i]][col_coords[i]] != '~') {
				return 0;
			}
		}
		return 1;
	}
	else if ((!rows_valid && cols_valid)) {
		//Check row values are in sequence by sorting
		bubbleSort(row_coords, shipSize);
		for (int i = 1; i < shipSize; i++) {
			if ((row_coords[i] > row_coords[i - 1] + 1) || board[row_coords[i]][col_coords[i]] != '~') {
				return 0;
			}
		}
		return 1;
	}
	return 0;
}

// Function bubbleSort: Sorts an array of integers in ascending order using the bubble sort algorithm.
// - arr: The array of integers to be sorted.
// - n: The number of elements in the array.
void bubbleSort(int arr[], int n) {
	int i, j, temp;
	for (i = 0; i < n - 1; i++) {
		// Last i elements are already in place
		for (j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				// swap arr[j] and arr[j+1]
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

//Checks if a player has won the game by sinking all the opponent's ships.
// - board: The game board representing the opponent's ships.
// Returns: - 1 if the player has won (sunk all opponent's ships), 0 otherwise.
int isWinner(char board[][NUM_COLS]) {
	int hit_count = 0;
	for (int i = 0; i < NUM_ROWS; i++) {
		for (int j = 0; j < NUM_COLS; j++) {
			if (board[i][j] == '*') {
				hit_count++;
			}
		}
	}
	if (hit_count == 17) {
		return 1;
	}
	return 0;
}

//Checks if a shot hits a ship on the opponent's board.
// - board: The game board representing the opponent's ships.
// - xPos: The x-coordinate of the shot.
// - yPos: The y-coordinate of the shot.
// - token: A pointer to a character variable to store the symbol of the ship hit.
// - 1 if the shot hits a ship, 0 otherwise.

int checkShot(char board[][NUM_COLS], int xPos, int yPos, char* token) {
	for (int i = 0; i < NUM_ROWS; i++) {
		for (int j = 0; j < NUM_COLS; j++) {
			if (i == xPos && j == yPos) {
				if (board[i][j] != '~') {
					if (board[i][j] != 'M' || board[i][j] != '*') {
						*token = board[i][j];
					}
					return 1;
				}
			}
		}
	}
	return 0;
}

//Updates the game board based on the result of a shot.
// - board: The game board to be updated.
// - xPos: The x-coordinate of the shot.
// - yPos: The y-coordinate of the shot.
// - wasHit: Indicates whether the shot was a hit (1) or a miss (0).
void updateBoard(char board[][NUM_COLS], int xPos, int yPos, int wasHit) {
	char shipToken = '\0';
	for (int i = 0; i < NUM_ROWS; i++) {
		for (int j = 0; j < NUM_COLS; j++) {
			if (i == xPos && j == yPos) {
				if (wasHit) {
					board[i][j] = '*';
				}
				else {
					board[i][j] = 'M';
				}
			}

		}
	}
}

//Checks if a ship has been sunk based on the remaining tokens of that ship on the board.
// - board: The game board.
// - ship_token: The token representing the ship.
// Returns: 1 if the ship is sunk, 0 otherwise.
int checkIfSunkShip(char board[][NUM_COLS], char ship_token) {
	int token_count = 0;
	for (int i = 0; i < NUM_ROWS; i++) {
		for (int j = 0; j < NUM_COLS; j++) {
			if (board[i][j] == ship_token) {
				token_count++;
			}
		}
	}
	//Note that while the function theoretically checks if there are "no" tokens left on the board, it actually checks if there is 1 left, as this
	//function executes before the board actually updates.
	if (token_count == 1) {
		return 1;
	}
	return 0;
}

//Outputs the result of the current move to a specified output file.
// - outfile: The file pointer to the output file.
// - current_player: Integer representing the current player (0 for player, 1 for computer).
// - xPos: The x-coordinate of the attack.
// - yPos: The y-coordinate of the attack.
// - wasHit: Integer indicating if the attack was a hit (1 for hit, 0 for miss).
// - wasSunk: Integer indicating if the attacked ship was sunk (1 for sunk, 0 for not sunk).
void outputCurrentMove(FILE* outfile, int current_player, int xPos, int yPos, int wasHit, int wasSunk) {
	switch (current_player) {
	case 0: //Player
		if (wasHit) {
			if (wasSunk) {
				fprintf(outfile, "Player 1 attacked at %d, %d. It was a hit, and the enemy's ship sank!\n", xPos, yPos);
			}
			else {
				fprintf(outfile, "Player 1 attacked at %d, %d. It was a hit!\n", xPos, yPos);
			}
		}
		else {
			fprintf(outfile, "Player 1 attacked at %d, %d. It was a miss.\n", xPos, yPos);
		}
		break;
	case 1: //Computer
		if (wasHit) {
			if (wasSunk) {
				fprintf(outfile, "Computer attacked at %d, %d. It was a hit, and the player's ship sank!\n", xPos, yPos);
			}
			else {
				fprintf(outfile, "Computer attacked at %d, %d. It was a hit!\n", xPos, yPos);
			}
		}
		else {
			fprintf(outfile, "Computer attacked at %d, %d. It was a miss.\n", xPos, yPos);
		}
		break;
	}
}

//Outputs the statistics of both players to the specified output file.
// - outfile: The file pointer to the output file.
// - playerOne: Statistics of Player One.
// - playerTwo: Statistics of Player Two (Computer).

void outputStats(FILE* outfile, Stats playerOne, Stats playerTwo) {
	fprintf(outfile, "Player One Stats:\n");
	fprintf(outfile, "-----------------\n");
	fprintf(outfile, "Number of Hits: %d\n", playerOne.numHits);
	fprintf(outfile, "Number of Misses: %d\n", playerOne.numMisses);
	fprintf(outfile, "Total Number of Shots: %d\n", playerOne.totalShots);
	fprintf(outfile, "Hit/Miss Ratio: %.2lf%%\n", playerOne.hitsMisses);
	fprintf(outfile, "Computer Stats:\n");
	fprintf(outfile, "-----------------\n");
	fprintf(outfile, "Number of Hits: %d\n", playerTwo.numHits);
	fprintf(outfile, "Number of Misses: %d\n", playerTwo.numMisses);
	fprintf(outfile, "Total Number of Shots: %d\n", playerTwo.totalShots);
	fprintf(outfile, "Hit/Miss Ratio: %.2lf%%\n", playerTwo.hitsMisses);
}