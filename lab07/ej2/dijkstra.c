#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <stdio.h>

#include "cost.h"
#include "graph.h"
#include "mini_set.h"

cost_t min(cost_t a, cost_t b) {
    cost_t minimo = (a < b) ? a : b;
    return minimo;
}

cost_t *dijkstra(graph_t graph, vertex_t init) {
    // cantidad de vertices
    unsigned int n = graph_max_vertexs(graph);

    // arreglo de vertices visitados
    bool visited[n];
    for (unsigned int i=0; i<n; ++i) {
        visited[i] = false;
    }

    // minimos caminos
    cost_t *results = calloc(n,sizeof(cost_t));
    vertex_t c;
    cost_t mincost;

    // conjunto de vertices no visitados
    set c_set = set_empty();
    for (unsigned int i=0; i<n; ++i) {
        c_set = set_add(c_set, i);
    }

    // visito c
    c_set = set_elim(c_set, init);
    visited[init] = true;

    // cargo las primeras distancias de init a los demas
    for (unsigned int j=0; j<n; ++j) {
        results[j] = graph_get_cost(graph,init,j);
    }

    // algoritmo
    while (!set_is_empty(c_set)) {
        mincost = INT_MAX;
        c = INT_MAX;
        for (unsigned int i=0; i<n; ++i) {
            if (!visited[i]) {
                if (min(mincost,results[i]) == results[i]) {
                    mincost = results[i];
                    c = i;
                }
            }
        }
        c_set = set_elim(c_set, c);
        visited[c] = true;
        for (unsigned int j=0; j<n; ++j) {
            if (!visited[j]) {
                if (!cost_is_inf(graph_get_cost(graph,c,j))) {
                    results[j] = min(results[j], results[c] + graph_get_cost(graph,c,j));
                }
            }
        }
    }

    return results;
}
