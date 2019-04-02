#pragma once
#include "ISearchGoalStrategy.h"
#include "IScanningProgressObserver.h"


class FindLargestFileStrategy : public ISearchGoalStrategy
{
public:
	FindLargestFileStrategy(ScanningProgressObserverSharedPtr scanningProgressObserver);
	virtual void performSearchGoalAction(const std::list<FileSystemObjectSharedPtr>& fileSystemObjects) override;
	virtual ~FindLargestFileStrategy() {};
private:
	FileSystemObjectSharedPtr largestFile;
	ScanningProgressObserverSharedPtr scanningProgressObserver;
};