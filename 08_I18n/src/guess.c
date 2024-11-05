#include <stdio.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "");
    bindtextdomain("guess", "po");
    textdomain("guess");

    printf(gettext("Think of a number between 1 and 100\n"));

    char ans[16];
    int left = 1, right = 100;
    while (left < right)
    {
        int mid = (left + right) / 2;
        printf(gettext("Is the number greater then %d?\n"), mid);
        
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

    printf(gettext("You thought of the number %d\n"), left);
    return 0;
 }