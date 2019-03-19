#pragma once
#include "ISearchGoalStrategy.h"
#include "IScanningProgressObserver.h"

class FindLargestFoldersStrategy : public ISearchGoalStrategy
{
public:
	FindLargestFoldersStrategy(const int amountOfFoldersToFind, ScanningProgressObserverSharedPtr scanningProgressObserver);
	virtual void performSearchGoalAction(FileSystemObjectSharedPtr fileSystemObject) override;
	virtual ~FindLargestFoldersStrategy() {};
private:
	int amountOfFoldersToFind = 0;
	ScanningProgressObserverSharedPtr scanningProgressObserver = nullptr;
};
