#include "Algorithms.h"

#include <math.h>

Algorithms::Algorithms(Model* model, int totalTime)
{
	vectorUtilityHandle = new VectorAndMapUtility();

	this->model = model;
	this->totalTime = totalTime;

	//resizing alpha
	alpha.resize(totalTime);
	for (int i = 0 ; i < totalTime ; ++i)
		alpha[i].resize(model->numberOfStates);

	//resizing beta
	beta.resize(totalTime);
	for (int i = 0 ; i < totalTime ; ++i)
		beta[i].resize(model->numberOfStates);

	//resizing gamma
	gamma.resize(totalTime);
	for (int i = 0 ; i < totalTime ; ++i)
		gamma[i].resize(model->numberOfStates);
}

void Algorithms::forward(std::vector<float> observations)
{
	std::cout << "started forward\n";

	float sum = 0;

	for (int t = 0 ; t < totalTime ; ++t)
	{
		for (int i = 0 ; i < model->numberOfStates ; ++i)
		{
			if (t == 0)
				alpha[t][i] = model->PI[i] * model->b(observations[t], i);
			else
			{
				for (int j = 0 ; j < model->numberOfStates ; ++j)
					sum += alpha[t-1][j] * model->TransitionalProbabilities[j][i];

				alpha[t][i] = sum * model->b(observations[t], i);
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
		for (int i = 0 ; i < model->numberOfStates ; ++i)
		{
			if ( t == (totalTime - 1) )
				beta[t][i] = 1;
			else
			{
				for (int j = 0 ; j < model->numberOfStates ; ++j)
					sum += model->TransitionalProbabilities[i][j] * model->b(observations[t+1], j) * beta[t+1][j];

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
		for (int i = 0 ; i < model->numberOfStates ; ++i)
			normalizationFactor += (alpha[t][i] * beta[t][i]);

		for (int i = 0 ; i < model->numberOfStates ; ++i)
			gamma[t][i] = alpha[t][i] * beta[t][i] / normalizationFactor;

		normalizationFactor = 0;
	}
}

float Algorithms::getProbabilityOfObservation(std::vector<float> observations)
{
	float prob = 0;

	forward(observations);

	for (int i = 0 ; i < model->numberOfStates ; ++i)
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

	rewards.resize(model->numberOfStates);
	for (int i = 0 ; i < model->numberOfStates ; ++i)
		rewards[i].resize(totalTime);


	for (int t = 0 ; t < totalTime ; ++t)
	{
		for (int i = 0 ; i < model->numberOfStates ; ++i)
		{
			if (t == 0)
				rewards[i][t] = log2(model->PI[i]) +  log2(model->b(observations[t], i));
			else
			{
				currentObservation = log2(model->b(observations[t], i));

				for (int j = 0 ; j < model->numberOfStates ; ++j)
					currentRewards.push_back(currentObservation + log2(model->TransitionalProbabilities[j][i]) + rewards[j][t-1]);

				rewards[i][t] = vectorUtilityHandle->getMaxElement(currentRewards);
			}
		}
	}

	std::cout << "done viterbi\n";
	return rewards;
}

std::vector<int> Algorithms::getMostLikelySequence(std::vector<float> observations)
{
	std::vector< std::vector<float> > rewards = viterbi(observations);
	std::vector<int> optimalSequence;

	for (int t = 0 ; t < rewards.size() ; ++t)
		optimalSequence.push_back(vectorUtilityHandle->getMaxIndex(rewards[t]));

	return optimalSequence;
}

float Algorithms::log2(float number)
{
	return log(number) / log(2.0f);
}


Algorithms::~Algorithms(void)
{
	delete model;
	delete vectorUtilityHandle;
}
