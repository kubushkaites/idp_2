#pragma once
#include "ITraversingStrategy.h"
#include "ISearchGoalStrategy.h"
#include "IScanningProgressObserver.h"

class DepthTraversingStrategy : public ITraversingStrategy
{
public:
	DepthTraversingStrategy(ScanningProgressObserverSharedPtr scanningProgressObserver);
	virtual const std::tuple<bool, const std::list<FileSystemObjectSharedPtr>&> traverse(const std::wstring& traverseDir) override;
private:
	std::wstring initialTraversingDir;
	std::list<FileSystemObjectSharedPtr> fileSystemObjects;
	ScanningProgressObserverSharedPtr scanningProgressObserver;
};
