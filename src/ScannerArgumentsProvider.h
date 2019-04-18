#pragma once
#include "pch.h"

enum class TraverseMode { BREADTH, DEPTH};

enum class SearchGoal { FIND_LARGEST_FOLDERS, FIND_LARGEST_FILE, FIND_FILES_BY_EXTENSION, DELETE_FILE };

struct ParsedArguments
{
	TraverseMode traverseMode;
	SearchGoal searchGoal;
	std::wstring traversingStartPath;
	std::wstring searchFileExtension;
	std::wstring fileToRemoveName;
	int amountOfFoldersToFind;
};


namespace ScannerArgumentsProviderConstants 
{
	static const std::wstring traverseMode = L"traverseMode";
	static const std::wstring searchGoal = L"searchGoal";
	static const std::wstring traversingStartPath = L"traversingStartPath";
	static const std::wstring amountOfFoldersToFind = L"amountOfObjectsToFind";
	static const std::wstring searchFileExtension = L"searchFileExtension";
	static const std::wstring fileToRemoveName = L"fileToRemoveName";
}

class ScannerArgumentsProvider
{
public:
	void parseArguments(std::map<std::wstring, std::variant<std::wstring, TraverseMode, SearchGoal>>&& arguments);
	const ParsedArguments& getParsedArguments() const;
private:
	ParsedArguments parsedArguments;
};
