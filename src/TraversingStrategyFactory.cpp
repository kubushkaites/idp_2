#include "pch.h"
#include "ScannerArgumentsProvider.h"
#include "TraversingStrategyFactory.h"
#include "ISearchGoalStrategy.h"
#include "BreadthTraversingStrategy.h"

TraversingStrategySharedPtr TraversingStrategyFactory::createTraversingStrategyFactory(SearchGoalStrategySharedPtr searchGoalStrategy, ScanningProgressObserverSharedPtr scanningProgressObserver)
{
	TraversingStrategySharedPtr traversingStrategy = nullptr;
	auto scannerArgumentsProvider = ScannerArgumentsProvider::Instance();
	switch (scannerArgumentsProvider.getTraverseMode())
	{
		case TraverseMode::BREADTH:
		{
			traversingStrategy = TraversingStrategySharedPtr(new BreadthTraversingStrategy(searchGoalStrategy, scanningProgressObserver, scannerArgumentsProvider.getStartSearchPath()));
			break;
		}
		default:
		{
			break;
		}
	}
	return traversingStrategy;
}
