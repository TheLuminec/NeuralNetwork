#pragma once
#ifndef LINEARLAYER_H
#define LINEARLAYER_H

#include <vector>
#include <functional>
#include <random>
#include <string>

/**
 * @brief Layers of a LinearNetwork
 *
 * Stores values, weights, and nodes to simplify the network code
 */
struct Layer {
    int size;                                           // Number of neurons

    std::vector<float> values;                          // Stored values of each node
    std::vector<float> biases;                          // Bias of each node
    std::vector<std::vector<float>> weights;            // Two-dimensional array of weights

    std::function<float(float)> activation_function;    // Activation function
    std::string activation_name;                        // Name of the activation function

    explicit Layer(int size, std::function<float(float)> activation = nullptr, const std::string& activation_name = "None")
        : size(size), values(size), biases(size), activation_function(activation), activation_name(activation_name)
    {}

    // Creates a deep copy of the layer
    Layer copy() const {
        return Layer(*this);
    }

    // Feeds the network forward from the previous layer
    void forward(const Layer* prev) {
        if (prev == nullptr)
            return;

        for (int i = 0; i < size; i++) {
            float sum = biases[i];
            for (int j = 0; j < prev->size; j++) {
                sum += prev->values[j] * weights[i][j];
            }

            values[i] = activation_function ? activation_function(sum) : sum;
        }
    }

    // Randomizes the weights and biases
    void randomWeightsAndBiases(int prevSize) {
        if (prevSize < 1)
            return;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<float> d(0.0f, 1.0f);
        weights.resize(size, std::vector<float>(prevSize));

        for (int i = 0; i < size; i++) {
            biases[i] = d(gen);
            for (int j = 0; j < prevSize; j++) {
                weights[i][j] = d(gen);
            }
        }
    }

    // Copy constructor
    Layer(const Layer& layer)
        : size(layer.size),
        values(layer.values),
        biases(layer.biases),
        weights(layer.weights),
        activation_function(layer.activation_function),
        activation_name(layer.activation_name)
    {}
};

#endif
