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

void print_game_rules(void);
double get_bank_balance(void);
double get_wager_amount(void);
int check_wager_amount(double wager, double balance);
int roll_die(void);
int calculate_sum_dice(int die1_value, int die2_value);
int is_win_loss_or_point(int sum_dice);
int is_point_loss_or_neither(int sum_dice, int point_value);
double adjust_bank_balance(double bank_balance, double wager_amount, int add_or_subtract);
void chatter_messages(int number_rolls, int win_loss_neither, double initial_bank_balance, double current_bank_balance);
void chatter_messages(int number_rolls, int is_balance_increased, double initial_balance, double current_balance);

#pragma once
