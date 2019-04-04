#include "pch.h"
#include "ScannerArgumentsProvider.h"

ScannerArgumentsProvider& ScannerArgumentsProvider::Instance()
{
	static ScannerArgumentsProvider instance;
	return instance;
}

void ScannerArgumentsProvider::parseArguments(std::map<std::wstring, std::wstring>&& arguments)
{
	traverseMode = traverseModesMatches.at(arguments.at(ScannerArgumentsProviderConstants::traverseMode));
	searchGoal = searchGoalMatches.at(arguments.at(ScannerArgumentsProviderConstants::searchGoal));
	traversingStartPath = arguments.at(ScannerArgumentsProviderConstants::traversingStartPath);
	
	const wchar_t trailingSlash = L'\\';
	if (traversingStartPath[traversingStartPath.size() - 1] != trailingSlash)
	{
		traversingStartPath += trailingSlash;
	}

	if (searchGoal == SearchGoal::FIND_LARGEST_FOLDERS)
	{
		amountOfFoldersToFind = std::stoi(arguments.at(ScannerArgumentsProviderConstants::amountOfFoldersToFind));
	}
	else if (searchGoal == SearchGoal::FIND_FILES_BY_EXTENSION)
	{
		searchFileExtension = arguments.at(ScannerArgumentsProviderConstants::searchFileExtension);
	}
	else if (searchGoal == SearchGoal::DELETE_FILE)
	{
		fileToRemoveName = arguments.at(ScannerArgumentsProviderConstants::fileToRemoveName);
	}
}

TraverseMode ScannerArgumentsProvider::getTraverseMode() const
{
	return traverseMode;
}

SearchGoal ScannerArgumentsProvider::getSearchGoal() const
{
	return searchGoal;
}

std::wstring ScannerArgumentsProvider::getStartSearchPath()const
{
	return traversingStartPath;
}

std::wstring ScannerArgumentsProvider::getFileToRemoveName()const
{
	return fileToRemoveName;
}

std::wstring ScannerArgumentsProvider::getSearchFileExtension()const
{
	return searchFileExtension;
}

int ScannerArgumentsProvider::getAmountOfObjectsToFind()const
{
	return amountOfFoldersToFind;
}