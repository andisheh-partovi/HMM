#include "Run.h"


Run::Run(void)
{
	ioHandle = new IOHandler();
}

Model* Run::createModel()
{
	std::vector< std::vector<float> > TransitionalProbabilities;
	std::vector<float> PI;

	//hard-coding PI
	PI.push_back(0.5);
	PI.push_back(0.5);

	//hard-coding A
	std::vector<float> tempRow;
	tempRow.push_back(0.99f);
	tempRow.push_back(0.01f);
	TransitionalProbabilities.push_back(tempRow);

	std::vector<float> tempRow2;
	tempRow2.push_back(0.1f);
	tempRow2.push_back(0.9f);
	TransitionalProbabilities.push_back(tempRow2);

	return new Model(TransitionalProbabilities, PI);
}

void Run::run(std::string dataFolderPath)
{
	//later get the observations from file
	//std::string dataFileContent = ioHandler->readFile(std::string filePath);
	std::vector<float> observations;
	observations.push_back(0.5);
	observations.push_back(0.9);
	observations.push_back(0.1);

	//creating the model and algorithm
	Model* model = createModel(); 
	algoHandle = new Algorithms(model , observations.size());

	algoHandle->forwardBackward(observations);

	std::cout << "\nAlpha:\n";
	ioHandle->print2DArray(algoHandle->getAlpha());

	std::cout << "\nBeta:\n";
	ioHandle->print2DArray(algoHandle->getBeta());

	std::cout << "\nGamma:\n";
	ioHandle->print2DArray(algoHandle->getGamma());
	
	std::cout << "\nRewards:\n";
	ioHandle->print2DArray(algoHandle->viterbi(observations));

	std::cout << "\nOptimal Sequence:\n";
	ioHandle->print1DArray(algoHandle->getMostLikelySequence(observations));
}


Run::~Run(void)
{
}
