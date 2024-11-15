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
		//std::cout << "[" << i << "] --> Output: " << getOutput(i) << std::endl;
	}
}

//This will give the network fitness for having not max/min values
//i.e. goes to zero
void LinearNetwork::fitnessCalc() {
	for (int i = 0; i < outputCount; i++) {
		if (getOutput(i) < 0.95 && getOutput(i) > -0.95) {
			fitness += 1 - getOutput(i)*getOutput(i);
		}
	}
}

//This implmentation will just use randomization and best fitness selection
void LinearNetwork::optimize() {

}
