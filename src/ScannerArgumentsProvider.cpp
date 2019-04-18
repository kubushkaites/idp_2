#include "pch.h"
#include "ScannerArgumentsProvider.h"

void ScannerArgumentsProvider::parseArguments(std::map<std::wstring, std::variant<std::wstring, TraverseMode, SearchGoal>>&& arguments)
{
	parsedArguments.traverseMode = std::get<TraverseMode>(arguments.at(ScannerArgumentsProviderConstants::traverseMode));
	parsedArguments.searchGoal = std::get<SearchGoal>(arguments.at(ScannerArgumentsProviderConstants::searchGoal));
	parsedArguments.traversingStartPath = std::get<std::wstring>(arguments.at(ScannerArgumentsProviderConstants::traversingStartPath));
	
	const wchar_t trailingSlash = L'\\';
	if (parsedArguments.traversingStartPath[parsedArguments.traversingStartPath.size() - 1] != trailingSlash)
	{
		parsedArguments.traversingStartPath += trailingSlash;
	}

	if (parsedArguments.searchGoal == SearchGoal::FIND_LARGEST_FOLDERS)
	{
		parsedArguments.amountOfFoldersToFind = std::stoi(std::get<std::wstring>(arguments.at(ScannerArgumentsProviderConstants::amountOfFoldersToFind)));
	}
	else if (parsedArguments.searchGoal == SearchGoal::FIND_FILES_BY_EXTENSION)
	{
		parsedArguments.searchFileExtension = std::get<std::wstring>(arguments.at(ScannerArgumentsProviderConstants::searchFileExtension));
	}
	else if (parsedArguments.searchGoal == SearchGoal::DELETE_FILE)
	{
		parsedArguments.fileToRemoveName = std::get<std::wstring>(arguments.at(ScannerArgumentsProviderConstants::fileToRemoveName));
	}
}

const ParsedArguments & ScannerArgumentsProvider::getParsedArguments() const
{
	return parsedArguments;
}
