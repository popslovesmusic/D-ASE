/**
 * @file analog.cpp
 * @brief Core D-ASE analog computer simulation engine
 * @author D-ASE Development Team
 * @version 1.0.0
 * @date 2025-08-11
 * 
 * This file implements the core analog computer simulation engine for D-ASE.
 * It provides classes for analog modules, computation engine, and JSON communication.
 */

#include <iostream>
#include <string>
#include <memory>
#include <map>

/**
 * @class AnalogModule
 * @brief Abstract base class for all analog computer modules
 * 
 * This class defines the interface that all analog modules must implement.
 * It provides basic functionality for input processing and output retrieval.
 */
class AnalogModule {
protected:
    std::string name;    ///< Module name identifier
    double output;       ///< Current output value

public:
    /**
     * @brief Constructor for AnalogModule
     * @param n Module name
     */
    AnalogModule(std::string n) : name(n), output(0.0) {}
    
    /**
     * @brief Virtual destructor
     */
    virtual ~AnalogModule() {}
    
    /**
     * @brief Process input and generate output
     * @param input Input value to process
     * @return Processed output value
     */
    virtual double processInput(double input) = 0;
    
    /**
     * @brief Get current output value
     * @return Current output value
     */
    double getOutput() { return output; }
    
    /**
     * @brief Get module name
     * @return Module name string
     */
    std::string getName() { return name; }
    
    /**
     * @brief Get module type identifier
     * @return Module type string
     */
    virtual std::string getType() = 0;
};