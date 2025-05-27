#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int num_occurrences;
    double frequency;
} Occurrences;

char* my_str_n_cat(char* dest, const char* src, int n);
bool binary_search(int list[], int n, int target, int* target_index);
void bubble_sort(char* arr[], int z);
int tolower(char ch);
int is_palindrome_recursive(const char* str, int start, int end);
int is_palindrome(const char* str, int length);
int sum_primes(unsigned int n);
void maximum_occurrences(const char* str, Occurrences* occurrences, int* max_occurrences, char* max_char);
void max_consecutive_integers(int** array, int rows, int columns, int** start_ptr, int* max_count_ptr);
#pragma once
