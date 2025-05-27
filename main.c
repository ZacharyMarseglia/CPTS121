#include "Header.h"

int main(void) {
	srand((unsigned int)time(NULL));


	// Declarations and initialization of variables for the Battleship game:
	char playerOneBoard[NUM_ROWS][NUM_COLS] = { {'\0'} },
		playerTwoBoard[NUM_ROWS][NUM_COLS] = { { '\0'} },
		pTwoShownBoard[NUM_ROWS][NUM_COLS] = { { '\0' } },
		shipSymbols[5] = { 'C', 'B', 'S', 'R', 'D' };
	int computerHasTried[NUM_ROWS][NUM_COLS] = { { 0 } };
	int ship_lengths[5] = { CARRIER_LENGTH, BATTLESHIP_LENGTH, SUBMARINE_LENGTH, CRUISER_LENGTH, DESTROYER_LENGTH };
	int direction = HORIZONTAL, row_start = 0, col_start = 0;
	int intIn = 0, xPos = 0, yPos = 0, wasHit = 0, wasSunk = 0, generating = 1;
	bool placing = false, hasWon = false, hasLost = false;
	char shipHit = '\0';
	Stats playerOne = { 0, 0, 0, 0.0 };
	Stats playerTwo = { 0, 0, 0, 0.0 };
	FILE* outfile = NULL;
	outfile = fopen("Battleshiplog.txt", "w");



	// Initialize boards and display game rules
	initializeBoard(playerOneBoard, NUM_ROWS, NUM_COLS);
	initializeBoard(playerTwoBoard, NUM_ROWS, NUM_COLS);
	initializeBoard(pTwoShownBoard, NUM_ROWS, NUM_COLS);

	printf("THE GAME BATTLE SHIP \n");
	printf("RULES \n");
	printf("1. This is a multiplayer, two player game.\n");
	printf("2. Player 1 is you, Player 2 is the computer.\n");
	printf("3. You and your opponent have five ships each: a carrier, battleship, submarine,\n");
	printf("   cruiser, and destroyer. Your objective is to guess your enemy's ships' coordinates.\n");
	printf("   If you manage to 'sink' (destroy all of your enemy's ships), you win!\n");
	printf("Press enter to start the game!\n");
	getch();

	//Manual or random placement
	printf("Would you like to manually place your ships, or randomly generate a board?\n");
	printf("1. Randomly generate board.\n");
	printf("2. Manually place ships.\n");
	do {
		scanf("%d", &intIn);
	} while (!(intIn == 1 || intIn == 2));
	if (intIn == 1) {
		for (int i = 0; i < 5; i++) {
			//Random placement of ships for player (Player 1)
			placing = true;
			direction = generateDirection();
			do {
				generateStartingPoint(direction, ship_lengths[i], &row_start, &col_start);
				if (detectCollision(playerOneBoard, direction, ship_lengths[i], row_start, col_start) == 1) {
					placeShip(playerOneBoard, NUM_ROWS, NUM_COLS, ship_lengths[i], shipSymbols[i], direction, row_start, col_start);
					placing = false;
				}
			} while (placing);
		}
	}
	else {
		manuallyPlaceShips(playerOneBoard);
	}
	printf("YOUR BOARD:\n");
	printBoard(playerOneBoard, NUM_ROWS, NUM_COLS);

	// Random placement of ships for computer (Player 2)
	for (int i = 0; i < 5; i++) {
		placing = true;
		direction = generateDirection();
		do {
			generateStartingPoint(direction, ship_lengths[i], &row_start, &col_start);
			if (detectCollision(playerTwoBoard, direction, ship_lengths[i], row_start, col_start) == true) {
				placeShip(playerTwoBoard, NUM_ROWS, NUM_COLS, ship_lengths[i], shipSymbols[i], direction, row_start, col_start);
				placing = false;
			}
		} while (placing);
	}

	// Randomly select who starts first
	int current_player = selectWhoStartsFirst();
	if (current_player == 0) { //Player
		printf("Player 1 has been randomly selected to go first.\n");
	}
	else if (current_player == 1) { //Computer
		printf("Player 2 (computer) has been randomly selected to go first.\n");
	}
	
	//Initialize computer parallel array
	for (int i = 0; i < NUM_ROWS; i++) {
		for (int j = 0; j < NUM_COLS; j++) {
			computerHasTried[i][j] = 0;
		}
	}
	// Game loop
	while (!hasWon || !hasLost) {
		switch (current_player) {
		case 0: //Player
			printf("Your Board:\n");
			printBoard(playerOneBoard, NUM_ROWS, NUM_COLS);
			printf("\nComputer's Board:\n");
			printBoard(pTwoShownBoard, NUM_ROWS, NUM_COLS);
			printf("Enter a target: ");
			scanf("%d %d", &xPos, &yPos);
			playerOne.totalShots++;
			wasHit = checkShot(playerTwoBoard, xPos, yPos, &shipHit);
			wasSunk = checkIfSunkShip(playerTwoBoard, shipHit);
			updateBoard(playerTwoBoard, xPos, yPos, wasHit);
			updateBoard(pTwoShownBoard, xPos, yPos, wasHit);
			if (wasHit) {
				playerOne.numHits++;
				printf("Hit!\n");
				if (wasSunk) {
					printf("You sunk the computer's ship %c!\n", shipHit);
				}
			}
			else {
				playerOne.numMisses++;
				printf("Miss...\n");
			}
			// Output move to file
			outputCurrentMove(outfile, current_player, xPos, yPos, wasHit, wasSunk);
			// Check if player has won
			if (isWinner(playerTwoBoard)) {
				printf("You won!\n");
				hasWon = 1;
				goto breakout;
			}
			current_player = 1;
			break;
		case 1: //Computer
			generating = 1;
			while (generating) {
				xPos = rand() % 10;
				yPos = rand() % 10;
				if (computerHasTried[xPos][yPos] != 1) {
					computerHasTried[xPos][yPos] = 1;
					generating = 0;
				}
			}
			playerTwo.totalShots++;
			wasHit = checkShot(playerOneBoard, xPos, yPos, &shipHit);
			wasSunk = checkIfSunkShip(playerOneBoard, shipHit);
			if (wasHit) {
				playerTwo.numHits++;
				printf("Computer selects %d, %d. It was a hit!\n", xPos, yPos);
				if (wasSunk) {
					printf("Computer selects %d, %d. It was a hit and sunk your ship!\n", xPos, yPos);
				}
			}
			else {
				playerTwo.numMisses++;
				printf("Computer selects %d, %d. It was a miss.\n", xPos, yPos);
			}
			
			updateBoard(playerOneBoard, xPos, yPos, wasHit);
			if (isWinner(playerOneBoard)) {
				printf("You lost!\n");
				hasLost = 1;
				goto breakout;
			}
			outputCurrentMove(outfile, current_player, xPos, yPos, wasHit, wasSunk);
			current_player = 0;
			break;
		}
	}

breakout:
	printf("Printing statistics to battleship.log...\n");
	playerOne.hitsMisses = ((double)playerOne.numHits / playerOne.totalShots) * 100;
	playerTwo.hitsMisses = ((double)playerTwo.numHits / playerTwo.totalShots) * 100;
	outputStats(outfile, playerOne, playerTwo);
	fclose(outfile);

	return 0; //End of main function
}