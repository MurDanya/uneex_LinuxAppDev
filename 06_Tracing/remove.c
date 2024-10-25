#include <stdio.h>
#include <string.h>
#include <dlfcn.h>

typedef int (*func)(const char *);

int remove(const char *filename)
{
    if (strstr(filename, "PROTECT")) {
        return 1;
    }
    func true_remove = dlsym(RTLD_NEXT, "remove");
    return true_remove(filename);
}