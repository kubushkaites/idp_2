#include "pch.h"
#include "FindLargestFoldersStrategy.h"
#include "FileSystemObject.h"

FindLargestFoldersStrategy::FindLargestFoldersStrategy(const int amountOfFoldersToFind, ScanningProgressObserverSharedPtr scanningProgressObserver)
	: amountOfFoldersToFind(amountOfFoldersToFind),
	scanningProgressObserver(scanningProgressObserver)
{
}

void FindLargestFoldersStrategy::performSearchGoalAction(FileSystemObjectSharedPtr fileSystemObject)
{
}
