#include <iostream>
#include <chrono>
#include "analog_universal_node_engine.h"

int main() {
    for (int nodes : {6, 12, 18, 24, 30}) {
        AnalogCellularEngine engine(nodes);
        
        // Test 5 runs to get best case
        int best_ns = 999999999;
        for (int run = 0; run < 5; run++) {
            auto start = std::chrono::high_resolution_clock::now();
            engine.performSignalSweep(1.0);
            auto end = std::chrono::high_resolution_clock::now();
            
            int ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            if (ns < best_ns) best_ns = ns;
        }
        std::cout << nodes << " nodes: " << best_ns << " ns (best of 5)" << std::endl;
    }
    return 0;
}