#pragma once
#ifndef EVOLVABLE_H
#define EVOLVABLE_H
#include <iostream>
#include "NeuralNetwork.h"

/**
* @brief Gives a NeuralNetwork the ability to evolve
* 
* Creates standard fitness and evolution functions
*/
class Evolvable {
public:
	explicit Evolvable(const float mutationRate) : 
		fitness(0.0f), mutationRate(mutationRate)
	{}

	//Returns the fitness
	virtual float getFitness() const { return fitness; }

	//Sets the fitness
	virtual void setFitness(const float fitness) { this->fitness = fitness; }

	//Overload Operators for sorting

	inline bool operator<(const Evolvable& other) const {
		return this->getFitness() < other.getFitness();
	}
	inline bool operator>(const Evolvable& other) const {
		return this->getFitness() > other.getFitness();
	}
	inline std::ostream& operator<<(std::ostream& os) const {
		return os << getFitness() << std::endl;
	}

protected:
	float fitness;			//fitness of the Network
	float mutationRate;		//mutation rate, from 0-1 with 1 being 100%
	
	//Mutates the given NeuralNetwork by the mutation rate
	virtual void mutate() = 0;

	//Randomizes the given NeuralNetwork
	virtual void randomize() = 0;

	//Function to calculate and store the fitness of a Network
	virtual void fitnessCalc() = 0;
};

#endif