#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Header.h"
#include <stdbool.h>

//Question 1
char* my_str_n_cat(char* dest, const char* src, int n) {
    char* original_dest = dest; // Store the original destination pointer

    // Move the destination pointer to the end of the destination string
    while (*dest != '\0') {
        dest++;
    }

    // Copy at most n characters from the source string to the destination string
    while (*src != '\0' && n > 0) {
        *dest = *src;
        dest++;
        src++;
        n--;
    }

    // Add null terminator to the end of the concatenated string
    *dest = '\0';

    return original_dest; // Return the original destination pointer
}

//Question 2
bool binary_search(int list[], int h, int target, int* target_index) {
    int left = 0;
    int right = h - 1;
    bool found = false;
    *target_index = -1; // Initialize target_index to -1

    while (!found && left <= right) {
        int mid = (left + right) / 2; // Calculate the midpoint

        if (list[mid] == target) {
            found = true;
            *target_index = mid;
        }
        else if (target < list[mid]) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }

    return found;
}

//Question 3
void bubble_sort(char* arr[], int z) {
    int U = z - 1; // Marker for the unsorted section
    while (U > 0) {
        int C = 1; // Marker for the current element
        while (C <= U) {
            if (strcmp(arr[C], arr[C - 1]) < 0) {
                // Swap pointers if the current element is less than the one to its left
                char* temp = arr[C];
                arr[C] = arr[C - 1];
                arr[C - 1] = temp;
            }
            C++;
        }
        U--; // Move the unsorted section marker to the left
    }
}
//question 3
int is_alphanumeric(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9');
}
//question 3
int tolower(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return ch + 32;
    }
    return ch;
}
//question 4
int is_palindrome_recursive(const char* str, int start, int end) {
    while (start < end) {
        while (!is_alphanumeric(str[start]) && start < end) {
            start++;
        }
        while (!is_alphanumeric(str[end]) && end > start) {
            end--;
        }
        if (tolower(str[start]) != tolower(str[end])) {
            return 0;
        }
        start++;
        end--;
    }
    return 1;
}

//question 4
int is_palindrome(const char* str, int length) {
    return is_palindrome_recursive(str, 0, length - 1);
}

//question 5
int is_prime(int num)
{
    if (num <= 1) return 0;
    if (num % 2 == 0 && num > 2) return 0;
    for (int i = 3; i < num / 2; i += 2)
    {
        if (num % i == 0)
            return 0;
    }
    return 1;
}
//question 5
//Function that recursively calculates the sum of all the primes up to a number
int sum_primes(unsigned int n)
{
    int sum = 0;
    if (n < 2)
    {
        return 0;
    }

    if (is_prime(n)) //I could put the "prime" logic here, but I thought this would be more readable
    {
        //printf("Prime: %d\n", n);
        sum = n;
    }
    else
    {
        sum = 0;
    }

    return sum + sum_primes(n - 1);


}

//question 6

void maximum_occurrences(const char* str, Occurrences* occurrences, int* max_occurrences, char* max_char) {
    // Initialize occurrences array
    for (int i = 0; i < 128; ++i) { // Assuming ASCII characters
        occurrences[i].num_occurrences = 0;
        occurrences[i].frequency = 0.0;
    }

    // Count occurrences of each character
    int total_characters = 0;
    for (const char* p = str; *p != '\0'; ++p) {
        if ((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z') || (*p >= '0' && *p <= '9')) {
            occurrences[(int)*p].num_occurrences++;
            total_characters++;
        }
    }

    // Calculate frequencies and find maximum occurrences and corresponding character
    *max_occurrences = 0;
    *max_char = '\0';
    for (int i = 0; i < 128; ++i) {
        if (occurrences[i].num_occurrences > 0) {
            occurrences[i].frequency = (double)occurrences[i].num_occurrences / total_characters;
            if (occurrences[i].num_occurrences > *max_occurrences) {
                *max_occurrences = occurrences[i].num_occurrences;
                *max_char = (char)i;
            }
        }
    }
}


