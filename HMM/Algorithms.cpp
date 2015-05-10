#include "Algorithms.h"

#include <math.h>


Algorithms::Algorithms(void)
{
	vectorUtilityHandle = new VectorAndMapUtility();

	//hard-coding PI
	PI.push_back(0.5);
	PI.push_back(0.5);

	//hard-coding A
	std::vector<float> tempRow;
	tempRow.push_back(0.99f);
	tempRow.push_back(0.01f);
	A.push_back(tempRow);

	std::vector<float> tempRow2;
	tempRow2.push_back(0.1f);
	tempRow2.push_back(0.9f);
	A.push_back(tempRow2);

	//getting alpha vector size
	numberOfStates = PI.size();
	totalTime = 3; //observations.size();

	//resizing alpha
	alpha.resize(totalTime);
	for (int i = 0 ; i < totalTime ; ++i)
		alpha[i].resize(numberOfStates);

	//resizing beta
	beta.resize(totalTime);
	for (int i = 0 ; i < totalTime ; ++i)
		beta[i].resize(numberOfStates);

	//resizing gamma
	gamma.resize(totalTime);
	for (int i = 0 ; i < totalTime ; ++i)
		gamma[i].resize(numberOfStates);
}

void Algorithms::forward(std::vector<float> observations)
{
	std::cout << "started forward\n";

	float sum = 0;

	for (int t = 0 ; t < totalTime ; ++t)
	{
		for (int i = 0 ; i < numberOfStates ; ++i)
		{
			if (t == 0)
				alpha[t][i] = PI[i] * b(observations[t], i);
			else
			{
				for (int j = 0 ; j < numberOfStates ; ++j)
					sum += alpha[t-1][j] * A[j][i];

				alpha[t][i] = sum * b(observations[t], i);
				sum = 0;
			}
		}
	}

	std::cout << "done forward\n";
}

void Algorithms::backward(std::vector<float> observations)
{
	std::cout << "started backward\n";

	float sum = 0;

	for (int t = totalTime - 1 ; t >= 0 ; --t)
	{
		for (int i = 0 ; i < numberOfStates ; ++i)
		{
			if ( t == (totalTime - 1) )
				beta[t][i] = 1;
			else
			{
				for (int j = 0 ; j < numberOfStates ; ++j)
					sum += A[i][j] * b(observations[t+1], j) * beta[t+1][j];

				beta[t][i] = sum;
				sum = 0;
			}
		}
	}

	std::cout << "done backward\n";
}

void Algorithms::forwardBackward(std::vector<float> observations)
{
	forward(observations);
	backward(observations);

	float normalizationFactor = 0;


	for (int t = 0 ; t < totalTime ; ++t)
	{
		for (int i = 0 ; i < numberOfStates ; ++i)
			normalizationFactor += (alpha[t][i] * beta[t][i]);

		for (int i = 0 ; i < numberOfStates ; ++i)
			gamma[t][i] = alpha[t][i] * beta[t][i] / normalizationFactor;

		normalizationFactor = 0;
	}
}

float Algorithms::getProbabilityOfObservation(std::vector<float> observations)
{
	float prob;

	forward(observations);

	for (int i = 0 ; i < numberOfStates ; ++i)
		prob += alpha[alpha.size()-1][i];

	return prob;
}

std::vector< std::vector<float> >  Algorithms::viterbi(std::vector<float> observations)
{
	std::cout << "started viterbi\n";

	//creating rewards and sizing it
	std::vector< std::vector<float> > rewards;
	std::vector<float> currentRewards;
	float currentObservation;

	rewards.resize(numberOfStates);
	for (int i = 0 ; i < numberOfStates ; ++i)
		rewards[i].resize(totalTime);


	for (int t = 0 ; t < totalTime ; ++t)
	{
		for (int i = 0 ; i < numberOfStates ; ++i)
		{
			if (t == 0)
				rewards[i][t] = log2(PI[i]) +  log2(b(observations[t], i));
			else
			{
				currentObservation = log2(b(observations[t], i));

				for (int j = 0 ; j < numberOfStates ; ++j)
					currentRewards.push_back(currentObservation + log2(A[j][i]) + rewards[j][t-1]);

				rewards[i][t] = vectorUtilityHandle->getMaxElement(currentRewards);
			}
		}
	}

	std::cout << "done viterbi\n";
	return rewards;
}

//state 0 is A
//state 1 is H
float Algorithms::b(float x, int state)
{
	if (state == 0)
		return 2 * (1-x);
	else if (state == 1)
		return 1 - x/2.0f;
	else
		std::cerr << "wrong choice of state";
}

float Algorithms::log2(float number)
{
	return log(number) / log(2.0f);
}


Algorithms::~Algorithms(void)
{
}
