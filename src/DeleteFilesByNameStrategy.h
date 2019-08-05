#pragma once
#include "ISearchGoalStrategy.h"
#include "IScanningProgressObserver.h"

class DeleteFilesByNameStrategy : public ISearchGoalStrategy
{
public:
	DeleteFilesByNameStrategy(std::wstring fileNameToDelete, ScanningProgressObserverSharedPtr scanningProgressObserver);
	virtual const std::tuple<SearchGoal, const std::list<FileSystemObjectSharedPtr>&> performSearchGoalAction(const std::list<FileSystemObjectSharedPtr>& fileSystemObjects) override;
private:
	std::wstring fileNameToDelete;
	ScanningProgressObserverSharedPtr scanningProgressObserver;
	std::list<FileSystemObjectSharedPtr> searchGoalFsObjects;
};

