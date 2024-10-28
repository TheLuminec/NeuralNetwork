#pragma once
#ifndef MEMORY_H
#define MEMORY_H

#include <vector>

class Memory {
public:
	Memory() : Memory(0) {}

	explicit Memory(const int memorySize) :
		memorySize(memorySize), memoryNodes(std::vector<float>(memorySize))
	{}

	virtual void setMemory(const int index, const float value) { memoryNodes[index] = value; }
	virtual void setMemory(const std::vector<float>& memory) { memoryNodes = memory; }
	virtual float getMemory(const int index) const { return memoryNodes[index]; }
	virtual std::vector<float> getMemory() const { return memoryNodes; }
	
	virtual ~Memory() {
		delete& memoryNodes;
	}

protected:
	int memorySize;
	std::vector<float> memoryNodes;
};

#endif