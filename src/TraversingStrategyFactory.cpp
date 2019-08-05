#include "pch.h"
#include "ScannerArgumentsProvider.h"
#include "TraversingStrategyFactory.h"
#include "ISearchGoalStrategy.h"
#include "BreadthTraversingStrategy.h"
#include "DepthTraversingStrategy.h"

TraversingStrategySharedPtr TraversingStrategyFactory::createTraversingStrategy(ScanningProgressObserverSharedPtr scanningProgressObserver, const ParsedArguments& parsedArguments)
{
	TraversingStrategySharedPtr traversingStrategy;
	switch (parsedArguments.traverseMode)
	{
		case TraverseMode::BREADTH:
		{
			traversingStrategy = TraversingStrategySharedPtr(new BreadthTraversingStrategy(scanningProgressObserver));
			break;
		}
		case TraverseMode::DEPTH:
		{
			traversingStrategy = TraversingStrategySharedPtr(new DepthTraversingStrategy(scanningProgressObserver));
			break;
		}
		default:
		{
			break;
		}
	}
	return traversingStrategy;
}
