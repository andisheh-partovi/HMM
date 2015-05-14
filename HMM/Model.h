#pragma once

#include <vector>
#include <iostream>
#include <math.h>

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

	std::vector<float> meanPerState;
	std::vector<float> SDPerState;

	//Emittion Probabilities
	//float b(float x, int state)
	//{
	//	if (state == 0)
	//		return 2 * (1-x);
	//	else if (state == 1)
	//		return 1 - x/2.0f;
	//	else
	//		std::cerr << "wrong choice of state";
	//}

	float b(float x, int state)
	{
		return gaussianDist(x, meanPerState[state], SDPerState[state]);
	}

	//sqrt(2*pi) = 2.506
	float gaussianDist(float x, float mean, float SD)
	{
		return exp(-1 * (pow((x - mean),2)) / (2 * pow(SD,2))) / (SD * 2.506);
	}

	Model (std::vector< std::vector<float> > TransitionalProbabilities, std::vector<float> PI, std::vector<float> meanPerState, std::vector<float> SDPerState)
	{
		this->TransitionalProbabilities = TransitionalProbabilities;
		this->PI = PI;
		this->meanPerState = meanPerState;
		this->SDPerState = SDPerState;

		numberOfStates = PI.size();
	}
};