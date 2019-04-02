#include "pch.h"
#include "ScannerArgumentsProvider.h"
#include "SearchGoalStrategyFactory.h"
#include "FindLargestFoldersStrategy.h"
#include "FindLargestFileStrategy.h"
#include "DeleteFilesByNameStrategy.h"
#include "FindFilesByExtensionStrategy.h"

SearchGoalStrategySharedPtr SearchGoalStrategyFactory::createSearchGoalStrategy(ScanningProgressObserverSharedPtr scanningProgressObserver)
{
	SearchGoalStrategySharedPtr searchGoalStrategy;
	auto scannerArgumentsProvider = ScannerArgumentsProvider::Instance();
	switch (scannerArgumentsProvider.getSearchGoal())
	{
		case SearchGoal::FIND_LARGEST_FOLDERS:
		{
			searchGoalStrategy = SearchGoalStrategySharedPtr(new FindLargestFoldersStrategy(scannerArgumentsProvider.getAmountOfObjectsToFind(), scanningProgressObserver));
			break;
		}
		case SearchGoal::FIND_LARGEST_FILE:
		{
			searchGoalStrategy = SearchGoalStrategySharedPtr(new FindLargestFileStrategy(scanningProgressObserver));
			break;
		}
		case SearchGoal::FIND_FILES_BY_EXTENSION:
		{
			searchGoalStrategy = SearchGoalStrategySharedPtr(new FindFilesByExtensionStrategy(scannerArgumentsProvider.getSearchFileExtension(), scanningProgressObserver));
			break;
		}
		case SearchGoal::DELETE_FILE:
		{
			searchGoalStrategy = SearchGoalStrategySharedPtr(new DeleteFilesByNameStrategy(scannerArgumentsProvider.getFileToRemoveName(), scanningProgressObserver));
			break;
		}
		default:
		{
			break;
		}
	}
	return searchGoalStrategy;
}
