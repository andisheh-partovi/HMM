#pragma once

#include <dirent.h>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

class IOHandler
{
public:

	//generic
	std::string readFile(std::string filePath)
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

	void write2File(std::string text, std::string filePath)
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
	
	//screen output:
	template<typename T> void print1DArray(std::vector <T> inputData)
	{
		std::cout << "\n";

		for (unsigned int i = 0 ; i < inputData.size() ; ++i)
			std::cout << inputData.at(i)<< " , ";

		std::cout << "\n";
	}

	template<typename K, typename V> void printMap(std::unordered_map<K, V> inputMap)
	{
		std::unordered_map<K, V>::iterator iter;

		for (iter = inputMap.begin() ; iter != inputMap.end() ; ++iter)
			std::cout << iter->first << ":" << iter->second << "\n";
	}

	template<typename T> void print2DArray(std::vector< std::vector <T> > inputData)
	{
		for (unsigned int i = 0 ; i < inputData.size() ; ++i)
		{
			for (unsigned int j = 0 ; j < inputData.at(i).size() ; ++j)
			{
				std::cout << inputData.at(i).at(j) << " , ";
			}

			std::cout << "\n";
		}
	}

};

