#pragma once
#ifndef MEMORY_H
#define MEMORY_H
#include <vector>
#include "NeuralNetwork.h"

/**
* @brief Gives a NeuralNetwork the ability to store values for the next step
* 
* Creates a memory node for the input and adds adds output neurons to store values for the next step. 
* This memory is used for feedback connections in the neural network.
*/
class Memory : public virtual NeuralNetwork{
public:
	//jank implementation
	explicit Memory(const int memorySize) :
		memorySize(memorySize), memoryNodes(memorySize)
	{
		inputCount += memorySize;
		outputCount += memorySize;
		inputs = std::vector<float>(inputCount);
		outputs = std::vector<float>(outputCount);
	}

protected:
	int memorySize;						//Memory size
	std::vector<float> memoryNodes;		//Stored memory nodes

	//Set specific memory cell
	virtual void setMemory(const int index, const float value) { memoryNodes[index] = value; }

	//Set memory vector
	virtual void setMemory(const std::vector<float>& memory) { memoryNodes = memory; }

	//Get specific memory cell
	virtual float getMemory(const int index) const { return memoryNodes[index]; }

	//Get memory vector
	virtual std::vector<float> getMemory() const { return memoryNodes; }
};

#endif