/*****************************************************************
* Programmer: Zachary Marseglia
* Class: CptS 121, Spring 2024; lab section 4
* Programming Assignment: PA5
* March 18, 2024
* Description:This program is the game Yahtzee, a dice game where
* the player can score in various combinations. The player rolls dice,
* chooses scoring categories, and attempts to maximize their score.
*****************************************************************/
          
#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Prints the main menu of the game.
void printGameMenu() {
    printf("===== YAHTZEE MENU =====\n");
    printf("1. Print game rules\n");
    printf("2. Start a game of Yahtzee\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
}

// Displays the rules of Yahtzee.
void printRules() {
    printf("\n===== YAHTZEE RULES =====\n");
    printf("The scorecard used for Yahtzee is composed of two sections. A upper section and a lower section.A total of thirteen boxes or thirteen scoring combinations are divided amongst the sections.The upper section consists of boxes that are scored by summing the value of the dice matching the faces of the box.If a player rolls four 3s, then the score placed in the 3s box is the sum of the dice which is 12. Once a player has chosen to score a box, it may not be changed and the combination is no longer in play for future rounds.If the sum of the scores in the upper section is greater than or equal to 63, then 35 more points are added to the players overall score as a bonus. The lower section contains a number of poker like combinations.See the table provided below : \n");
}
// Initializes player scores to 0.
void initializeScores(int* player1Score, int* player2Score) {
    *player1Score = 0;
    *player2Score = 0;
}

// Starts a game of Yahtzee, handling the turn-based gameplay.
void startGame() {
    int player1Score = 0, player2Score = 0;
    int round = 1;
    int dice[5];

    initializeScores(&player1Score, &player2Score);
    // The game consists of 13 rounds, corresponding to the 13 scoring categories.
    while (round <= 13) {
        printf("Round %d\n", round);
        printf("Player 1's turn:\n");
        rollDice(dice);
        selectCombination(dice, &player1Score);
        printScores(player1Score, player2Score);

        printf("Round %d\n", round);
        printf("Player 2's turn:\n");
        rollDice(dice);
        selectCombination(dice, &player2Score);
        printScores(player1Score, player2Score);

        round++;
    }

    // Calculate upper section bonus
    if (player1Score >= 63)
        player1Score += 35;
    if (player2Score >= 63)
        player2Score += 35;

    // Print final scores and winner
    printScores(player1Score, player2Score);
    printWinner(player1Score, player2Score);
}
// Rolls 5 dice, each die having a value between 1 and 6.
void rollDice(int dice[]) {
    srand(time(NULL));
    for (int i = 0; i < 5; i++) {
        dice[i] = rand() % 6 + 1;
    }
}
// Displays the values of the rolled dice.
void displayDice(int dice[]) {
    for (int i = 0; i < 5; i++) {
        printf("\nDie %d: %d\n", i + 1, dice[i]);
    }
}
// Handles the logic for rerolling dice and selecting scoring combinations.
void selectCombination(int dice[], int* playerScore) {
    int rolls = 0;
    char choice;

    printf("Hit any key to roll the dice...\n");
    getch(); // Initial roll
    rollDice(dice);
    displayDice(dice);

    while (rolls < 2) { // Allows up to 2 rerolls
        printf("Do you want to reroll certain dice? (Y/N): ");
        scanf(" %c", &choice);
        if (choice == 'Y' || choice == 'y') {
            rerollDice(dice);
            displayDice(dice);
            rolls++;
        }
        else {
            break; // Exit the loop if the user does not want to reroll
        }
    }

        printf("\nSelect a combination for scoring:\n");
        printf("1. Sum of 1's\n");
        printf("2. Sum of 2's\n");
        printf("3. Sum of 3's\n");
        printf("4. Sum of 4's\n");
        printf("5. Sum of 5's\n");
        printf("6. Sum of 6's\n");
        printf("7. Three-of-a-kind\n");
        printf("8. Four-of-a-kind\n");
        printf("9. Full house\n");
        printf("10. Small straight\n");
        printf("11. Large straight\n");
        printf("12. Yahtzee\n");
        printf("13. Chance\n");

        int combination;
        printf("\nEnter your choice: ");
        scanf("%d", &combination);

        // Call the calculateScore function passing the combination and dice array
        int score = calculateScore(combination, dice);
        printf("Score for combination %d: %d\n", combination, score);
        *playerScore += score; // Update player's score

    }
// Asks the user if they want to reroll certain dice.
int askForReroll() {
    char choice;
    printf("Do you want to reroll certain dice? (Y/N): ");
    scanf(" %c", &choice);
    return (choice == 'Y' || choice == 'y');
}
// Handles the rerolling of specific dice chosen by the player.
void rerollDice(int dice[]) {
    int number = 0;
    int die_reroll = 0;

        // Prompt the user for the number of dice to reroll
        do {
            printf("How many dice would you like to reroll? Or, enter 0 to use this roll. ");
            scanf("%d", &number);
        } while (number < 0 || number > 5);

        // Reroll the selected dice
        if (number != 0) {
            printf("Enter the number(s) of the die you would like to reroll (1-5), separated by spaces: ");
            for (int reroll_index = 0; reroll_index < number; reroll_index++) {
                scanf("%d", &die_reroll);
                // Reroll the selected die
                dice[die_reroll - 1] = rollSingleDie();
            }
            // Exit the function if dice are rerolled
            return;
        }
    }

// Rolls a single die.
int rollSingleDie() {
    return rand() % 6 + 1;
}

// Calculates and returns the score for the selected combination.
int calculateScore(int combination, int dice[]) {
    int score = 0;
    int counts[6] = { 0 }; // Array to count occurrences of each dice value

    // Count occurrences of each dice value
    for (int i = 0; i < 5; i++) {
        counts[dice[i] - 1]++;
    }

    switch (combination) {
    case 1: // Sum of 1's
    case 2: // Sum of 2's
    case 3: // Sum of 3's
    case 4: // Sum of 4's
    case 5: // Sum of 5's
    case 6: // Sum of 6's
        score = counts[combination - 1] * combination;
        break;
    case 7: // Three-Of-A-Kind
        for (int i = 0; i < 6; i++) {
            if (counts[i] >= 3) {
                for (int j = 0; j < 5; j++) score += dice[j];
                break;
            }
        }
        break;
    case 8: // Four-Of-A-Kind
        for (int i = 0; i < 6; i++) {
            if (counts[i] >= 4) {
                for (int j = 0; j < 5; j++) score += dice[j];
                break;
            }
        }
        break;
    case 9: { // Full House
        int threeFound = 0, twoFound = 0;
        for (int i = 0; i < 6; i++) {
            if (counts[i] == 3) threeFound = 1;
            if (counts[i] == 2) twoFound = 1;
        }
        if (threeFound && twoFound) score = 25;
        break;
    }
    case 10: // Small Straight
        if ((counts[0] && counts[1] && counts[2] && counts[3]) ||
            (counts[1] && counts[2] && counts[3] && counts[4]) ||
            (counts[2] && counts[3] && counts[4] && counts[5])) {
            score = 30;
        }
        break;
    case 11: // Large Straight
        if ((counts[0] && counts[1] && counts[2] && counts[3] && counts[4]) ||
            (counts[1] && counts[2] && counts[3] && counts[4] && counts[5])) {
            score = 40;
        }
        break;
    case 12: // YAHTZEE (Five-Of-A-Kind)
        for (int i = 0; i < 6; i++) {
            if (counts[i] == 5) {
                score = 50;
                break;
            }
        }
        break;
    case 13: // Chance
        for (int i = 0; i < 5; i++) score += dice[i];
        break;
    default:
        printf("Invalid combination selected.\n");
        break;
    }

    return score;
}
// Validates the chosen combination based on the current dice roll.
int validateCombination(int combination, int dice[]) {
    switch (combination) {
    case 1: // Sum of 1's
        for (int i = 0; i < 5; i++) {
            if (dice[i] == 1) {
                return 1;
            }
        }
        return 0;
        break;

    case 2: // Sum of 2's
        for (int i = 0; i < 5; i++) {
            if (dice[i] == 2) {
                return 1;
            }
        }
        return 0;
        break;

        // Implement cases for other combinations
    }
}
// Prints the current scores of both players.
void printScores(int player1Score, int player2Score) {
    printf("Player 1 Score: %d\n", player1Score);
    printf("Player 2 Score: %d\n", player2Score);
}
// Determines and prints the winner based on final scores.
void printWinner(int player1Score, int player2Score) {
    if (player1Score > player2Score)
        printf("Player 1 wins!\n");
    else if (player2Score > player1Score)
        printf("Player 2 wins!\n");
    else
        printf("It's a tie!\n");
}
