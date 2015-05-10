#pragma once

#include <vector>
#include <iostream>

class Model
{
public:
	
	enum State {
		A,
		H
	};

	int numberOfStates;

	std::vector< std::vector<float> > TransitionalProbabilities; //transition probabilities
	std::vector<float> PI; //prior probabilities

	//Emittion Probabilities
	float b(float x, int state)
	{
		if (state == 0)
			return 2 * (1-x);
		else if (state == 1)
			return 1 - x/2.0f;
		else
			std::cerr << "wrong choice of state";
	}

	Model (std::vector< std::vector<float> > TransitionalProbabilities, std::vector<float> PI)
	{
		this->TransitionalProbabilities = TransitionalProbabilities;
		this->PI = PI;

		numberOfStates = PI.size();
	}
};