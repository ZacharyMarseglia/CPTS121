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
#include "Header.h"

int main()
{
	//Get the values of R and assign them
	int R1, R2, R3;
	printf("Enter values for R1, R2, and R3 (separated by spaces): ");
	scanf("%d %d %d", &R1, &R2, &R3);

	//The code calculates the total series resistance of resistors (R1, R2, R3) using the calculate_series_resistance function and prints the result in the  thousandths place
	int series_resistance = calculate_series_resistance(R1, R2, R3);
	printf("Total Series Resistance: %.3f\n", (float)series_resistance);

	//prompts the user to input values for sales tax rate and item cost then stores them as floating points
	double sales_tax_rate, item_cost;
	printf("Enter sales tax rate and item cost (separated by spaces): ");
	scanf("%lf %lf", &sales_tax_rate, &item_cost);
	//calculates the total sales tax and then prints the results in the thousandths place
	double total_sales_tax = calculate_total_sales_tax(sales_tax_rate, item_cost);
	printf("Total Sales Tax: %.3f\n", total_sales_tax);
	//prompts user to input length width hight and stores them as floating point
	double l, w, h;
	printf("Enter length, width, and height of the pyramid base (separated by spaces): ");
	scanf("%lf %lf %lf", &l, &w, &h);
	//assigns the volume to the unction then prints
	double volume_pyramid = calculate_volume_pyramid(l, w, h);
	printf("Volume of the Pyrimid is: %.3f\n", volume_pyramid);
    //prompts the user for more R values then stores them as integers 
	printf("Enter values for R1, R2, and R3 for parallel resistance (separated by spaces): ");
	scanf("%d %d %d", &R1, &R2, &R3);
	//assigns the parrrel resistance to the function then prints the results in the thousands  
	double parallel_resistance = calculate_parallel_resistance(R1, R2, R3);
	printf("Total Parallel Resistance: %.3f\n", parallel_resistance);
	//prompts the users to input a plain character text and a shift value the stores them as a character and an integer 
	char plaintext_character;
	int shift;
	printf("Enter plaintext character and shift value (separated by a space): ");
	scanf(" %c %d", &plaintext_character, &shift);
	// assigns encoded character to the functionn calculate character encoding and then prints the results
	char encoded_character = calculate_character_encoding(plaintext_character, shift);
	printf("Encoded Character: %c\n", encoded_character);
	//prompts the user for inputs of cordinates then stores them as floating points
	double x1, y1, x2, y2;
	printf("Enter coordinates (x1 y1 x2 y2) for two points (separated by spaces): ");
	scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
	// assigns distance to the calculate distance between points function and then prints the results in the thousandths place
	double distance = calculate_distance_between_points(x1, y1, x2, y2);
	printf("Distance between two points: %.3f\n", distance);
	//prompts the user for input values x, y, and z then stores them a floating points
	double x, y, z;
	printf("Enter values for x, y, and z in the general equation (separated by spaces): ");
	scanf("%lf %lf %lf", &x, &y, &z);
	//assigns result to the evaluate general equation function the prints it in the thousandths place
	double result = evaluate_general_equation(x, y, z, 10);
	printf("result of the General eqation: %.3f\n", result);
	// return
	return 0;
}