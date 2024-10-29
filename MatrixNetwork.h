#pragma once
#ifndef MATRIXNETWORK_H
#define MATRIXNETWORK_H
#include "NeuralNetwork.h"
#include "MatrixLayer.h"

/**
* @brief A neural network using matrix operations for calculations.
* Standard feed forward weighted network.
*/
class MatrixNetwork : public NeuralNetwork {
public:
	explicit MatrixNetwork(std::vector<int> layerSizes) :
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

	//Creates a deep copy of the network
	MatrixNetwork* copy() const override {
		return new MatrixNetwork(*this);
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

	//Constructor to copy a MatrixNetwork
	MatrixNetwork(const MatrixNetwork* matNet) : 
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