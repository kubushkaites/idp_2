#pragma once
#include "ISearchGoalStrategy.h"
#include "IScanningProgressObserver.h"

class FindLargestFoldersStrategy : public ISearchGoalStrategy
{
public:
	FindLargestFoldersStrategy(const int amountOfFoldersToFind, ScanningProgressObserverSharedPtr scanningProgressObserver);
	virtual const std::tuple<SearchGoal, const std::list<FileSystemObjectSharedPtr>&> performSearchGoalAction(const std::list<FileSystemObjectSharedPtr>& fileSystemObjects) override;
private:
	int amountOfFoldersToFind = 0;
	bool foundDirectoriesSorted = false;
	std::list<FileSystemObjectSharedPtr> searchGoalFsObjects;
	ScanningProgressObserverSharedPtr scanningProgressObserver;
};
