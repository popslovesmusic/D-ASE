#include <iostream>
#include <chrono>
#include "analog_universal_node_engine.h"

int main() {
    AnalogCellularEngine engine(12);
    
    std::cout << "Testing 1000 individual measurements vs batch:" << std::endl;
    
    // Method 1: 1000 individual measurements
    double total_individual = 0;
    for (int i = 0; i < 1000; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        engine.performSignalSweep(1.0);
        auto end = std::chrono::high_resolution_clock::now();
        total_individual += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }
    
    std::cout << "Individual avg: " << total_individual / 1000.0 << " ns" << std::endl;
    
    // Method 2: Batch timing (like benchmark does)
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++) {
        engine.performSignalSweep(1.0);
    }
    auto end = std::chrono::high_resolution_clock::now();
    
    auto batch_avg = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / 1000.0;
    std::cout << "Batch avg: " << batch_avg << " ns" << std::endl;
    
    return 0;
}