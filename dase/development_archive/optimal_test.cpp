#include <iostream>
#include <chrono>
#include "analog_universal_node_engine.h"

int main() {
    for (int nodes : {12, 24, 36, 48, 60, 72}) {
        AnalogCellularEngine engine(nodes);
        
        auto start = std::chrono::high_resolution_clock::now();
        engine.performSignalSweep(1.0);
        auto end = std::chrono::high_resolution_clock::now();
        
        auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        std::cout << nodes << " nodes: " << ns << " ns" << std::endl;
    }
    return 0;
}