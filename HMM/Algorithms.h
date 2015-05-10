#pragma once

#include <vector>
#include <iostream>

class Algorithms
{
private:

	std::vector< std::vector<float> > alpha; //forward alpha table
	std::vector< std::vector<float> > beta; //backward beta table
	std::vector< std::vector<float> > gamma; //forward-backward gamma table

	//model
	std::vector< std::vector<float> > A; //transition probabilities
	std::vector<float> PI; //prior probabilities
	float b(float x, int state); //Emittion Probabilities

	int numberOfStates;
	int totalTime;


public:
	Algorithms(void);
	~Algorithms(void);

	//Algorithms for HMM
	void forward(std::vector<float> observations);
	void backward(std::vector<float> observations);
	void forwardBackward(std::vector<float> observations);
	void viterbi(std::vector<float> observations);

	//interfaces:
	float getProbabilityOfObservation(std::vector<float> observations);

	std::vector< std::vector<float> > getAlpha() { return alpha; }
	std::vector< std::vector<float> > getBeta() { return beta; }
	std::vector< std::vector<float> > getGamma() { return gamma; }
};

