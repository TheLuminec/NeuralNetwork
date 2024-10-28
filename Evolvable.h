#pragma once
#ifndef EVOLVABLE_H
#define EVOLVABLE_H
#include <iostream>

class Evolvable {
public:
	Evolvable() : Evolvable(0.01) {}

	explicit Evolvable(const float mutationRate) : 
		fitness(0.0f), mutationRate(mutationRate)
	{}

	virtual void mutate() = 0;
	virtual void randomize() = 0;

	virtual void fitnessCalc() = 0;
	virtual float getFitness() const { return fitness; }
	virtual void setFitness(const float fitness) { this->fitness = fitness; }

	//Overload Operators
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
	float fitness;
	float mutationRate;
	
};

#endif