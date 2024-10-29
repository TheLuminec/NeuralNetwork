#pragma once
#ifndef DYNAMICNETWORK_H
#define DYNAMICNETWORK_H

#include "NeuralNetwork.h"

class DynamicNetwork : public virtual NeuralNetwork {
public:
	void simulate() override {
		input();
		fullStep();
		output();
	}

	virtual void fullStep() {
		currentSimStep = 0;
		simulationSteps(stepsPerSimulation);
	}


private:
	int stepsPerSimulation;
	int currentSimStep;


	virtual void simulationStep() {
		currentSimStep++;
	}

	virtual void simulationSteps(int steps) {
		for (int i = 0; i < steps; i++) {
			simulationStep();
		}
	}
};

#endif