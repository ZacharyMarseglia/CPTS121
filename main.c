#include <stdio.h>
#include <stdbool.h>
#include "Header.h"

int main() {
    char dest[20] = "Hello, ";
    const char* src = "world!";
    int num_chars = 5; // Copy at most 5 characters

    printf("Before concatenation: %s\n", dest);
    my_str_n_cat(dest, src, num_chars);
    printf("After concatenation: %s\n", dest);

    int list[] = { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 };
    int h = sizeof(list) / sizeof(list[0]);
    int target = 13;
    int target_index;

    if (binary_search(list, h, target, &target_index)) {
        printf("Target value %d found at index %d\n", target, target_index);
    }
    else {
        printf("Target value %d not found in the list\n", target);
    }

    char* strings[] = { "banana", "apple", "orange", "grape", "kiwi" };
    int z = sizeof(strings) / sizeof(strings[0]);

    printf("Before sorting:\n");
    for (int i = 0; i < z; i++) {
        printf("%s\n", strings[i]);
    }

    bubble_sort(strings, z);

    printf("\nAfter sorting:\n");
    for (int i = 0; i < z; i++) {
        printf("%s\n", strings[i]);
    }

    const char* str1 = "race car";
    const char* str2 = "A man, a plan, a canal, Panama!";

    printf("\"%s\" is a palindrome: %s\n", str1, is_palindrome(str1, 8) ? "true" : "false");
    printf("\"%s\" is a palindrome: %s\n", str2, is_palindrome(str2, 31) ? "true" : "false");

    
    printf("The sum of the primes up to 41 is %d\n", sum_primes(41));

    const char* str = "test string";
    Occurrences occurrences[128]; // Declare the occurrences array
    int max_occurrences;
    char max_char;

    maximum_occurrences(str, occurrences, &max_occurrences, &max_char);

    printf("Maximum occurrences: %d\n", max_occurrences);
    printf("Corresponding character: %c\n", max_char);


    return 0;
}
