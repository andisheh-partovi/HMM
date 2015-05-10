#include "IOHandler.h"


IOHandler::IOHandler(void)
{
}

std::string IOHandler::readFile(std::string filePath)
{
	std::string fileContent;
	std::string eachLine;
	std::ifstream file;

	file.open (filePath);

	if (file.is_open())
	{
		while(!file.eof()) // To get you all the lines.
		{
			std::getline(file,eachLine); // Saves the line in STRING.
			fileContent += eachLine + "\n";
		}

		file.close();

		return fileContent;
	}
	else
	{
		std::cerr << "unable to open file for reading:" << filePath;
		return NULL;
	}
}

//writes the input "text" to the files with the specified path
void IOHandler::write2File(std::string text, std::string filePath)
{
	std::ofstream file;
	file.open (filePath);

	if (file.is_open())
	{
		file << text;

		file.close();

	}
	else
		std::cerr << "unable to open file for writing:" << filePath;
}

IOHandler::~IOHandler(void)
{
}
