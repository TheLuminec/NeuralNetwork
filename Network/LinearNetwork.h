#pragma once
#ifndef LINEARNETWORK_H
#define LINEARNETWORK_H
#include "NeuralNetwork.h"
#include "LinearLayer.h"
#include "Memory.h"

/**
* @brief A neural network using feed forward layers
* Standard feed forward weighted network.
*/
class LinearNetwork : public NeuralNetwork, Memory {
public:
	explicit LinearNetwork(int inputCount, int outputCount, int memorySize = 0, std::function<float(float)> activation = nullptr) :
		NeuralNetwork(inputCount, outputCount), layers()
	{
		layers.emplace_back(Layer(inputCount));
		layers.emplace_back(Layer(outputCount, activation));
	}

	//Function to add a hidden layer to the end of the network
	void addLayer(int size, std::function<float(float)> activation = nullptr) {
		if (layers.size() < 1) {
			throw std::runtime_error("Network input and output layers are not set.");
		}

		Layer outputLayer = layers.back();
		layers.pop_back();

		layers.emplace_back(size, activation);
		layers.push_back(outputLayer);
	}

	void randomize() {
		int prevSize = 0;
		for (Layer& l : layers) {
			l.randomWeightsAndBiases(prevSize);
			prevSize = l.size;
		}
	}

	//Creates a deep copy of the network
	LinearNetwork* copy() const override {
		return new LinearNetwork(*this);
	}

protected:
	std::vector<Layer> layers;		// layers inside the network

	void input() override;
	void output() override;

	void forward() override {
		layers.front().values = inputs;

		Layer* prev = nullptr;
		for (auto& l : layers) {
			l.forward(prev);
			prev = &l;
		}

		outputs = layers.back().values;

	}

	//Constructor to copy a LinearNetwork
	LinearNetwork(const LinearNetwork& matNet) :
		NeuralNetwork(matNet)
	{
		layers.reserve(matNet.layers.size());
		for (auto& l : matNet.layers) {
			auto newLayer = l.copy();
			layers.push_back(newLayer);
		}
	}

};

#endif