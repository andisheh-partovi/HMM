#pragma once

#include <boost/lexical_cast.hpp>//casting long double to string

class Reward
{
public:

	float reward;
	int state;

	Reward(float reward, int state)
	{
		this->reward = reward;
		this->state = state;
	}

	std::string toString()
	{
		return "state: " + boost::lexical_cast<std::string>(this->state) + " reward: " + boost::lexical_cast<std::string>(this->reward);
	}
};