#ifndef DIJKSTRA_H
#define DIJKSTRA_H


// including header files that are necessary for graph structure  and vector containter
#include "graph.h"
#include <vector>


//prototype for dijkstra's algorithm 
std::vector<int> dijkstra(const Graph& graph, int source_index, int target_index);

#endif

