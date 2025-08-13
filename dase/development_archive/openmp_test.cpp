#include <iostream>
#include <omp.h>
#include <vector>
#include <chrono>

// Simple OpenMP verification test
void test_basic_openmp() {
    std::cout << "=== BASIC OPENMP TEST ===" << std::endl;
    
    std::cout << "Max threads available: " << omp_get_max_threads() << std::endl;
    
    // Force thread settings
    omp_set_dynamic(0);
    omp_set_num_threads(12);
    
    std::cout << "After setting to 12 threads: " << omp_get_max_threads() << std::endl;
    
    // Test parallel region
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        
        #pragma omp critical
        {
            std::cout << "Thread " << thread_id << " of " << num_threads << " threads" << std::endl;
        }
    }
    
    // Test parallel for loop
    std::cout << "\n=== PARALLEL FOR TEST ===" << std::endl;
    
    std::vector<double> data(1000, 1.0);
    double sum = 0.0;
    
    auto start = std::chrono::high_resolution_clock::now();
    
    #pragma omp parallel for reduction(+:sum) num_threads(12)
    for (int i = 0; i < 1000; i++) {
        // Simulate some work
        for (int j = 0; j < 100; j++) {
            data[i] += sin(i * 0.001 + j * 0.01);
        }
        sum += data[i];
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Parallel computation completed in " << duration.count() << " microseconds" << std::endl;
    std::cout << "Sum result: " << sum << std::endl;
    
    // Test with explicit thread verification in loop
    std::cout << "\n=== THREAD VERIFICATION IN LOOP ===" << std::endl;
    
    #pragma omp parallel for num_threads(12)
    for (int i = 0; i < 100; i++) {
        if (i < 10) {  // Only print first 10 to avoid spam
            #pragma omp critical
            {
                std::cout << "Processing item " << i << " on thread " << omp_get_thread_num() << std::endl;
            }
        }
    }
}

int main() {
    std::cout << "OpenMP Direct Verification Test" << std::endl;
    
    #ifdef _OPENMP
    std::cout << "OpenMP version: " << _OPENMP << std::endl;
    #else
    std::cout << "OpenMP NOT ENABLED!" << std::endl;
    return 1;
    #endif
    
    test_basic_openmp();
    
    return 0;
}