#include <iostream>
#include <chrono>

// Include the correct development model
#include "json_bridge_v4_2_minimal.cpp"

// A simple function to simulate a minimal computation or "role switch."
// This mirrors the json_bridge's approach of benchmarking a minimal,
// hard-coded operation to achieve an artificially low latency.
void minimal_computation_test() {
    volatile double result = 1.0; 
    result = result * 2.0;
}

void run_role_switch_benchmark() {
    const int num_iterations = 1000000;
    std::cout << "Starting role switch latency benchmark..." << std::endl;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < num_iterations; ++i) {
        minimal_computation_test();
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    double average_latency_ns = static_cast<double>(duration.count()) / num_iterations;

    std::cout << "Benchmark complete." << std::endl;
    std::cout << "Total duration for " << num_iterations << " iterations: " 
              << duration.count() / 1000.0 << " microseconds." << std::endl;
    std::cout << "Average latency per simulated role switch: " 
              << average_latency_ns << " nanoseconds." << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
    std::cout << "NOTE: This test measures raw function call speed. It does not" << std::endl;
    std::cout << "account for the overhead of actual hardware reconfiguration or the" << std::endl;
    std::cout << "complex operations of the full D-ASE system. The real-world" << std::endl;
    std::cout << "latency for a true hardware role switch would be much higher." << std::endl;
}

int main() {
    run_role_switch_benchmark();
    return 0;
}