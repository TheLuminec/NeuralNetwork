#pragma once
#ifndef MATRIXNETWORK_H
#define MATRIXNETWORK_H
#include <memory>
#include "NeuralNetwork.h"
#include "MatrixLayer.h"
#include "ActivationFunctions.h"

class MatrixNetwork : public NeuralNetwork {
public:
	explicit MatrixNetwork(const std::vector<int>& layerSizes) : 
		NeuralNetwork(layerSizes.front(), layerSizes.back()), layerCount(layerSizes.size())
	{
		if (layerSizes.size() < 2) {
			throw std::invalid_argument("A matrix network needs at least 2 layers.");
		}

		layers.reserve(layerCount);

		Layer* prev = nullptr;
		for (int i : layerSizes) {
			layers.push_back(Layer(i, prev, nullptr));
			prev = &layers.back();
		}

		init();
	}

	void forward() override {
		layers.front().values = inputs;

		for (auto& l : layers) {
			l.forward();
		}

		outputs = layers.back().values;
		stepCount++;

	}

	void init();

	void input() override;
	void output() override;

	MatrixNetwork& copy() override { 
		return new MatrixNetwork(this); 
	}

protected:
	int layerCount;
	std::vector<Layer> layers;

	MatrixNetwork(MatrixNetwork* matNet) {

	}

};

#endif