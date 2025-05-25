/*****************************************************************
* Programmer: Zachary Marseglia
* Class: CptS 121, Spring 2024; Lab Section 4
* Programming Assignment: PA1
* Date: January 23,26, 2024
* Description:prompt the user for inputs to each equation and evaluate them based on the inputs.
*****************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#define PI 3.14159

int main(void) 
{
// request memory for
	int R1 = 0, R2 = 0, R3 = 0, shift = 0, series_resistance = 0, a = 0, x = 0, y = 0, z = 0;
	double total_sales_tax = 0, item_cost = 0, l = 0, w = 0, h = 0, volume_pyramid = 0, parallel_resistance = 0, R1p2 = 0, R2p2 = 0, R3p2 = 0, encoded_character = 0, distance = 0, x1 = 0, x2 = 0, y1 = 0,y2 =0, y3 = 0;
	char plaintext_character = ' ';
//*Had assiastanice from alex william he helped me with my problem of having my equations in a print stament so they werent running and moving my series resistance to int instead of double.

// Number 1 Total series resistance with the use of R1, R2, and R3 used d for decimal
	printf("Enter the values for R1, R2, and R3: ");
	scanf("%d%d%d", &R1, &R2, &R3);
	series_resistance = R1 + R2 + R3;
	printf("Total Series Resistance: %d\n", series_resistance);

// Number 2 Sales tax basically got the sales tax used lf 
	printf("Enter item cost and sales tax rate: ");
	scanf("%lf%lf", &total_sales_tax, &item_cost);
	total_sales_tax = total_sales_tax * item_cost;
	printf("Total Sales Tax: %lf\n", total_sales_tax);

// Number 3 Volume of a right rectangular pyrimaid using lf
	printf("Enter length, width, and height of the pyramid: ");
	scanf("%lf%lf%lf", &l, &w, &h);
	volume_pyramid = ((l * w * h) / 3);
	printf("Volume of Pyramid: %lf\n", volume_pyramid);
//Number 4 Total parallel resistance: need a double so used a diffrent name for R1-R3 so I also had to use lf
	printf("Enter values for R1, R2, and R3 (integers): ");
	scanf("%lf%lf%lf", &R1p2, &R2p2, &R3p2);
	parallel_resistance = (1 / (1 / R1p2 + 1 / R2p2 + 1 / R3p2));
	printf("Total Parallel Resistance: %lf\n", parallel_resistance);
//Number 5 Chacacter encoding:first time myself using the %c and it was difficult or some reason in my output I have to type the number twice also was causing errors untill i added a space in the scan "&c&d"
	printf("Enter plaintext character and shift value: ");
	scanf(" %c%d ", &plaintext_character, &shift);
	encoded_character = (plaintext_character - 'a') + 'A' - shift;
	printf("Encoded Character: %c%d\n", encoded_character);
//Number 6 Distancce between two points : used integers so I used d
	printf("Enter x1, y1, x2, y2 values: ");
	scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
	distance = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
	printf("Distance between the points is: %d\n", distance);
//Number 7 General equation  
	printf("Enter the values for x, y, z, and a: ");
	scanf("%d%d%d%d", &x, &y, &z, &a);
	y3 = (double)y / ((float)3 / (float)17) - z + x / (a % 2) + PI;
	printf("Results of general equation: %d\n", y3);
// A bunch of errors with the 2 y so I changed one of the names
	return 0;

}