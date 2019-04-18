#include "pch.h"
#include "ScannerArgumentsProvider.h"
#include "SearchGoalStrategyFactory.h"
#include "FindLargestFoldersStrategy.h"
#include "FindLargestFileStrategy.h"
#include "DeleteFilesByNameStrategy.h"
#include "FindFilesByExtensionStrategy.h"

SearchGoalStrategySharedPtr SearchGoalStrategyFactory::createSearchGoalStrategy(ScanningProgressObserverSharedPtr scanningProgressObserver, const ParsedArguments& parsedArguments)
{
	SearchGoalStrategySharedPtr searchGoalStrategy;
	switch (parsedArguments.searchGoal)
	{
		case SearchGoal::FIND_LARGEST_FOLDERS:
		{
			searchGoalStrategy = SearchGoalStrategySharedPtr(new FindLargestFoldersStrategy(parsedArguments.amountOfFoldersToFind, scanningProgressObserver));
			break;
		}
		case SearchGoal::FIND_LARGEST_FILE:
		{
			searchGoalStrategy = SearchGoalStrategySharedPtr(new FindLargestFileStrategy(scanningProgressObserver));
			break;
		}
		case SearchGoal::FIND_FILES_BY_EXTENSION:
		{
			searchGoalStrategy = SearchGoalStrategySharedPtr(new FindFilesByExtensionStrategy(parsedArguments.searchFileExtension, scanningProgressObserver));
			break;
		}
		case SearchGoal::DELETE_FILE:
		{
			searchGoalStrategy = SearchGoalStrategySharedPtr(new DeleteFilesByNameStrategy(parsedArguments.fileToRemoveName, scanningProgressObserver));
			break;
		}
		default:
		{
			break;
		}
	}
	return searchGoalStrategy;
}
