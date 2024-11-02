#include "../inc/pathfinder.h"

bool is_in_list(const char *name, char **name_list, int size) {
    for (int i = 0; i < size; i++) {
        if (mx_strcmp(name_list[i], name) == 0) {
            return 1;
        }
    }
    return 0; 
} 

t_graph* parse_file(const char *filename) {
    int fd =  open(filename, O_RDONLY);
    if (fd < 0) {
        error_file_not_exist(filename);
    }
    char *filestr =  mx_file_to_str(filename);
    if (mx_strlen(filestr) == 0) {
        error_file_empty(filename);
        mx_strdel(&filestr);
        exit(-1);
    }

    char **lines = mx_strsplit(filestr, '\n');

    check_first_line(lines[0]);
    int v = mx_atoi(lines[0]);
    t_graph *graph = create_graph(v);
    graph->name_list = malloc(v * 2 * (sizeof(char*))); 
    int name_count = 0;

    int sum_len = 0;
    
    char *island_from;
    char *island_to;
    int weight;
    int offset = 0;

    for (int i = 1; lines[i] != NULL; i++) {
        island_from = mx_strndup(lines[i], mx_get_char_index(lines[i], '-'));
        if (!is_name_alphabetical(island_from )) is_invalid_line(i + 1);
        if (!is_in_list(island_from, graph->name_list, name_count)) {
            graph->name_list[name_count++] = island_from;
        }

        offset = mx_get_char_index(lines[i], '-') + 1;
        island_to = mx_strndup(&lines[i][offset], mx_get_char_index(&lines[i][offset], ','));
        if (!is_name_alphabetical(island_to)) is_invalid_line(i + 1);
        if(!is_in_list(island_to, graph->name_list, name_count)) {
            graph->name_list[name_count++] = island_to;
        }

        offset += mx_get_char_index(&lines[i][offset], ',') + 1;
        weight = mx_atoi(&lines[i][offset]);
        sum_len += weight;

        if (sum_len + weight > INT_MAX) {
        bridge_overload(sum_len, weight);
        }
        is_dup(lines[i]);
        create_edge(graph, island_from, island_to, weight);   
    }
    if (name_count != v) {
        islands_number();
    }
    mx_strdel(&filestr);
    mx_del_strarr(&lines);
    close(fd);
    
    return graph;
}
