/*****************************************************************
* Programmer: Zachary Marseglia
* Class: CptS 121, Spring 2024; lab section 4
* Programming Assignment: PA4
* February 23, 2024
* Description:
*****************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include "Header.h"

// Function to print the game rules

void print_game_rules(void) 
{

    printf("A player rolls two dice. Each die has six faces. These faces contain 1, 2, 3, 4, 5, and 6 spots. After the dice have come to rest, the sum of the spots on the two upward faces is calculated.If the sum is 7 or 11 on the first throw, the player wins.If the sum is 2, 3, or 12 on the first throw (called craps), the player loses(i.e.the house wins).If the sum is 4, 5, 6, 8, 9, or 10 on the first throw, then the sum becomes the player's point. To win, you must continue rolling the dice until you make your point. The player loses by rolling a 7 before making the point.\n");
    printf("\n");
}
// Function to get the initial bank balance from the player

double get_bank_balance(void) 
{
    double balance;
    printf("Enter your initial bank balance: $");
    scanf("%lf", &balance);
    return balance;
}
// Function to get the wager amount from the player

double get_wager_amount(void)
{

    double wager;
    printf("Enter your wager: $");
    scanf("%lf", &wager);
    return wager;
}
// Function to check if the wager amount is valid

int check_wager_amount(double wager, double balance) {
    
    if (wager <= 0)
    {
        printf("Wager must be greater than 0. Please try again.\n");
        return 0;
    }

    if (wager > balance) 
    {
        printf("Wager exceeds your available balance. Please try again.\n");
        return 0; 
    }

    return 1; 
}

// Function to simulate the roll of a die
int roll_die(void)
{
        return rand() % 6 + 1;
}

int calculate_sum_dice(int die1_value, int die2_value) 
{
    return die1_value + die2_value;
}


// Function to calculate the sum of two dice values
int is_win_loss_or_point(int sum_dice)
{
  
    if (sum_dice == 7 || sum_dice == 11)
    {
        return 1;//win
    }
    if (sum_dice == 2 || sum_dice == 3 || sum_dice == 12)
    {
        return 0; // Loss
    }
    else
    {
        return -1; // point
    }
}

// Function to determine if the player wins, loses, or establishes a point
int is_point_loss_or_neither(int sum_dice, int point_value)
{
    
    if (sum_dice == point_value) 
    {
        return 1;// made point and won
    }
    if (sum_dice == 7) 
    {
        return 0;// lost by rolling 7
    }
    else 
    {
        printf("No change/Tie \n");// Tie
        return -1;
    }
}

// Function to determine if the player makes the point, loses, or neither
double adjust_bank_balance(double bank_balance, double wager_amount, int add_or_subtract)
{
    if (add_or_subtract == 1) 
    {
        return bank_balance + wager_amount; // Add
    }
    if (add_or_subtract == 0) 
    {
        return bank_balance - wager_amount;//Subtract
    }
    else {
        return bank_balance;// No change 
    }
}
// Function to adjust the bank balance based on the result of the game
void display_updated_balance(double current_balance)
{
    printf("Updated Balance: $%.2f\n", current_balance);
}
// Function to display the updated bank balance
void chatter_messages(int number_rolls, int is_balance_increased, double initial_balance, double current_balance)
{
    printf("Chatter Messages:\n");

    if (number_rolls > 0) {
        printf("Number of Rolls: %d\n", number_rolls);

        if (is_balance_increased) {
            printf("Congratulations! Your balance increased from %.2lf to %.2lf\n", initial_balance, current_balance);
        }
        else {
            printf("Sorry, your balance decreased from %.2lf to %.2lf\n", initial_balance, current_balance);
        }
    }
    else {
        printf("No rolls yet.\n");
    }

    printf("\n");
}