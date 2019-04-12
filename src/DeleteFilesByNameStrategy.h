#pragma once
#include "ISearchGoalStrategy.h"
#include "IScanningProgressObserver.h"

class DeleteFilesByNameStrategy : public ISearchGoalStrategy
{
public:
	DeleteFilesByNameStrategy(std::wstring fileNameToDelete, ScanningProgressObserverSharedPtr scanningProgressObserver);
	virtual void performSearchGoalAction(const std::list<FileSystemObjectSharedPtr>& fileSystemObjects) override;
private:
	std::wstring fileNameToDelete;
	ScanningProgressObserverSharedPtr scanningProgressObserver;
};

