#include "bench_parser.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>

Graph parse_bench_file(const std::string& filename, std::unordered_map<std::string, int>& gate_map) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Wrong file name");
    }

    Graph graph;
    std::string line;
    int gate_count = 0;

    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        std::string token;
        iss >> token;

        if (token == "INPUT" || token == "OUTPUT") continue;

        size_t equal_pos = line.find('=');
        std::string gate_name = line.substr(0, equal_pos - 1);
        std::string gate_def = line.substr(equal_pos + 2);

        gate_name.erase(remove_if(gate_name.begin(), gate_name.end(), isspace), gate_name.end());

        if (gate_map.find(gate_name) == gate_map.end()) {
            gate_map[gate_name] = gate_count++;
            graph.push_back(Gate{});
        }
        int gate_index = gate_map[gate_name];

        std::replace(gate_def.begin(), gate_def.end(), '(', ' ');
        std::replace(gate_def.begin(), gate_def.end(), ')', ' ');
        std::replace(gate_def.begin(), gate_def.end(), ',', ' ');

        std::istringstream iss_def(gate_def);
        std::string gate_type;
        iss_def >> gate_type;

        std::vector<int> inputs;
        while (iss_def >> token) {
            if (gate_map.find(token) == gate_map.end()) {
                gate_map[token] = gate_count++;
                graph.push_back(Gate{});
            }
            inputs.push_back(gate_map[token]);
        }

        graph[gate_index].gate_delay = inputs.size();

        for (int input_index : inputs) {
            graph[input_index].edges.push_back({gate_index, graph[gate_index].gate_delay});
        }
    }

    file.close();
    return graph;
}

