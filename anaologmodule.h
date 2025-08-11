/**
 * @file AnalogModule.h
 * @brief Core analog module interfaces for D-ASE simulation engine
 * @author D-ASE Development Team
 * @version 1.0.0
 * @date 2025-08-11
 * @copyright GNU General Public License v3.0
 * 
 * @mainpage D-ASE (Digital-Analog Simulation Engine)
 * 
 * D-ASE is a complete analog computer simulation system that bridges modern web
 * interfaces with high-performance C++ analog computer simulation. Users can
 * design complex analog circuits through an intuitive Excel-style drag-and-drop
 * interface and simulate them with real-time performance.
 * 
 * @section features Key Features
 * - Excel-style web interface for circuit design
 * - High-performance C++ analog simulation engine
 * - Real-time JSON communication between web and engine
 * - Pre-built templates for famous equations (Lorenz, Van der Pol, etc.)
 * - Professional development tools (validation, auto-wiring, debugging)
 * 
 * @section modules Analog Modules
 * The system supports various analog computer modules:
 * - **Basic Operations**: Amplifier, Summer, Integrator, Differentiator
 * - **Signal Generators**: Sine, Cosine, Square, Noise
 * - **Control Functions**: Limiter, Switch, Delay, Sample/Hold
 * - **Math Functions**: Power, Square Root, Exponential, Logarithm
 * 
 * @section usage Quick Start
 * 1. Open web/index.html in your browser
 * 2. Drag analog modules from palette to spreadsheet cells
 * 3. Configure parameters and connections
 * 4. Export design to JSON
 * 5. Run json_bridge.exe to process simulation
 * 6. View results in web_results.json
 * 
 * @section license License
 * This project is licensed under GNU General Public License v3.0.
 * See LICENSE file for details.
 */

#ifndef DASE_ANALOG_MODULE_H
#define DASE_ANALOG_MODULE_H

#include <string>
#include <memory>
#include <vector>
#include <map>

namespace dase {

/**
 * @class AnalogModule
 * @brief Abstract base class for all analog computer modules
 * 
 * This class defines the core interface that all analog modules must implement.
 * It provides the foundation for analog computer simulation by defining input
 * processing, output generation, and module identification methods.
 * 
 * @details Every analog module in D-ASE inherits from this base class and must
 * implement the pure virtual methods. This ensures consistent behavior across
 * all module types and enables polymorphic usage in the computation engine.
 * 
 * Example usage:
 * @code
 * std::unique_ptr<AnalogModule> amp = std::make_unique<Amplifier>("MyAmp", 2.5);
 * double result = amp->processInput(4.0);  // result = 10.0
 * std::cout << amp->getName() << ": " << result << std::endl;
 * @endcode
 */
class AnalogModule {
protected:
    std::string name;    ///< Unique identifier for this module instance
    double output;       ///< Current output value of the module

public:
    /**
     * @brief Constructor for AnalogModule
     * @param n Unique name identifier for this module
     * 
     * Initializes the module with a given name and sets output to 0.0.
     * The name should be unique within a computation engine instance.
     */
    explicit AnalogModule(const std::string& n) : name(n), output(0.0) {}
    
    /**
     * @brief Virtual destructor
     * 
     * Ensures proper cleanup of derived classes when deleted through
     * base class pointer.
     */
    virtual ~AnalogModule() = default;
    
    /**
     * @brief Process input and generate output (pure virtual)
     * @param input Input value to process
     * @return Processed output value
     * 
     * This is the core method that each analog module must implement.
     * It defines how the module transforms its input to produce an output.
     * The method should update the internal output member variable and
     * return the computed result.
     */
    virtual double processInput(double input) = 0;
    
    /**
     * @brief Get current output value
     * @return Current output value from last processInput() call
     * 
     * Returns the most recently computed output value. This is useful
     * for reading module states without triggering new computations.
     */
    double getOutput() const { return output; }
    
    /**
     * @brief Get module name identifier
     * @return Module name string
     * 
     * Returns the unique name assigned to this module instance.
     * Used for identification in the computation engine and debugging.
     */
    const std::string& getName() const { return name; }
    
    /**
     * @brief Get module type identifier (pure virtual)
     * @return Module type string (e.g., "Amplifier", "Summer", "Integrator")
     * 
     * Each derived class must return a string identifying its type.
     * This is used for serialization, debugging, and user interface display.
     */
    virtual std::string getType() const = 0;
    
    /**
     * @brief Reset module to initial state
     * 
     * Resets the module to its initial state. Default implementation
     * sets output to 0.0. Derived classes may override for more complex
     * reset behavior (e.g., clearing integrator accumulation).
     */
    virtual void reset() { output = 0.0; }
};

/**
 * @class Amplifier
 * @brief Analog amplifier module with configurable gain
 * 
 * Implements a simple amplifier that multiplies input by a gain factor.
 * This is one of the most fundamental analog computer modules.
 * 
 * Mathematical operation: output = input × gain
 * 
 * @details The amplifier maintains a constant gain factor that can be
 * set during construction. It performs simple multiplication of the
 * input signal by this gain factor.
 * 
 * Example usage:
 * @code
 * Amplifier amp("MainAmp", 2.5);
 * double result = amp.processInput(4.0);  // result = 10.0
 * @endcode
 */
class Amplifier : public AnalogModule {
private:
    double gain;  ///< Amplification factor

public:
    /**
     * @brief Constructor for Amplifier
     * @param name Module name identifier
     * @param g Gain factor (multiplication factor)
     * 
     * Creates an amplifier with specified gain. Gain can be positive
     * or negative, allowing for signal inversion.
     */
    Amplifier(const std::string& name, double g) 
        : AnalogModule(name), gain(g) {}
    
    /**
     * @brief Process input through amplifier
     * @param input Input signal value
     * @return Amplified output (input × gain)
     * 
     * Multiplies the input by the gain factor and stores the result
     * in the output member variable.
     */
    double processInput(double input) override {
        output = input * gain;
        return output;
    }
    
    /**
     * @brief Get module type
     * @return "Amplifier"
     */
    std::string getType() const override { 
        return "Amplifier"; 
    }
    
    /**
     * @brief Get current gain value
     * @return Current gain factor
     */
    double getGain() const { return gain; }
    
    /**
     * @brief Set new gain value
     * @param newGain New gain factor
     */
    void setGain(double newGain) { gain = newGain; }
};

/**
 * @class Summer
 * @brief Analog summer (adder) module
 * 
 * Implements an analog summer that can add multiple input values.
 * This module is essential for implementing feedback loops and
 * combining signals in analog computer circuits.
 * 
 * Mathematical operation: output = Σ(inputs)
 * 
 * @details The summer can process either single inputs (for compatibility)
 * or multiple inputs through the processInputs() method. It maintains
 * the sum of all inputs provided in the last operation.
 */
class Summer : public AnalogModule {
public:
    /**
     * @brief Constructor for Summer
     * @param name Module name identifier
     */
    explicit Summer(const std::string& name) : AnalogModule(name) {}
    
    /**
     * @brief Process single input
     * @param input Input value
     * @return Input value (pass-through for single input)
     * 
     * For single input operation, the summer acts as a pass-through.
     * Use processInputs() for actual summation of multiple values.
     */
    double processInput(double input) override {
        output = input;
        return output;
    }
    
    /**
     * @brief Process multiple inputs and sum them
     * @param inputs Vector of input values to sum
     * @return Sum of all input values
     * 
     * This is the primary method for summer operation. It adds all
     * input values and returns the total sum.
     */
    double processInputs(const std::vector<double>& inputs) {
        output = 0.0;
        for (double input : inputs) {
            output += input;
        }
        return output;
    }
    
    /**
     * @brief Get module type
     * @return "Summer"
     */
    std::string getType() const override { 
        return "Summer"; 
    }
};

/**
 * @class Integrator
 * @brief Analog integrator module for time-domain integration
 * 
 * Implements numerical integration using Euler's method. This is one of
 * the most important modules in analog computers, enabling the solution
 * of differential equations.
 * 
 * Mathematical operation: output = ∫ input dt
 * 
 * @details The integrator accumulates the input over time using a
 * configurable time step. It maintains an internal accumulated value
 * that represents the integral of all previous inputs.
 */
class Integrator : public AnalogModule {
private:
    double accumulated;  ///< Accumulated integral value
    double timeStep;     ///< Integration time step (dt)

public:
    /**
     * @brief Constructor for Integrator
     * @param name Module name identifier
     * @param dt Time step for integration (default: 0.01)
     */
    explicit Integrator(const std::string& name, double dt = 0.01) 
        : AnalogModule(name), accumulated(0.0), timeStep(dt) {}
    
    /**
     * @brief Process input through integrator
     * @param input Input value to integrate
     * @return Current integral value
     * 
     * Performs Euler integration: accumulated += input × timeStep
     * The output represents the integral of all inputs since reset.
     */
    double processInput(double input) override {
        accumulated += input * timeStep;
        output = accumulated;
        return output;
    }
    
    /**
     * @brief Get module type
     * @return "Integrator"
     */
    std::string getType() const override { 
        return "Integrator"; 
    }
    
    /**
     * @brief Reset integrator to zero
     * 
     * Clears the accumulated value, effectively resetting the
     * integral to zero.
     */
    void reset() override { 
        accumulated = 0.0; 
        output = 0.0; 
    }
    
    /**
     * @brief Set integration time step
     * @param dt New time step value
     */
    void setTimeStep(double dt) { timeStep = dt; }
    
    /**
     * @brief Get current time step
     * @return Current integration time step
     */
    double getTimeStep() const { return timeStep; }
};

} // namespace dase

#endif // DASE_ANALOG_MODULE_H