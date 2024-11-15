#include "LinearNetwork.h"
#include "ActivationFunctions.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

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

