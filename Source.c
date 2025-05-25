/*****************************************************************
* Programmer: Zachary Marseglia
* Class: CptS 121, Spring 2024; Lab Section 4
* Programming Assignment: PA2
* Date: January 31, 2024
* Description:The functions implemented cover a range of 
applications, including electrical circuit calculations 
(series and parallel resistances), geometric computations 
(volume of a pyramid, distance between two points), financial 
calculations (sales tax), character encoding, and a general mathematical equation.
*****************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include "Header.h"

//calculates series resistance 
int calculate_series_resistance(int R1, int R2, int R3)
{

	return R1 + R2 + R3;

}
// calculates total sales tax
double calculate_total_sales_tax(double sales_tax_rate, double item_cost)
{

	return sales_tax_rate * item_cost;

}
// claculate volume of a pyramid
double calculate_volume_pyramid(double l, double w, double h)
{

	return (l * w * h) / 3;

}
//calculates the parallel resistance
double calculate_parallel_resistance(int R1, int R2, int R3)
{

	return 1 / ((1 / R1) + (1 / R2) + (1 / R3));

}
// calculates character encodings 
char calculate_character_encoding(char plaintext_character, int shift)
{

	return (char)((plaintext_character - 'a') + 'A' - shift);

}
// calculates the distance between points 
double calculate_distance_between_points(double x1, double y1, double x2, double y2)
{

	return sqrt(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)));

}
// does the general equation 
double evaluate_general_equation(double x, double y, double z, int a)
{

	return y / ((double)3 / 17) - z + x / (a % 2) + PI;

}