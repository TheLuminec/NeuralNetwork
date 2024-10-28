#pragma once
#ifndef MATRIXLAYER_H
#define MATRIXLAYER_H
#include <memory>
#include <vector>
#include <functional>
#include <random>
#include <iostream>

struct Layer {
    int size;
    Layer* prev;

    std::vector<float> values;
    std::vector<float> biases;
    std::vector<std::vector<float>> weights;

    std::function<float(float)> activation_function;

    Layer() : Layer(0) {}

    explicit Layer(int size, Layer* prev = nullptr, std::function<float(float)> activation = nullptr)
        : size(size), prev(prev), values(size), biases(size), activation_function(activation)
    {
        if (prev != nullptr) {
            weights.resize(size, std::vector<float>(prev->size));
        }
    }

    void forward() {
        if (prev == nullptr) {
            return;
        }

        for (int i = 0; i < size; i++) {
            float sum = biases[i];
            for (int j = 0; j < prev->size; j++) {
                sum += prev->values[j] * weights[i][j];
            }

            values[i] = activation_function ? activation_function(sum) : sum;
        }
    }

    void randomWeightsAndBiases() {
        if (prev == nullptr)
            return;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<float> d(0.0f, 1.0f);

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < prev->size; j++) {
                weights[i][j] = d(gen);
            }
        }

        for (int i = 0; i < size; i++) {
            biases[i] = d(gen);
        }
    }
};

#endif