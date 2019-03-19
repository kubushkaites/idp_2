#pragma once
#include "pch.h"
#include "ISearchGoalStrategy.h"
#include "IScanningProgressObserver.h"
#include "ScannerArgumentsProvider.h"

class SearchGoalStrategyFactory
{
public:
	static SearchGoalStrategySharedPtr createSearchGoalStrategy(ScanningProgressObserverSharedPtr scanningProgressObserver);
};