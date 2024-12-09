#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "../src/guess.h"

#if _WIN32
#  define C_RED(s)     s
#  define C_GREEN(s)   s
#else
#  define C_RED(s)     "\033[31;1m" s "\033[0m"
#  define C_GREEN(s)   "\033[32;1m" s "\033[0m"
#endif

#define TEST(s, x)                              \
    do {                                        \
        if (x) {                                \
            printf(C_GREEN("PASS") " %s\n", s); \
            count_pass++;                       \
        } else {                                \
            printf(C_RED("FAIL") " %s\n", s);   \
            count_fail++;                       \
        }                                       \
    } while (0)

int main() {
    int count_pass = 0, count_fail = 0;

    TEST("Int to roman 1", !strcmp(number_to_roman(2), "II"));
    TEST("Int to roman 2", !strcmp(number_to_roman(42), "XLII"));
    TEST("Int to roman 3", !strcmp(number_to_roman(77), "LXXVII"));
    TEST("Roman to int 1", roman_to_number("XXV") == 25);
    TEST("Roman to int 2", roman_to_number("XCIX") == 99);
    TEST("Roman to int 3", roman_to_number("LXXXVIII") == 88);

    printf("%d fail, %d pass\n", count_fail, count_pass);
    return count_fail != 0;
}
