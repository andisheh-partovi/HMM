#include "Run.h"

Run::Run(void)
{
	ioHandle = new IOHandler();
	stringUtilityHandle = new MyStringUtility();
}

Model* Run::createModel()
{
	std::vector< std::vector<float> > TransitionalProbabilities;
	std::vector<float> PI;
	std::vector<float> meanPerState;
	std::vector<float> SDPerState;

	//hard-coding PI
	PI.push_back(0.5);
	PI.push_back(0.5);

	//hard-coding A
	std::vector<float> tempRow;
	tempRow.push_back(0.3f);
	tempRow.push_back(0.7f);
	TransitionalProbabilities.push_back(tempRow);

	std::vector<float> tempRow2;
	tempRow2.push_back(0.5f);
	tempRow2.push_back(0.5f);
	TransitionalProbabilities.push_back(tempRow2);

	meanPerState.push_back(100);
	meanPerState.push_back(100);

	SDPerState.push_back(50);
	SDPerState.push_back(50);

	return new Model(TransitionalProbabilities, PI, meanPerState, SDPerState);
}

std::vector<float> Run::getObservations(std::string fileContent)
{
	std::vector<float> observations;

	std::vector<std::string> allLines = stringUtilityHandle->split(fileContent, '\n' );
	
	for (unsigned int i = 0 ; i < allLines.size() ; ++i)
		observations.push_back(stringUtilityHandle->string2Int(allLines[i]));

	return observations;
}

void Run::run(std::string dataFilePath)
{
	//later get the observations from file
	std::vector<float> observations = getObservations(ioHandle->readFile(dataFilePath));
	//std::vector<float> observations;
	//observations.push_back(0.5);
	//observations.push_back(0.9);
	//observations.push_back(0.1);

	//creating the model and algorithm
	Model* model = createModel(); 
	algoHandle = new Algorithms(model , observations.size());

	//algoHandle->forwardBackward(observations);

	//std::cout << "\nAlpha:\n";
	//ioHandle->print2DArray(algoHandle->getAlpha());

	//std::cout << "\nBeta:\n";
	//ioHandle->print2DArray(algoHandle->getBeta());

	//std::cout << "\nGamma:\n";
	//ioHandle->print2DArray(algoHandle->getGamma());

	std::cout << "\nOptimal Sequence:\n";
	ioHandle->print1DArray(algoHandle->getMostLikelySequence(observations));
}


Run::~Run(void)
{
}
