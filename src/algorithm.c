#include "../inc/pathfinder.h"

void pathfinder(t_graph *graph, char **name_list) {
    for (int i = 0; i < graph->v; i++)
    {
        dijkstra(graph, i, name_list[i], name_list);
    }
}

void dijkstra(t_graph* graph, int src_idx, const char *src_name, char **name_list) {
    int v = graph->v;
    int *dist = malloc(v * sizeof(int));
    int *parents = malloc(v * sizeof(int));
    t_min_heap* min_heap = create_min_heap(v);

    if (!dist || !parents) {
        free(dist);
        free(parents);
        return;
    }

    for (int i = 1; i < v; i++) {
        dist[i] = INT_MAX;
        parents[i] = -1;
    }

    dist[src_idx] = 0;
    insert_min_node(min_heap, new_heap_node(src_idx, 0));
    
    while (min_heap->size > 0) {
        t_min_heap_node* min_node = extract_min_node(min_heap);
        int u = min_node->v;
     
        if (min_node->dist > dist[u]) {
            free(min_node);
            continue;
        }
    
        t_island* adj = graph->list[u].head;
        while (adj != NULL) {
            int v = mx_get_name_index(graph, adj->name);
            int weight = adj->weight;
            if (dist[u] != INT_MAX && weight + dist[u] < dist[v]) {
                dist[v] = weight + dist[u];
                parents[v] = u;
                insert_min_node(min_heap, new_heap_node(v, dist[v]));
            }
            adj = adj->next; 
        }
        free(min_node);
    }
    print_path(graph, dist, parents, src_name, name_list);
    
    free(dist);
    free(parents);
    free_min_heap(min_heap);
}
