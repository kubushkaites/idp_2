#include "pch.h"
#include "FileSystemScanner.h"

FileSystemScanner::FileSystemScanner(ScanningProgressObserverSharedPtr scanningProgressObserver)
{
	searchGoalStrategy = SearchGoalStrategyFactory::createSearchGoalStrategy(scanningProgressObserver);
	traversingStrategy = TraversingStrategyFactory::createTraversingStrategy(searchGoalStrategy, scanningProgressObserver);
}

void FileSystemScanner::Scan()
{
	traversingStrategy->traverse(ScannerArgumentsProvider::Instance().getStartSearchPath());
}
