#pragma once
#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <vector>

class NeuralNetwork {
public:
	NeuralNetwork() : NeuralNetwork(0,0) {}

	explicit NeuralNetwork(const int inputCount, const int outputCount) : 
		stepCount(0), 
		inputCount(inputCount), inputs(std::vector<float>(inputCount)),
		outputCount(outputCount), outputs(std::vector<float>(outputCount))
	{}

	virtual void forward() = 0;
	virtual void input() = 0;
	virtual void output() = 0;

	virtual NeuralNetwork* copy() const = 0;

protected:
	int stepCount;
	int inputCount;
	std::vector<float> inputs;
	int outputCount;
	std::vector<float> outputs;

	virtual void setInput(const int index, const float value) { inputs[index] = value; }
	virtual void setInputs(const std::vector<float>& inputs) { this->inputs = inputs; }
	virtual float getOutput(const int index) const { return outputs[index]; }
	virtual std::vector<float> getOutputs() const { return outputs; }

};

#endif