#pragma once

#include <vector>
#include <iostream>

#include "VectorAndMapUtility.h"
#include "Model.h"

class Algorithms
{
private:

	int totalTime;

	std::vector< std::vector<float> > alpha; //forward alpha table
	std::vector< std::vector<float> > beta; //backward beta table
	std::vector< std::vector<float> > gamma; //forward-backward gamma table

	Model* model;

	//utility handles
	VectorAndMapUtility* vectorUtilityHandle;

	//utilities
	float log2(float number);

public:
	Algorithms(Model* model, int totalTime);
	~Algorithms(void);

	//Algorithms for HMM
	void forward(std::vector<float> observations);
	void backward(std::vector<float> observations);
	void forwardBackward(std::vector<float> observations);
	std::vector< std::vector<float> >  viterbi(std::vector<float> observations);

	//interfaces:
	float getProbabilityOfObservation(std::vector<float> observations);
	std::vector<int> getMostLikelySequence(std::vector<float> observations);

	std::vector< std::vector<float> > getAlpha() { return alpha; }
	std::vector< std::vector<float> > getBeta() { return beta; }
	std::vector< std::vector<float> > getGamma() { return gamma; }
};

