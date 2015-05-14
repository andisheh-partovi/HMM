#pragma once

#include "IOHandler.h"
#include "Algorithms.h"
#include "MyStringUtility.h"

class Run
{
private:
	Algorithms* algoHandle;
	IOHandler* ioHandle;
	MyStringUtility* stringUtilityHandle;

	Model* createModel();
	std::vector<float> getObservations(std::string fileContent);

public:
	Run(void);
	~Run(void);

	void run(std::string dataFilePath);
};

