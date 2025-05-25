/*****************************************************************
* Programmer: Zachary Marseglia
* Class: CptS 121, Spring 2024; lab section 4
* Programming Assignment: PA5
* March 18, 2024
* Description:This program is the game Yahtzee, a dice game where
* the player can score in various combinations. The player rolls dice,
* chooses scoring categories, and attempts to maximize their score.
*****************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

#ifndef YAHTZEE_H
#define YAHTZEE_H


void printGameMenu();
void printRules();
void startGame();
void rollDice(int dice[]);
void displayDice(int dice[]);
void selectCombination(int dice[]);
int calculateScore(int combination, int dice[]);
int validateCombination(int combination, int dice[]);
void printScores(int player1Score, int player2Score);
void printWinner(int player1Score, int player2Score);
int rollSingleDie();
void rerollDice(int dice[]);
int askForReroll();
int askForReroll();
#endif
#pragma once

