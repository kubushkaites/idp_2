#pragma once
#include "ISearchGoalStrategy.h"
#include "IScanningProgressObserver.h"


class FindFilesByExtensionStrategy : public ISearchGoalStrategy
{
public:
	FindFilesByExtensionStrategy(std::wstring fileExtension, ScanningProgressObserverSharedPtr scanningProgressObserver);
	virtual const std::tuple<SearchGoal, const std::list<FileSystemObjectSharedPtr>&> performSearchGoalAction(const std::list<FileSystemObjectSharedPtr>& fileSystemObjects) override;
private:
	std::wstring fileExtension;
	ScanningProgressObserverSharedPtr scanningProgressObserver;
	std::list<FileSystemObjectSharedPtr> searchGoalFsObjects;
};