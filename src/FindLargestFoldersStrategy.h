#pragma once
#include "ISearchGoalStrategy.h"
#include "IScanningProgressObserver.h"

class FindLargestFoldersStrategy : public ISearchGoalStrategy
{
public:
	FindLargestFoldersStrategy(const int amountOfFoldersToFind, ScanningProgressObserverSharedPtr scanningProgressObserver);
	virtual void performSearchGoalAction(const std::list<FileSystemObjectSharedPtr>& fileSystemObjects) override;
	virtual ~FindLargestFoldersStrategy() {};
private:
	int amountOfFoldersToFind = 0;
	bool foundDirectoriesSorted = false;
	std::vector<FileSystemObjectSharedPtr> foundDirectories;
	ScanningProgressObserverSharedPtr scanningProgressObserver;
};
