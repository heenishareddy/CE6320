#include "dijkstra.h"
#include <queue>
#include <limits>
#include <algorithm>

std::vector<int> dijkstra(const Graph& graph, int source_index, int target_vertex) {
    std::vector<int> dist(graph.size(), std::numeric_limits<int>::max());
    std::vector<int> prev(graph.size(), -1);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

    dist[source_index] = 0;
    pq.push({0, source_index});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (dist[u] == std::numeric_limits<int>::max())
            break;

        for (const Edge& edge : graph[u].edges) {
            int v = edge.target_vertex;
            int weight = edge.edge_weight;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[target_vertex] == std::numeric_limits<int>::max()) {
        return std::vector<int>();
    }

    std::vector<int> path;
    for (int at = target_vertex; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());

    return path;
}

