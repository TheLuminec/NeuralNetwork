#include "LinearNetwork.h"
#include "ActivationFunctions.h"
#include <iostream>

void LinearNetwork::init() {
	for (int i = 0; i < layerCount; i++) {
		layers[i].activation_function = ActivationFunctions::relu;
		layers[i].randomWeightsAndBiases();
	}

	layers.back().activation_function = ActivationFunctions::tanh;
}

void LinearNetwork::input() {
	for (int i = 0; i < inputCount; i++) {
		setInput(i, rand()%3 - 1);
	}
}

void LinearNetwork::output() {
	std::cout << stepCount << ":--------------------------------" << std::endl;
	for (int i = 0; i < outputCount; i++) {
		std::cout << "[" << i << "] --> Output: " << getOutput(i) << std::endl;
	}
}