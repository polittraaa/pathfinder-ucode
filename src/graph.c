#include "../inc/pathfinder.h"

void create_edge(t_graph* graph, const char* island_from, const char* island_to, int weight) {
    int from_idx = mx_get_name_index(graph, island_from);
    int to_idx = mx_get_name_index(graph, island_to);

    t_island* new_node = new_adj_node(island_to, weight);
    new_node->next = graph->list[from_idx].head;
    graph->list[from_idx].head = new_node;

    new_node = new_adj_node(island_from, weight);
    new_node->next = graph->list[to_idx].head;
    graph->list[to_idx].head = new_node;
    
}

t_graph* create_graph(int v) {
    t_graph* graph = malloc(sizeof(t_graph));
    graph->v = v;
    graph->list = malloc(v * sizeof(t_adj_list));

    for (int i = 0; i < v; i++) {
        graph->list[i].head = NULL;
    }
    return graph;
}

void clear_islands(t_adj_list* list) {
    t_island* node = list->head;
     while (node != NULL) {
        mx_strdel(&node->name);
        free(node);
        node = node->next;
    }
    list->head = NULL;
}

void clear_graph(t_graph** graph) {
    for (int i = 0; i < (*graph)->v; i++) {
       clear_islands(&(*graph)->list[i]);
    }
    if ((*graph)->name_list != NULL) {
        for (int i = 0; i < (*graph)->v; i++) {
            mx_strdel(&(*graph)->name_list[i]);
        }
        free((*graph)->name_list);
    }
    free((*graph)->list);
    free(*graph);
    *graph = NULL; 
}
