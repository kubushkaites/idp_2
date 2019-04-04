#pragma once
#include "pch.h"

enum class TraverseMode { BREADTH, DEPTH};

enum class SearchGoal { FIND_LARGEST_FOLDERS, FIND_LARGEST_FILE, FIND_FILES_BY_EXTENSION, DELETE_FILE };

namespace ScannerArgumentsProviderConstants 
{
	static const std::wstring traverseMode = L"traverseMode";
	static const std::wstring searchGoal = L"searchGoal";
	static const std::wstring traversingStartPath = L"traversingStartPath";
	static const std::wstring amountOfFoldersToFind = L"amountOfObjectsToFind";
	static const std::wstring searchFileExtension = L"searchFileExtension";
	static const std::wstring fileToRemoveName = L"fileToRemoveName";

	static const std::wstring breadthTraverseMode = L"BREADTH";
	static const std::wstring depthTraverseMode = L"DEPTH";

	static const std::wstring findLargestFoldersGoal = L"FIND_LARGEST_FOLDERS";
	static const std::wstring findLargestFileGoal = L"FIND_LARGEST_FILE";
	static const std::wstring findFilesByExtensionGoal = L"FIND_FILES_BY_EXTENSION";
	static const std::wstring deleteFileGoal = L"DELETE_FILE";
}

class ScannerArgumentsProvider
{
public:
	static ScannerArgumentsProvider& Instance();
	void parseArguments(std::map<std::wstring, std::wstring>&& arguments);
	TraverseMode getTraverseMode() const;
	SearchGoal getSearchGoal() const;
	std::wstring getStartSearchPath() const;
	std::wstring getFileToRemoveName() const;
	std::wstring getSearchFileExtension() const;
	int getAmountOfObjectsToFind() const;
private:
	ScannerArgumentsProvider() {};
private:
	TraverseMode traverseMode;
	SearchGoal searchGoal;
	std::map<std::wstring, TraverseMode> traverseModesMatches = {{ScannerArgumentsProviderConstants::breadthTraverseMode, TraverseMode::BREADTH}, 
																{ScannerArgumentsProviderConstants::depthTraverseMode, TraverseMode::DEPTH}};
	std::map<std::wstring, SearchGoal> searchGoalMatches = {{ScannerArgumentsProviderConstants::findLargestFoldersGoal, SearchGoal::FIND_LARGEST_FOLDERS}, 
															{ScannerArgumentsProviderConstants::findLargestFileGoal, SearchGoal::FIND_LARGEST_FILE},
															{ScannerArgumentsProviderConstants::findFilesByExtensionGoal, SearchGoal::FIND_FILES_BY_EXTENSION}, 
															{ScannerArgumentsProviderConstants::deleteFileGoal, SearchGoal::DELETE_FILE}};
	
	std::wstring traversingStartPath;

	std::wstring searchFileExtension;
	std::wstring fileToRemoveName;

	int amountOfFoldersToFind;
};
