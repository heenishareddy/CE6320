#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"
#include <vector>

std::vector<int> dijkstra(const Graph& graph, int source_index, int target_index);

#endif

