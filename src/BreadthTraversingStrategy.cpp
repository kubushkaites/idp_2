#include "pch.h"
#include "BreadthTraversingStrategy.h"

BreadthTraversingStrategy::BreadthTraversingStrategy(SearchGoalStrategySharedPtr searchGoalStrategy, ScanningProgressObserverSharedPtr scanningProgressObserver, const std::wstring & traversingStartPath)
	: searchGoalStrategy(searchGoalStrategy),
	  scanningProgressObserver(scanningProgressObserver),
      traversingStartPath(traversingStartPath)
{

}

void BreadthTraversingStrategy::traverse(const std::wstring & nextDir)
{

}
