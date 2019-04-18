#include "pch.h"
#include "ScannerArgumentsProvider.h"
#include "TraversingStrategyFactory.h"
#include "ISearchGoalStrategy.h"
#include "BreadthTraversingStrategy.h"
#include "DepthTraversingStrategy.h"

TraversingStrategySharedPtr TraversingStrategyFactory::createTraversingStrategy(SearchGoalStrategySharedPtr searchGoalStrategy, ScanningProgressObserverSharedPtr scanningProgressObserver, const ParsedArguments& parsedArguments)
{
	TraversingStrategySharedPtr traversingStrategy;
	switch (parsedArguments.traverseMode)
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
