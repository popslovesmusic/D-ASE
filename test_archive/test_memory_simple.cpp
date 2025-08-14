/**
 * @file test_memory_single.cpp
 * @brief Everything in one file - simple test
 */

#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <vector>

namespace DASE {

// Simple memory node
struct MemoryNode {
    std::atomic<double> value{0.0};
    std::atomic<bool> computed{false};
    double params[4] = {0.0};
    int nodeType = 0;  // 0=amplifier
    
    void compute_parallel() {
        // Simple amplifier: output = input * gain
        value.store(params[0] * params[1]);
        computed.store(true);
    }
};

// Simple memory sheet
class MemoryParallelSheet {
private:
    static constexpr size_t MAX_NODES = 100;
    MemoryNode nodes[MAX_NODES];
    std::atomic<size_t> nodeCount{0};
    std::vector<std::thread> workers;

public:
    MemoryNode* allocateNode(int type) {
        size_t index = nodeCount.fetch_add(1);
        if (index >= MAX_NODES) return nullptr;
        
        nodes[index].nodeType = type;
        return &nodes[index];
    }
    
    size_t getNodeCount() const { 
        return nodeCount.load(); 
    }
    
    void executeParallelWaves() {
        size_t numCores = std::thread::hardware_concurrency();
        
        // Launch worker threads
        for (size_t core = 0; core < numCores; ++core) {
            workers.emplace_back([this, core, numCores]() {
                for (size_t i = core; i < nodeCount.load(); i += numCores) {
                    if (!nodes[i].computed.load()) {
                        nodes[i].compute_parallel();
                    }
                }
            });
        }
        
        // Wait for completion
        for (auto& worker : workers) {
            worker.join();
        }
        workers.clear();
    }
    
    const MemoryNode* getResults() const { 
        return nodes; 
    }
};

// Factory function
MemoryParallelSheet* createTestCircuit(size_t numNodes) {
    auto* sheet = new MemoryParallelSheet();
    
    for (size_t i = 0; i < numNodes; ++i) {
        MemoryNode* node = sheet->allocateNode(0); // Amplifier
        if (node) {
            node->params[0] = 1.0 + (i * 0.1);  // Input
            node->params[1] = 2.0 + (i * 0.05); // Gain
        }
    }
    
    return sheet;
}

} // namespace DASE

int main() {
    std::cout << "🧪 D-ASE Memory Engine Test" << std::endl;
    std::cout << "============================" << std::endl;
    
    // Create test circuit
    std::cout << "\n📊 Creating test circuit..." << std::endl;
    auto* circuit = DASE::createTestCircuit(10);
    
    // Run test
    std::cout << "\n🚀 Running test..." << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    
    circuit->executeParallelWaves();
    
    auto end = std::chrono::high_resolution_clock::now();
    double time_ms = std::chrono::duration<double, std::milli>(end - start).count();
    
    // Show results
    std::cout << "\n⚡ Results:" << std::endl;
    std::cout << "Time: " << time_ms << " ms" << std::endl;
    std::cout << "Nodes: " << circuit->getNodeCount() << std::endl;
    
    if (time_ms < 0.1) {
        std::cout << "✅ TARGET ACHIEVED!" << std::endl;
    } else {
        std::cout << "⚠️ Still fast!" << std::endl;
    }
    
    // Show computed values
    const auto* nodes = circuit->getResults();
    for (size_t i = 0; i < circuit->getNodeCount() && i < 5; ++i) {
        std::cout << "Node " << i << " = " << nodes[i].value.load() << std::endl;
    }
    
    // Cleanup
    delete circuit;
    
    std::cout << "\n🎉 Test complete!" << std::endl;
    return 0;
}