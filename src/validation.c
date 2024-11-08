#include "pathfinder.h"

void mx_printerr(const char* errortext) {
    write(2, errortext, mx_strlen(errortext));
}

void error_file_not_exist(const char* filename) {
    mx_printerr("error: file ");
    mx_printerr(filename);
    mx_printerr(" does not exist\n");
    exit(-1);
}
void error_file_empty(const char* filename) {
    mx_printerr("error: file ");
    mx_printerr(filename);
    mx_printerr(" is empty\n");
}
void bridge_overload() {
    mx_printerr("error: sum of bridges lengths is too big\n");
    exit(-1);
}

void check_first_line(char* firstline) {
   if (not_a_number(firstline) == true || firstline[0] == '0') {
       mx_printerr("error: line 1 is not valid\n");
       exit(-1);
   }
}

void inv_number_arguments() {
    mx_printerr("usage: ./pathfinder [filename]\n");
    exit(-1);
}

void islands_number() {
    mx_printerr("error: invalid number of islands\n");
    exit(-1);
}

void is_invalid_line(int idx) {
    mx_printerr("error: line "); 
    mx_printerr(mx_itoa(idx));
    mx_printerr(" is not valid\n");
    exit(-1);
}

void dup_bridges(char *island_from, char *island_to) {
    if (mx_strcmp(island_from, island_to) == 0) {
    mx_printerr("error: duplicate bridges");
    exit(-1);
    }
}

bool is_dup(char* edge) {
    char c = '-';
    int count = 0;
    while (*edge != '\0') {
        if (*edge == c)
            count++;
        if (count > 1) {
            return true;  
        }
        edge++;
    }
    return false;
}
