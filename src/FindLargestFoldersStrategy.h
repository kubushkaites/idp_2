#pragma once
#include "ISearchGoalStrategy.h"
#include "IScanningProgressObserver.h"


class FindLargestFoldersStrategy : public ISearchGoalStrategy
{
public:
	FindLargestFoldersStrategy(ScanningProgressObserverSharedPtr scanningProgressObserver);
	virtual void performSearchGoalAction(FileSystemObjectSharedPtr& fileSystemObject) override;
	virtual ~FindLargestFoldersStrategy() {};
private:
	ScanningProgressObserverSharedPtr scanningProgressObserver;
};
