#include "../inc/pathfinder.h"

void print_path_between(const char *src_name, const char *dest_name) {
    mx_printstr("Path: ");
    mx_printstr(src_name);
    mx_printstr(" -> ");
    mx_printstr(dest_name);
    mx_printstr("\n");
}

void print_distance(int *distances, int dest, int *parents) {
    int total_distance = 0;

    mx_printstr("\nDistance: ");
    for (int i = dest; parents[i] != -1; i = parents[i]) {
        int parent = parents[i];
        mx_printint(distances[i] - distances[parent]);
        if (parents[parent] != -1) mx_printstr(" + ");
        total_distance += distances[i] - distances[parent];
    }
    mx_printstr(" = ");
    mx_printint(total_distance);
    mx_printstr("\n");
}

void print_route(int *parents, int dest, char **name_list) {
    if (parents[dest] == -1) {
        mx_printstr(name_list[dest]);
        return;
    }
    print_route(parents, parents[dest], name_list);
    mx_printstr(" -> ");
    mx_printstr(name_list[dest]);
}

void print_path(t_graph *graph, int *dist, int *parents, const char *src_name, char **name_list) {
    mx_printstr("========================================\n");
    for (int i = 0; i < graph->v; i++) {
        print_path_between(src_name, name_list[i]);
        mx_printstr("Route: ");
        print_route(parents, i, name_list);
        mx_printstr("\n");
        print_distance(dist, i, parents);
    }
    mx_printstr("========================================\n");
}

