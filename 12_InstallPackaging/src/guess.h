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
static const char *romans[100] = {
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
static char buffer[16];

/** Converting numbers to the Roman numeral system
 * @param number number for conversion
 * @return number in the roman numeral system
 */
const char* number_to_roman(int number);

/** Сonversion from roman to decimal
 * @param roman number in the roman numeral system for conversion
 * @return number in the decimal numeral system
 */
int roman_to_number(const char *roman);

/** Сonverting a number to a string in a given number system
 * @param number number for conversion
 * @param is_roman given number system
 * @return a number as a string in a given number system
 */
const char* number_to_str(int number, bool is_roman);

/**
 * Main function of the program.
 */
int run_guess(int argc, char* argv[]);
