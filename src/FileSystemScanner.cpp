#include "pch.h"
#include "FileSystemScanner.h"

FileSystemScanner::FileSystemScanner(ScanningProgressObserverSharedPtr scanningProgressObserver)
{
	//auto searchGoalStrategyFactory = SearchGoalStrategyFactory();
	searchGoalStrategy = SearchGoalStrategyFactory::createSearchGoalStrategy(scanningProgressObserver);
	//auto traversingStrategyFactory = TraversingStrategyFactory();
	traversingStrategy = TraversingStrategyFactory::createTraversingStrategyFactory(searchGoalStrategy, scanningProgressObserver);
}

void FileSystemScanner::Scan()
{
	traversingStrategy->traverse(ScannerArgumentsProvider::Instance().getStartSearchPath());
}
