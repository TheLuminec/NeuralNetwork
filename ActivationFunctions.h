#pragma once
#ifndef ACTIVATIONFUNCTIONS_H
#define ACTIVATIONFUNCTIONS_H

#include <cmath>
#include <algorithm>

namespace ActivationFunctions {
    static float sigmoid(float x) {
        return 1.0f / (1.0f + std::exp(-x));
    }

    static float relu(float x) {
        return std::max(0.0f, x);
    }

    static float tanh_activation(float x) {
        return std::tanh(x);
    }
};

#endif