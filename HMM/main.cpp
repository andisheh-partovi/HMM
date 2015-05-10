#include <conio.h>

#include "IOHandler.h"
#include "Algorithms.h"

int main()
{
	Algorithms* algo = new Algorithms();
	IOHandler* ioHandle = new IOHandler();

	std::vector<float> observations;
	observations.push_back(0.5);
	observations.push_back(0.9);
	observations.push_back(0.1);

	algo->forwardBackward(observations);

	std::cout << "\nAlpha:\n";
	ioHandle->print2DArray(algo->getAlpha());

	std::cout << "\nBeta:\n";
	ioHandle->print2DArray(algo->getBeta());

	std::cout << "\nGamma:\n";
	ioHandle->print2DArray(algo->getGamma());
	
	std::cout << "\nRewards:\n";
	ioHandle->print2DArray(algo->viterbi(observations));

	_getch();
	return 0;
}