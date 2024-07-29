#ifndef GATE_H
#define GATE_H


//including necessary header file for edge structure and vectoer container 
#include "edge.h"
#include <vector>


//gate structure definition
struct Gate {
    std::vector<Edge> edges;
    int gate_delay;
};

#endif

