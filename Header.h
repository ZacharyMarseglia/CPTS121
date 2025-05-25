/*****************************************************************
* Programmer: Zachary Marseglia
* Class: CptS 121, Spring 2024; lab section 4
* Programming Assignment: PA2
* January 31, 2024
* Description:The functions implemented cover a range of
applications, including electrical circuit calculations
(series and parallel resistances), geometric computations
(volume of a pyramid, distance between two points), financial
calculations (sales tax), character encoding, and a general mathematical equation.
*****************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#define PI 3.14159265
//function prototypes for the main and source files 

int calculate_series_resistance(int R1, int R2, int R3);
double calculate_total_sales_tax(double sales_tax_rate, double item_cost);
double calculate_volume_pyramid(double l, double w, double h);
double calculate_parallel_resistance(int R1, int R2, int R3);
char calculate_character_encoding(char plaintext_character, int shift);
double calculate_distance_between_points(double x1, double y1, double x2, double y2);
double evaluate_general_equation(double x, double y, double z, int a);

