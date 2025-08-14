/**
 * @file memory_parallel_engine.cpp
 * @brief Implementation of memory-parallel processing engine
 * @target < 0.1ms for 100+ nodes
 */

#include "memory_parallel_engine.h"
#include <iostream>
#include <chrono>
#include <algorithm>

namespace DASE {

void MemoryParallelSheet::executeParallelWaves() {
    auto start = std::chrono::high_resolution_clock::now();
    
    size_t numCores = std::thread::hardware_concurrency();
    std::cout << "🔥 Executing on " << numCores << " cores, " 
              << nodeCount.load() << " nodes..." << std::endl;
    
    // Launch worker threads for parallel node processing
    for (size_t core = 0; core < numCores; ++core) {
        workers.emplace_back([this, core, numCores]() {
            // Each core processes every Nth node for load balancing
            for (size_t i = core; i < nodeCount.load(); i += numCores) {
                if (!nodes[i].computed.load()) {
                    nodes[i].compute_parallel();
                }
            }
        });
    }
    
    // Wait for parallel wave completion
    for (auto& worker : workers) {
        worker.join();
    }
    workers.clear();
    
    auto end = std::chrono::high_resolution_clock::now();
    double time_ms = std::chrono::duration<double, std::milli>(end - start).count();
    
    std::cout << "⚡ Parallel wave execution: " << time_ms << " ms" << std::endl;
    std::cout << "📊 Throughput: " << (nodeCount.load() / time_ms) << " nodes/ms" << std::endl;
}

// Factory method to create test circuit
MemoryParallelSheet* createTestCircuit(size_t numNodes) {
    auto* sheet = new MemoryParallelSheet();
    
    std::cout << "🏗️ Creating " << numNodes << " node test circuit..." << std::endl;
    
    for (size_t i = 0; i < numNodes; ++i) {
        MemoryNode* node = sheet->allocateNode(0); // Amplifier type
        if (node) {
            // Set test parameters: different gains for each node
            node->params[0] = 1.0 + (i * 0.1);  // Varying gain
            node->params[1] = 2.0 + (i * 0.05); // Varying input
        }
    }
    
    std::cout << "✅ Circuit created with " << sheet->getNodeCount() << " nodes" << std::endl;
    return sheet;
}

} // namespace DASE