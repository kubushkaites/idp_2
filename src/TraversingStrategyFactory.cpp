#include "pch.h"
#include "ScannerArgumentsProvider.h"
#include "TraversingStrategyFactory.h"
#include "ISearchGoalStrategy.h"
#include "BreadthTraversingStrategy.h"
#include "DepthTraversingStrategy.h"

TraversingStrategySharedPtr TraversingStrategyFactory::createTraversingStrategy(SearchGoalStrategySharedPtr searchGoalStrategy, ScanningProgressObserverSharedPtr scanningProgressObserver)
{
	TraversingStrategySharedPtr traversingStrategy;
	auto scannerArgumentsProvider = ScannerArgumentsProvider::Instance();
	switch (scannerArgumentsProvider.getTraverseMode())
	{
		case TraverseMode::BREADTH:
		{
			traversingStrategy = TraversingStrategySharedPtr(new BreadthTraversingStrategy(searchGoalStrategy, scanningProgressObserver));
			break;
		}
		case TraverseMode::DEPTH:
		{
			traversingStrategy = TraversingStrategySharedPtr(new DepthTraversingStrategy(searchGoalStrategy, scanningProgressObserver));
			break;
		}
		default:
		{
			break;
		}
	}
	return traversingStrategy;
}
