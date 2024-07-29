#include "bench_parser.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>


//to parse a bench file and create a graph
Graph parse_bench_file(const std::string& filename, std::unordered_map<std::string, int>& gate_map) {
  std::ifstream file(filename);//to open a file 
    if (!file) {
        throw std::runtime_error("Wrong file name");
    }

   

 Graph graph;  //to intialize a graph that stores gates and it's connection s 
    std::string line;  //stores each line of the file 
    int gate_count = 0;  //to keep a track of the number of gates

 

   while (getline(file, line)) {  //to go through each and every line in the file 
      if (line.empty() || line[0] == '#') continue;  //to avoid lines starting with # and empty lines

      std::istringstream iss(line);  //string stream is created to parse the line
      std::string token;  //to store the first token 
      iss >> token;   //extract it 

      if (token == "INPUT" || token == "OUTPUT") continue;  //omit the lines that start with INOUT or oUTPUT 

     size_t equal_pos = line.find('=');  //to find the location of =
        std::string gate_name = line.substr(0, equal_pos - 1);
        std::string gate_def = line.substr(equal_pos + 2);  //extract gate name and gate definition 

        gate_name.erase(remove_if(gate_name.begin(), gate_name.end(), isspace), gate_name.end());  //to remove white spaces from gate name 

        if (gate_map.find(gate_name) == gate_map.end()) {
            gate_map[gate_name] = gate_count++;
            graph.push_back(Gate{});  // first adding an empty gate to graph for new gate 
        }
        int gate_index = gate_map[gate_name];  //find the index 


	//for easy parasing we replacesome of the charcters in the gate def 
        std::replace(gate_def.begin(), gate_def.end(), '(', ' ');
        std::replace(gate_def.begin(), gate_def.end(), ')', ' ');
        std::replace(gate_def.begin(), gate_def.end(), ',', ' ');

        std::istringstream iss_def(gate_def);
        std::string gate_type;
        iss_def >> gate_type;  //repeat

        std::vector<int> inputs;  //define a vector to store indices of incoming gate 
        while (iss_def >> token) {  // for the remaining tokens 
	  if (gate_map.find(token) == gate_map.end()) { // add input gate and increcrement the gate count 
                gate_map[token] = gate_count++;
                graph.push_back(Gate{});  //create space for new graph byt adding a additional gate 
            }
	  inputs.push_back(gate_map[token]);  //inoput gate index is added to the vector 
        }

        graph[gate_index].gate_delay = inputs.size();  //setting the gate delay based on inputs


	//create edge from input gates to the present gate 
        for (int input_index : inputs) {
            graph[input_index].edges.push_back({gate_index, graph[gate_index].gate_delay});
        }
    }

   file.close();  //close 
    return graph;
}

