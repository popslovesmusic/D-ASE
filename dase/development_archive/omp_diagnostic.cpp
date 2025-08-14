#include <iostream> 
#include <omp.h> 
int main() { 
    std::cout << "Max threads available: " << omp_get_max_threads() << std::endl; 
    std::cout << "Num procs: " << omp_get_num_procs() << std::endl; 
    #pragma omp parallel 
    { 
        #pragma omp single 
        std::cout << "Actual threads in parallel region: " << omp_get_num_threads() << std::endl; 
    } 
    return 0; 
} 
