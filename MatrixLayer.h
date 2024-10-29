#pragma once
#ifndef MATRIXLAYER_H
#define MATRIXLAYER_H
#include <vector>
#include <functional>
#include <random>

/**
* @brief Layers of a MatrixNetwork
* 
* Stores values, weights, and nodes to simplify the network code
*/
struct Layer {
    int size;                                           //Number of neurons
    Layer* prev;                                        //Previous layer, nullptr if none

    std::vector<float> values;                          //Stored values of each node
    std::vector<float> biases;                          //Bias of each node
	std::vector<std::vector<float>> weights;            //Two dimensional array of weights

    std::function<float(float)> activation_function;    //activation function of the nodes, takes and returns a float

    explicit Layer(int size, Layer* prev = nullptr, std::function<float(float)> activation = nullptr)
        : size(size), prev(prev), values(size), biases(size), activation_function(activation)
    {
        if (prev != nullptr) {
            weights.resize(size, std::vector<float>(prev->size));
        }
    }

	//Creates a deep copy of the layer
    Layer copy() const {
        return new Layer(*this);
    }

    //Feeds the network forward from the previous layer
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

    //temporary function to randomize the network
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
private:
	//Constructor to copy a Layer
    Layer(const Layer* layer) : 
		size(layer->size), prev(nullptr), 
        values(std::vector<float>(layer->size)),
        biases(std::vector<float>(layer->biases)),
        weights(std::vector<std::vector<float>>(layer->weights)),
        activation_function(layer->activation_function)
    {

    }

};

#endif