#include "pch.h"
#include "FileSystemScanner.h"

FileSystemScanner::FileSystemScanner(ScanningProgressObserverSharedPtr scanningProgressObserver, const ParsedArguments& parsedArguments)
	: parsedArguments(parsedArguments)
{
	searchGoalStrategy = SearchGoalStrategyFactory::createSearchGoalStrategy(scanningProgressObserver, parsedArguments);
	traversingStrategy = TraversingStrategyFactory::createTraversingStrategy(searchGoalStrategy, scanningProgressObserver, parsedArguments);
}

void FileSystemScanner::Scan()
{
	traversingStrategy->traverse(parsedArguments.traversingStartPath);
}
