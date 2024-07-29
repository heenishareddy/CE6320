#ifndef BENCH_PARSER_H
#define BENCH_PARSER_H

#include "graph.h"
#include <unordered_map>
#include <string>

Graph parse_bench_file(const std::string& filename, std::unordered_map<std::string, int>& gate_map);

#endif

