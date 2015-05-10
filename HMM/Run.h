#pragma once

#include "IOHandler.h"
#include "Algorithms.h"

class Run
{
private:
	Algorithms* algoHandle;
	IOHandler* ioHandle;

	Model* createModel();

public:
	Run(void);
	~Run(void);

	void run(std::string dataFolderPath);
};

