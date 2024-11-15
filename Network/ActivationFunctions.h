#pragma once
#ifndef ACTIVATIONFUNCTIONS_H
#define ACTIVATIONFUNCTIONS_H

#include <algorithm>
#include <unordered_map>
#include <cmath>
#include <functional>
#include <string>
#include <stdexcept>

/**
* @brief Contains activation function implementations
*
* This namespace provides implementations for activation functions, such as Sigmoid, ReLU, and tanh.
*/
namespace ActivationFunctions {
    
    //Squishes the value to 0 - 1 for simple outputs
    static float sigmoid(float x) {
        return 1.0f / (1.0f + std::exp(-x));
    }

    //Does nothing unless the value is negative then returns 0
    static float relu(float x) {
        return std::max(0.0f, x);
    }

	//Squishes the value to -1 - 1 for simple outputs
    static float tanh(float x) {
        return std::tanh(x);
    }

    static std::unordered_map<std::string, std::function<float(float)>> functionMap = {
        {"relu", relu},
        {"sigmoid", sigmoid},
        {"tanh", tanh}
    };

    static std::function<float(float)> getFunction(const std::string& name) {
        if (name == "None") {
            return nullptr;
        }
        auto it = functionMap.find(name);
        if (it != functionMap.end()) {
            return it->second;
        }
        throw std::invalid_argument("Unknown activation function: " + name);
    }


};

#endif