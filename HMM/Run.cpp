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

	//// Transitional Probs Model 1 non-holiday houses
	//// A
	//std::vector<float> tempRow;
	//tempRow.push_back(0.867f);
	//tempRow.push_back(0.133f);
	//TransitionalProbabilities.push_back(tempRow);
	//// H
	//std::vector<float> tempRow2;
	//tempRow2.push_back(0.006f);
	//tempRow2.push_back(0.994f);
	//TransitionalProbabilities.push_back(tempRow2);

	//// Transitional Probs Model 1 holiday houses
	//// A
	//std::vector<float> tempRow;
	//tempRow.push_back(0.994f);
	//tempRow.push_back(0.006f);
	//TransitionalProbabilities.push_back(tempRow);
	//// H
	//std::vector<float> tempRow2;
	//tempRow2.push_back(0.133f);
	//tempRow2.push_back(0.867f);
	//TransitionalProbabilities.push_back(tempRow2);

	//// Transitional Probs Model 2 non-holiday houses
	//// A
	//std::vector<float> tempRow;
	//tempRow.push_back(0.550f);
	//tempRow.push_back(0.450f);
	//TransitionalProbabilities.push_back(tempRow);
	//// H
	//std::vector<float> tempRow2;
	//tempRow2.push_back(0.192f);
	//tempRow2.push_back(0.808f);
	//TransitionalProbabilities.push_back(tempRow2);

	// Transitional Probs Model 2 holiday houses
	// A
	std::vector<float> tempRow;
	tempRow.push_back(0.808f);
	tempRow.push_back(0.192f);
	TransitionalProbabilities.push_back(tempRow);
	// H
	std::vector<float> tempRow2;
	tempRow2.push_back(0.450f);
	tempRow2.push_back(0.550f);
	TransitionalProbabilities.push_back(tempRow2);

	////house 1
	//meanPerState.push_back(103.066f); //for "Away" state
	//meanPerState.push_back(621.303f); //for "Home" state
	//SDPerState.push_back(46.729f); //for "Away" state
	//SDPerState.push_back(657.912f); //for "Home" state

	////house 2
	//meanPerState.push_back(55.523f); //for "Away" state
	//meanPerState.push_back(1411.336f); //for "Home" state
	//SDPerState.push_back(143.540f); //for "Away" state
	//SDPerState.push_back(1463.731f); //for "Home" state

	//house 3
	meanPerState.push_back(21.674f); //for "Away" state
	meanPerState.push_back(466.184f); //for "Home" state
	SDPerState.push_back(18.538f); //for "Away" state
	SDPerState.push_back(499.698f); //for "Home" state

	////house 4
	//meanPerState.push_back(201.625f); //for "Away" state
	//meanPerState.push_back(739.588f); //for "Home" state
	//SDPerState.push_back(37.511f); //for "Away" state
	//SDPerState.push_back(758.378f); //for "Home" state

	//house 5
	//meanPerState.push_back(53.592f); //for "Away" state
	//meanPerState.push_back(340.311f); //for "Home" state
	//SDPerState.push_back(19.564f); //for "Away" state
	//SDPerState.push_back(348.669f); //for "Home" state

	//house 6
	//meanPerState.push_back(137.093f); //for "Away" state
	//meanPerState.push_back(656.255f); //for "Home" state
	//SDPerState.push_back(53.058f); //for "Away" state
	//SDPerState.push_back(682.685f); //for "Home" state

	//house 7
	//meanPerState.push_back(288.732f); //for "Away" state
	//meanPerState.push_back(963.473f); //for "Home" state
	//SDPerState.push_back(100.451f); //for "Away" state
	//SDPerState.push_back(1001.960f); //for "Home" state

	//house 8
	//meanPerState.push_back(99.693f); //for "Away" state
	//meanPerState.push_back(690.166f); //for "Home" state
	//SDPerState.push_back(108.465f); //for "Away" state
	//SDPerState.push_back(731.838f); //for "Home" state

	////house 9
	//meanPerState.push_back(91.721f); //for "Away" state
	//meanPerState.push_back(635.537f); //for "Home" state
	//SDPerState.push_back(32.691f); //for "Away" state
	//SDPerState.push_back(652.640f); //for "Home" state

	return new Model(TransitionalProbabilities, PI, meanPerState, SDPerState);
}

std::vector<float> Run::getObservations(std::string fileContent)
{
	std::vector<float> observations;
	std::vector<std::string> eachNumber;
	float sum = 0;
	int time;

	std::vector<std::string> allLines = stringUtilityHandle->split(fileContent, '\n' );
	
	for (unsigned int i = 0 ; i < allLines.size() ; ++i)
	{
		eachNumber = stringUtilityHandle->split(allLines[i], '\t' );
		time = stringUtilityHandle->string2Int(eachNumber[1]);

		if (time > 33 && time <45) //if it is dinner time, i.e. between [34,44]
		{
			//std::cout << eachNumber[0];
			sum += stringUtilityHandle->string2Int(eachNumber[0]);
		}
		else if (time == 45)
		{
			observations.push_back(sum / 11);
			sum = 0;
		}
	}	

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

	
	std::vector<int> sequence = algoHandle->getMostLikelySequence(observations);
	std::string sequenceText;

	//std::cout << "\nOptimal Sequence:\n";
	//ioHandle->print1DArray(sequence);

	for (int i = 0 ; i < sequence.size() ; ++i)
	{
		if (sequence[i] == 0)
			sequenceText += "A";
		else if (sequence[i] == 1)
			sequenceText += "H";

		sequenceText += "\n";
	}

	ioHandle->write2File(sequenceText, "mostLikelyObservation3.txt");
}


Run::~Run(void)
{
}
