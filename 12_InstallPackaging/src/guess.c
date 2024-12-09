#include <stdio.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>

#include "guess.h"

const char* number_to_roman(int number) {
    return romans[number - 1];
}

int roman_to_number(const char *roman) {
    for (int index = 0; index < 100; ++index) {
        if (!strcmp(romans[index], roman)) {
            return index + 1;
        }
    }
    return -1;
}

const char* number_to_str(int number, bool is_roman) {
    if (is_roman) {
        return number_to_roman(number);
    }
    sprintf(buffer, "%d", number);
    return buffer;
}

int run_guess(int argc, char **argv) {
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