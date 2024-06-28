#ifndef GATE_H
#define GATE_H

#include "edge.h"
#include <vector>

struct Gate {
    std::vector<Edge> edges;
    int gate_delay;
};

#endif

