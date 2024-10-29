#pragma once
#ifndef ACTIVATIONFUNCTIONS_H
#define ACTIVATIONFUNCTIONS_H
#include <cmath>
#include <algorithm>

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
};

#endif