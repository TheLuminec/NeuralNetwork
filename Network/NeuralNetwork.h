#pragma once
#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H
#include <vector>

/**
 * @brief Abstract base class representing a generic neural network.
 * 
 * This class provides a common interface and shared functionality for different types of neural networks.
 */
class NeuralNetwork {
public:
    explicit NeuralNetwork(const int inputCount, const int outputCount) :
        stepCount(0),
        inputCount(inputCount), inputs(inputCount),
        outputCount(outputCount), outputs(outputCount)
    {}

    //Simulates a single step of the network.
    virtual void simulate() {
        input();
        forward();
        stepCount++;
        output();
    }

    //Creates a deep copy of the current network
    virtual NeuralNetwork* copy() const = 0;

protected:
    int stepCount;                  // Number of simulation steps executed
    int inputCount;                 // Number of inputs to the network
    std::vector<float> inputs;      // Input values for the network
    int outputCount;                // Number of outputs from the network
    std::vector<float> outputs;     // Output values from the network

    //Constructor to copy a NeuralNetwork
    NeuralNetwork(const NeuralNetwork* net) :
        stepCount(0), inputCount(net->inputCount), outputCount(net->outputCount),
        inputs(net->inputCount), outputs(net->outputCount)
    {}

    //Performs forward propagation through the network.
    virtual void forward() = 0;

    //Handles inputs to the network.
    virtual void input() = 0;

    //Handles outputs from the network.
    virtual void output() = 0;

    //Sets the value of a specific input neuron.
    virtual void setInput(const int index, const float value) { inputs[index] = value; }

    //Sets all input values for the network.
    virtual void setInputs(const std::vector<float>& inputs) { this->inputs = inputs; }

    //Retrieves the value of a specific output neuron.
    virtual float getOutput(const int index) const { return outputs[index]; }

    //Retrieves all output values from the network.
    virtual std::vector<float> getOutputs() const { return outputs; }

};

#endif
