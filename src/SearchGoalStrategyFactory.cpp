#include "pch.h"
#include "ScannerArgumentsProvider.h"
#include "SearchGoalStrategyFactory.h"
#include "FindLargestFoldersStrategy.h"

SearchGoalStrategySharedPtr SearchGoalStrategyFactory::createSearchGoalStrategy(ScanningProgressObserverSharedPtr scanningProgressObserver)
{
	SearchGoalStrategySharedPtr searchGoalStrategy = nullptr;
	auto scannerArgumentsProvider = ScannerArgumentsProvider::Instance();
	switch (scannerArgumentsProvider.getSearchGoal())
	{
		case SearchGoal::FIND_LARGEST_FOLDERS:
		{
			searchGoalStrategy = SearchGoalStrategySharedPtr(new FindLargestFoldersStrategy(scannerArgumentsProvider.getAmountOfObjectsToFind(), scanningProgressObserver));
			break;
		}
		default:
		{
			break;
		}
	}
	return searchGoalStrategy;
}
