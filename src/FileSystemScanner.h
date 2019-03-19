#pragma once
#include "pch.h"
#include "ScannerArgumentsProvider.h"
#include "TraversingStrategyFactory.h"
#include "SearchGoalStrategyFactory.h"

class FileSystemScanner
{
public:
	FileSystemScanner(ScanningProgressObserverSharedPtr scanningProgressObserver);
	void Scan();
private:
	TraversingStrategySharedPtr traversingStrategy;
	SearchGoalStrategySharedPtr searchGoalStrategy;
};


