#ifdef BENCHMARK_BUILD

#include <iostream>
#include <chrono>
#include <vector>
#include <iomanip>
#include "analog_universal_node_engine.h"

#ifdef _OPENMP
#include <omp.h>
#endif

// CRITICAL: Implementation of missing function for linkage
void minimal_computation_test() {
    // Simple analog computation test
    AnalogCellularEngine engine(100);
    
    auto start = std::chrono::high_resolution_clock::now();
    
    // Perform minimal analog computation
    for (int i = 0; i < 1000; i++) {
        engine.performSignalSweep(1.0);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    
    std::cout << "Minimal computation test: " 
              << duration.count() / 1000.0 << " ns per operation" << std::endl;
}

// BREAKTHROUGH: Analog Cellular Computing Benchmark
void run_role_switch_benchmark() {
    std::cout << "\n=== D-ASE ANALOG CELLULAR COMPUTING BENCHMARK ===" << std::endl;
    std::cout << "Testing: Analog Signal-Controlled Universal Nodes" << std::endl;
    std::cout << "Target: <1,000 nanoseconds (1 microsecond)" << std::endl;
    std::cout << "Architecture: Parallel Analog Signal Processing" << std::endl;
    
    // Create analog cellular engine with 100 nodes
    AnalogCellularEngine engine(100);
    
    const int iterations = 1000;  // 1 million iterations for accurate measurement
    std::cout << "\nTesting " << iterations << " iterations of analog cellular computing..." << std::endl;
    
    // Warm-up phase
    std::cout << "Warming up..." << std::endl;
    for (int i = 0; i < 10000; i++) {
        engine.performSignalSweep(1.0 + i * 0.001);
    }
    
    // PARALLEL ANALOG PROCESSING BENCHMARK
    auto start_time = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < iterations; i++) {
        // Perform authentic analog cellular computing
        // Variable frequency for realistic signal processing
        double frequency = 1.0 + (i % 100) * 0.01;
        engine.performSignalSweep(frequency);
    }
    
    auto end_time = std::chrono::high_resolution_clock::now();
    
    // Calculate performance metrics
    auto total_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
    double avg_nanoseconds = static_cast<double>(total_duration.count()) / iterations;
    
    // Performance Analysis
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\n=== PERFORMANCE RESULTS ===" << std::endl;
    std::cout << "Total time: " << total_duration.count() / 1000000.0 << " milliseconds" << std::endl;
    std::cout << "Average per operation: " << avg_nanoseconds << " nanoseconds" << std::endl;
    std::cout << "Operations per second: " << (1000000000.0 / avg_nanoseconds) << std::endl;
    
    // Target analysis
    double target_ns = 1000.0;  // 1 microsecond target
    double performance_ratio = (avg_nanoseconds / target_ns) * 100.0;
    
    std::cout << "\n=== TARGET ANALYSIS ===" << std::endl;
    std::cout << "Target performance: " << target_ns << " nanoseconds" << std::endl;
    std::cout << "Achieved performance: " << avg_nanoseconds << " nanoseconds" << std::endl;
    
    if (avg_nanoseconds <= target_ns) {
        std::cout << "🎯 TARGET ACHIEVED! " << (target_ns - avg_nanoseconds) 
                  << " nanoseconds under target" << std::endl;
        std::cout << "Performance: " << std::setprecision(1) << (100.0 - performance_ratio + 100.0) 
                  << "% of target achieved" << std::endl;
    } else {
        double gap = avg_nanoseconds - target_ns;
        std::cout << "Gap to target: " << gap << " nanoseconds" << std::endl;
        std::cout << "Performance: " << std::setprecision(1) << (target_ns / avg_nanoseconds * 100.0) 
                  << "% of target achieved" << std::endl;
    }
    
    // Parallel processing validation
    std::cout << "\n=== PARALLEL PROCESSING STATUS ===" << std::endl;
    #ifdef _OPENMP
    std::cout << "OpenMP enabled: YES" << std::endl;
    std::cout << "Available threads: " << omp_get_max_threads() << std::endl;
    std::cout << "Parallel analog processing: ACTIVE" << std::endl;
    #else
    std::cout << "OpenMP enabled: NO (sequential processing)" << std::endl;
    std::cout << "Available threads: 1" << std::endl;
    #endif
    
    // JSON output for web interface compatibility
    std::cout << "\n=== JSON OUTPUT ===" << std::endl;
    std::cout << "{" << std::endl;
    std::cout << "  \"benchmark_type\": \"analog_cellular_computing\"," << std::endl;
    std::cout << "  \"iterations\": " << iterations << "," << std::endl;
    std::cout << "  \"avg_nanoseconds\": " << avg_nanoseconds << "," << std::endl;
    std::cout << "  \"target_nanoseconds\": " << target_ns << "," << std::endl;
    std::cout << "  \"target_achieved\": " << (avg_nanoseconds <= target_ns ? "true" : "false") << "," << std::endl;
    std::cout << "  \"performance_ratio\": " << (target_ns / avg_nanoseconds * 100.0) << "," << std::endl;
    std::cout << "  \"parallel_processing\": " << 
    #ifdef _OPENMP
    "true" <<
    #else 
    "false" <<
    #endif
    std::endl;
    std::cout << "}" << std::endl;
    
    // Run minimal computation test
    std::cout << "\n=== ADDITIONAL TESTS ===" << std::endl;
    minimal_computation_test();
}

int main() {
    std::cout << "D-ASE Analog Cellular Computing Engine Benchmark" << std::endl;
    std::cout << "Parallel Processing Implementation - Phase 5A" << std::endl;
    
    try {
        run_role_switch_benchmark();
        std::cout << "\n✅ Benchmark completed successfully!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "❌ Benchmark failed: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}

#endif // BENCHMARK_BUILD
