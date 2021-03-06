#pragma once

#include <unordered_map>
#include <vector>
#include <set>

class VectorAndMapUtility
{
public:

	VectorAndMapUtility(){}

	template<typename K , typename V> std::vector<K> getKeys(std::unordered_map<K, V> inputMap)
	{
		std::vector<K> keys;

		std::unordered_map<K, V>::iterator iter;

		for (iter = inputMap.begin() ; iter != inputMap.end() ; ++iter)
		{
			keys.push_back(iter->first);
		}

		return keys;
	}

	template<typename K , typename V> std::set<K> getUniqueKeys(std::unordered_map<K, V> inputMap)
	{
		std::set<K> keys;

		std::unordered_map<K, V>::iterator iter;

		for (iter = inputMap.begin() ; iter != inputMap.end() ; ++iter)
		{
			keys.insert(iter->first);
		}

		return keys;
	}

	template<typename K , typename V> std::vector<V> getValues(std::unordered_map<K, V> inputMap)
	{
		std::vector<V> values;

		std::unordered_map<K, V>::iterator iter;

		for (iter = inputMap.begin() ; iter != inputMap.end() ; ++iter)
		{
			values.push_back(iter->second);
		}

		return values;
	}

	//merges the maps in the input list of maps, if their index is between the start and end index
	template<typename K, typename V> std::unordered_map<K, V> 
	mergeMaps(std::vector< std::unordered_map<K, V> > inputList, int startIndex, int endIndex)
	{
		std::unordered_map<K, V> returnMap;
		std::unordered_map<K, V> currentMap;
		K currentKey;
		V currentValue;
		std::unordered_map<K, V>::iterator iter;

		for(int i = startIndex ; i <= endIndex ; ++i) 
		{
			currentMap = inputList.at(i);

			for (iter = currentMap.begin() ; iter != currentMap.end() ; ++iter)
			{
				currentKey = iter->first;
				currentValue = iter->second;
				if (returnMap.find(currentKey) == returnMap.end()) //if not in the map
					returnMap[currentKey] = currentValue;
				else
					returnMap[currentKey] = returnMap[currentKey] + currentValue;
			}
		}

		return returnMap;
	}

	template<typename K, typename V> V sumOfElements(std::unordered_map<K, V> inputMap)
	{
		V sum = 0;

		std::unordered_map<K, V>::iterator iter;

		for (iter = inputMap.begin() ; iter != inputMap.end() ; ++iter)
		{
			sum += iter->second;
		}

		return sum;
	}

	template<typename T> T sumOfElements(std::vector <T> inputVector)
	{
		T sum = 0;

		for (unsigned int i = 0 ; i < inputVector.size() ; ++i)
			sum += inputVector[i];

		return sum;
	}

	template<typename T> T getMaxElement(std::vector <T> inputVector)
	{
		T max = inputVector.at(0);

		for (unsigned int i = 1 ; i < inputVector.size() ; ++i)
			if (inputVector[i] > max)
				max = inputVector[i];

		return max;
	}

	template<typename T> int getMaxIndex(std::vector <T> inputVector)
	{
		T max = inputVector.at(0);
		int maxIndex = 0;

		for (unsigned int i = 1 ; i < inputVector.size() ; ++i)
			if (inputVector[i] > max)
			{
				max = inputVector[i];
				maxIndex = i;
			}

		return maxIndex;
	}

	template<typename K, typename V> std::unordered_map<K, V> normalise(std::unordered_map<K, V> inputMap)
	{
		V sum = sumOfElements(inputMap);

		std::unordered_map<K, V>::iterator iter;

		for (iter = inputMap.begin() ; iter != inputMap.end() ; ++iter)
		{
			inputMap[iter->first] = iter->second / sum;
		}

		return inputMap;
	}

	//precond: inputMap1 is a subset of inputMap2
	template<typename K, typename V> std::unordered_map<K, V> add(std::unordered_map<K, V> inputMap1, std::unordered_map<K, V> inputMap2)
	{
		std::unordered_map<K, V> returnMap;
		K key;

		std::unordered_map<K, V>::iterator iter;
		for (iter = inputMap2.begin() ; iter != inputMap2.end() ; ++iter)
		{
			key = iter->first;

			if (inputMap1.find(key) != inputMap1.end())
				returnMap[key] = iter->second + inputMap1[key];
			else
				returnMap[key] = iter->second;
		}

		return returnMap;
	}

};