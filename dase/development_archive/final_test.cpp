#include <iostream>
#include <chrono>
#include "analog_universal_node_engine.h"

int main() {
    AnalogCellularEngine engine(36);  // Optimal node count
    
    // Test multiple single operations
    for (int i = 0; i < 10; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        engine.performSignalSweep(1.0);
        auto end = std::chrono::high_resolution_clock::now();
        
        auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        std::cout << "Run " << i+1 << ": " << ns << " ns" << std::endl;
    }
    return 0;
}