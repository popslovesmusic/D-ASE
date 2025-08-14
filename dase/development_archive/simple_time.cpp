#include <iostream> 
#include <chrono> 
#include "analog_universal_node_engine.h" 
int main() { 
    AnalogCellularEngine engine(100); 
    auto start = std::chrono::high_resolution_clock::now(); 
    engine.performSignalSweep(1.0); 
    auto end = std::chrono::high_resolution_clock::now(); 
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count(); 
    std::cout << "Single operation: " << ns << " ns" << std::endl; 
    return 0; 
} 
