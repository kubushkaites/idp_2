#pragma once
#include "ISearchGoalStrategy.h"
#include "IScanningProgressObserver.h"


class FindFilesByExtensionStrategy : public ISearchGoalStrategy
{
public:
	FindFilesByExtensionStrategy(std::wstring fileExtension, ScanningProgressObserverSharedPtr scanningProgressObserver);
	virtual void performSearchGoalAction(const std::list<FileSystemObjectSharedPtr>& fileSystemObjects) override;
	virtual ~FindFilesByExtensionStrategy() {};
private:
	std::wstring fileExtension;
	ScanningProgressObserverSharedPtr scanningProgressObserver;
};