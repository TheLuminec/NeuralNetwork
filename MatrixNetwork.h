#pragma once
#ifndef MATRIXNETWORK_H
#define MATRIXNETWORK_H
#include "NeuralNetwork.h"

struct Layer {
	std::vector<float> values;
	std::vector<float> weights;
	std::vector<float> biases;

	void activation() {
		
	}

	void forward() {

	}
};

class MatrixNetwork : public NeuralNetwork {
public:
	explicit MatrixNetwork() {

	}

protected:
	std::vector<Layer> layers;

	
};

#endif