#include "pch.h"
#include "FileSystemScanner.h"

FileSystemScanner::FileSystemScanner(ScanningProgressObserverSharedPtr scanningProgressObserver, const ParsedArguments& parsedArguments)
	: parsedArguments(parsedArguments),
	scanningProgressObserver(scanningProgressObserver)
{
	searchGoalStrategy = SearchGoalStrategyFactory::createSearchGoalStrategy(scanningProgressObserver, parsedArguments);
	traversingStrategy = TraversingStrategyFactory::createTraversingStrategy(scanningProgressObserver, parsedArguments);
}

void FileSystemScanner::Scan()
{
	auto traversingResult = traversingStrategy->traverse(parsedArguments.traversingStartPath);
	if (std::get<0>(traversingResult))
	{
		auto searchGoalResult = searchGoalStrategy->performSearchGoalAction(std::get<1>(traversingResult));
		scanningProgressObserver->onScanningResult(std::get<0>(searchGoalResult), std::get<1>(searchGoalResult));
	}
}
