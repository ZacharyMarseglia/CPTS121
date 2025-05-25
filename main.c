/*****************************************************************
* Programmer: Zachary Marseglia
* Class: CptS 121, Spring 2024; lab section 4
* Programming Assignment: PA5
* March 18, 2024
* Description:This program is the game Yahtzee, a dice game where
* the player can score in various combinations. The player rolls dice,
* chooses scoring categories, and attempts to maximize their score.
*****************************************************************/
#include "header.h"

int main() {
    int option;
    do {
        // Display the game menu and prompt the user for input
        printGameMenu();
        scanf("%d", &option);
        // Process the user's choice using a switch statement
        switch (option) {
        case 1:// Print game rules
            printRules();
            break;
        case 2:// Start a game of Yahtzee
            startGame();
            break;
        case 3:// Exit the program
            printf("Goodbye! Thanks for playing Yahtzee.\n");
            break;
        default:
            printf("Invalid option. Please try again.\n");
        }
    } while (option != 3);// Continue looping until the user chooses to exit

    return 0;
}