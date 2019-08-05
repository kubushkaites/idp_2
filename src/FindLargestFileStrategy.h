#pragma once
#include "ISearchGoalStrategy.h"
#include "IScanningProgressObserver.h"


class FindLargestFileStrategy : public ISearchGoalStrategy
{
public:
	FindLargestFileStrategy(ScanningProgressObserverSharedPtr scanningProgressObserver);
	virtual const std::tuple<SearchGoal, const std::list<FileSystemObjectSharedPtr>&> performSearchGoalAction(const std::list<FileSystemObjectSharedPtr>& fileSystemObjects) override;
private:
	ScanningProgressObserverSharedPtr scanningProgressObserver;
	std::list<FileSystemObjectSharedPtr> searchGoalFsObjects;
};