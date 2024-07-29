#include "dijkstra.h"
#include <queue>
#include <limits>
#include <algorithm>


//code to find the shortest path between the input to output gate using the dijkstra's algorithm 
std::vector<int> dijkstra(const Graph& graph, int source_index, int target_vertex) {  

  // intializing vectros
  std::vector<int> dist(graph.size(), std::numeric_limits<int>::max());  //for distance 
  std::vector<int> prev(graph.size(), -1);  //for previous vertex
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;  //for priority queue



  dist[source_index] = 0;  //source vertex distance is set to 0 
  pq.push({0, source_index});  //pushed into priority queue

    while (!pq.empty()) {
      int u = pq.top().second; //extracting the vertex with smallest distance from priority queue 
        pq.pop();

        if (dist[u] == std::numeric_limits<int>::max())  //this condition is when current vertex is still maximum 
            break;

        for (const Edge& edge : graph[u].edges) {  
            int v = edge.target_vertex;
            int weight = edge.edge_weight;  // in this block we are iterating through the edges of current vertex 

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pq.push({dist[v], v});  //if any shorter path is found above, then update the distance and previous vector 
            }
        }
    }

    if (dist[target_vertex] == std::numeric_limits<int>::max()) {  // this condition is when tatrget vertex is still maximum 
        return std::vector<int>();
    }

    std::vector<int> path;
    for (int at = target_vertex; at != -1; at = prev[at]) {
      path.push_back(at);  // redesign the shortest path from input to output 
    }


    std::reverse(path.begin(), path.end()); //start it all over again by reversing the paths 

    return path;
}

