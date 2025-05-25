/*****************************************************************
* Programmer: Zachary Marseglia
* Class: CptS 121, Spring 2024; lab section 4
* Programming Assignment: PA4
* February 23, 2024
* Description:This program is the game craps a simple gambling game with dice rolls
*   where the player can place wagers and attempt to win or lose money.
*****************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include "Header.h"

int main() {

    srand(time(NULL));
    // Seed the random number generator


    print_game_rules();
    // Display the game rules

    double initial_balance = get_bank_balance();
    double current_balance = initial_balance;
    int number_rolls = 0;
    double new_point_value = 0;
    int loop = 0;
    double wager = 0;
    // Initialize variables for player's balance, rolls, point value, loop control, and wager

    // Main game loop - continues as long as the player has a positive balance
    while (current_balance > 0) 
    {
        do {
            wager = get_wager_amount();
            if (!(loop = check_wager_amount(wager, current_balance))) {
                printf("Invalid wager. Please try again.\n");
            }
        }// Get a valid wager from the player
        while (!loop);


        int die1 = roll_die();
        int die2 = roll_die();
        int sum_dice = calculate_sum_dice(die1, die2);
        // Roll two dice and calculate their sum

        printf("You have a %d roll.\n", sum_dice);
        // Display the result of the dice roll

        if (number_rolls == 0) 
        {// Check the result based on the number of rolls

            
            int result = is_win_loss_or_point(sum_dice);
            // First roll - determine if it's a win, loss, or point
            if (result == 1) 
            {
                printf("Congratulations! You won on the first roll! Lucky is here bet big!\n");
                current_balance = adjust_bank_balance(current_balance, wager, 1);
                // Player won on the first roll

            }
            else if (result == 0) 
            {
                printf("Sorry, you lost on the first roll. Remeber you can only lose 100 percent of the money you gamble, but you could potentially win 100 Times your money!\n");
                current_balance = adjust_bank_balance(current_balance, wager, 0);
               
            }
            else 
            {
                new_point_value = sum_dice;
            }// Player established a point value
            printf("Your current balance is: %.2lf \n", current_balance);
        }
        else {
            // Subsequent rolls - check if the player made the point or rolled a 7
            int result = is_point_loss_or_neither(sum_dice, new_point_value);

            if (result == 1) {
                printf("Congratulations! You made your roll and won!\n");
            }// Player made the point and won
            else if (result == 0) {
                // Player lost by rolling a 7
                printf("Sorry, you lost. You rolled a 7\n");
            }
            // Adjust the player's balance based on the result
            current_balance = adjust_bank_balance(current_balance, wager, result);
            printf("Your current balance is: %.2lf \n", current_balance);

        }
        // Display chatter messages based on the game state
        chatter_messages(number_rolls, current_balance > initial_balance, initial_balance, current_balance);

        // Increment the number of rolls for each iteration
        number_rolls++;

    } 


    // Display game over message when the player is out of money
    printf("Game over! You are out of money.\n");

    return 0;
}