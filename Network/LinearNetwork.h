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
class LinearNetwork : public virtual NeuralNetwork, public virtual Memory {
public:
	explicit LinearNetwork(std::vector<int> layerSizes) :
		NeuralNetwork(layerSizes.front(), layerSizes.back()), layerCount(layerSizes.size())
	{
		if (layerSizes.size() < 2) {
			throw std::invalid_argument("A matrix network needs at least 2 layers.");
		}

		//temporaryly here for Memory
		layerSizes.front() = inputCount;
		layerSizes.back() = outputCount;

		layers.reserve(layerCount);
		//potential problem code as it can deallocate the pointers

		Layer* prev = nullptr;
		for (int i : layerSizes) {
			layers.push_back(Layer(i, prev, nullptr));
			prev = &layers.back();
		}

		init();
	}

	explicit LinearNetwork(const int inputCount, const int outputCount, const int maxLayers = 64, std::function<float(float)> activation = nullptr) :
		NeuralNetwork(inputCount, outputCount), Memory(), layers(), layerCount(2)
	{
		layers.reserve(maxLayers);
		layers.push_back(Layer(inputCount));
		layers.push_back(Layer(outputCount, &layers.front(), activation));
		layers.back().prev = &layers.front();
	}

	//Function to add a hidden layer to the end of the network
	void addLayer(int size, std::function<float(float)> activation = nullptr) {
		Layer tmpOut = layers.back();
		layers.pop_back();
		Layer* prev = &layers.back();
		layers.push_back(Layer(size, prev, activation));
		tmpOut.prev = &layers.back();
		layers.push_back(tmpOut);
		layerCount++;
	}

	void addMemoryNode() {
		inputCount++;
		outputCount++;
	}
	void addMemoryNodes(int count) {
		for (int i = 0; i < count; i++) {
			addMemoryNode();
		}
	}

	void randomize() {
		for (Layer& l : layers) {
			l.randomWeightsAndBiases();
		}
	}

	//Creates a deep copy of the network
	LinearNetwork* copy() const override {
		return new LinearNetwork(*this);
	}

protected:
	int layerCount;					// number of layers
	std::vector<Layer> layers;		// layers inside the network

	//Initialization, called when network in constructed
	void init();

	void input() override;
	void output() override;

	void forward() override {
		layers.front().values = inputs;

		for (auto& l : layers) {
			l.forward();
		}

		outputs = layers.back().values;

	}

	//Constructor to copy a LinearNetwork
	LinearNetwork(const LinearNetwork* matNet) :
		NeuralNetwork(matNet), layerCount(matNet->layerCount)
	{
		layers.reserve(layerCount);
		Layer* prev = nullptr;
		for (auto& l : matNet->layers) {
			auto newLayer = l.copy();
			newLayer.prev = prev;
			layers.push_back(newLayer);
			prev = &newLayer;
		}
	}

};

#endif