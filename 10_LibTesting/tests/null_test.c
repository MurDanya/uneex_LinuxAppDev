#include "test_utils.h"

int main()
{
    volatile int count_pass = 0;
    volatile int count_fail = 0;

    /* Clearing an NULL pointer is a no-op */
    float *a = 0;
    buf_clear(a);
    TEST("clear empty", buf_size(a) == 0);
    TEST("clear no-op", a == 0);
    
    return 0;
}


