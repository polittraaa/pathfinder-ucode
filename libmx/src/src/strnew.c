#include "libmx.h"

char *mx_strnew(const int size) {
    char *new_str = (char *)malloc(size + 1);

    if (new_str == NULL)
        return NULL;

    for (int i = 0; i <= size; i++) {
        new_str[i] = '\0';
    }
    return new_str;
}
