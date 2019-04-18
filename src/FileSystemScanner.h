#pragma once
#include "pch.h"
#include "ScannerArgumentsProvider.h"
#include "TraversingStrategyFactory.h"
#include "SearchGoalStrategyFactory.h"

class FileSystemScanner
{
public:
	FileSystemScanner(ScanningProgressObserverSharedPtr scanningProgressObserver, const ParsedArguments& parsedAruments);
	void Scan();
private:
	ParsedArguments parsedArguments;
	TraversingStrategySharedPtr traversingStrategy;
	SearchGoalStrategySharedPtr searchGoalStrategy;
};


