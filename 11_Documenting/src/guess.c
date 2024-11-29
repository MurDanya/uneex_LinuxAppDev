/** @mainpage
 * # Programm for guessing a number from 1 to 100
 */
/** @page program Guessing number game program.
 * You need to guess a number between 1 and 100.
 * The program will ask questions whether your number is greater than a certain number.
 * You need to answer yes or no (y or n).
 * 
 * Argument --help will show the helping message
 * Argument -r will enable Roman number representation
 * 
 */

#include <stdio.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>
#include <stdbool.h>

/** @file guess.c
 * Implementation
 *
 * Guesses the number
 */

/**
 * Roman numeral conversion table
 */
const char *romans[100] = {
    "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X",
    "XI", "XII", "XIII", "XIV", "XV", "XVI", "XVII", "XVIII", "XIX", "XX",
    "XXI", "XXII", "XXIII", "XXIV", "XXV", "XXVI", "XXVII", "XXVIII", "XXIX", "XXX",
    "XXXI", "XXXII", "XXXIII", "XXXIV", "XXXV", "XXXVI", "XXXVII", "XXXVIII", "XXXIX", "XL",
    "XLI", "XLII", "XLIII", "XLIV", "XLV", "XLVI", "XLVII", "XLVIII", "XLIX", "L",
    "LI", "LII", "LIII", "LIV", "LV", "LVI", "LVII", "LVIII", "LIX", "LX",
    "LXI", "LXII", "LXIII", "LXIV", "LXV", "LXVI", "LXVII", "LXVIII", "LXIX", "LXX",
    "LXXI", "LXXII", "LXXIII", "LXXIV", "LXXV", "LXXVI", "LXXVII", "LXXVIII", "LXXIX", "LXXX",
    "LXXXI", "LXXXII", "LXXXIII", "LXXXIV", "LXXXV", "LXXXVI", "LXXXVII", "LXXXVIII", "LXXXIX", "XC",
    "XCI", "XCII", "XCIII", "XCIV", "XCV", "XCVI", "XCVII", "XCVIII", "XCIX", "C"
};

/**
 * Buffer for converting a number to a string
 */
char buffer[16];

/** Converting numbers to the Roman numeral system
 * @param number number for conversion
 * @return number in the roman numeral system
 */
const char* number_to_roman(int number) {
    return romans[number - 1];
}

/** Сonversion from roman to decimal
 * @param roman number in the roman numeral system for conversion
 * @return number in the decimal numeral system
 */
int roman_to_number(const char *roman) {
    for (int index = 0; index < 100; ++index) {
        if (!strcmp(romans[index], roman)) {
            return index + 1;
        }
    }
    return -1;
}

/** Сonverting a number to a string in a given number system
 * @param number number for conversion
 * @param is_roman given number system
 * @return a number as a string in a given number system
 */
const char* number_to_str(int number, bool is_roman) {
    if (is_roman) {
        return number_to_roman(number);
    }
    sprintf(buffer, "%d", number);
    return buffer;
}

int main(int argc, char **argv) {
    setlocale(LC_ALL, "");
    bindtextdomain("guess", "po");
    textdomain("guess");

    bool is_roman = false;
    if (argc > 1) {
        if (!strcmp(argv[1], "--help")) {
            printf(gettext("Guessing a number from 1 to 100.\n"));
            printf(gettext("Usage:\n"));
            printf(gettext("    --help  Show help message\n"));
            printf(gettext("    -r      Enable Roman numbers\n"));
            return 0;
        }
        if (!strcmp(argv[1], "-r")) {
            is_roman = true;
        }
    }

    printf(gettext("Think of a number between 1 and 100\n"));

    char ans[16];
    int left = 1, right = 100;
    
    while (left < right)
    {
        int mid = (left + right) / 2;
        printf(gettext("Is the number greater then %s?\n"), number_to_str(mid, is_roman));
        
        if (scanf("%10s", ans) != 1)
            continue;

        if (strcmp(ans, gettext("y")) == 0 || strcmp(ans, gettext("yes")) == 0)
        {
            left = mid + 1;
        }
        else if (strcmp(ans, gettext("n")) == 0 || strcmp(ans, gettext("no")) == 0)
        {
            right = mid;
        }
        else
        {
            printf(gettext("Enter yes(y) or no(n)\n"));
        }
    }

    printf(gettext("You thought of the number %s\n"), number_to_str(left, is_roman));
    return 0;
 }