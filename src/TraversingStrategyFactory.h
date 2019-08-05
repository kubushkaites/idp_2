#pragma once
#include "pch.h"
#include "ScannerArgumentsProvider.h"
#include "ITraversingStrategy.h"
#include "ISearchGoalStrategy.h"
#include "IScanningProgressObserver.h"

class TraversingStrategyFactory
{
public:
	static TraversingStrategySharedPtr createTraversingStrategy(ScanningProgressObserverSharedPtr scanningProgressObserver, const ParsedArguments& parsedArguments);
};