#pragma once
#include "ITraversingStrategy.h"
#include "ISearchGoalStrategy.h"
#include "IScanningProgressObserver.h"

class BreadthTraversingStrategy : public ITraversingStrategy
{
public:
	BreadthTraversingStrategy(ScanningProgressObserverSharedPtr scanningProgressObserver);
	virtual const std::tuple<bool, const std::list<FileSystemObjectSharedPtr>&> traverse(const std::wstring& traverseDir) override;
private:
	std::list<FileSystemObjectSharedPtr> fileSystemObjects;
	ScanningProgressObserverSharedPtr scanningProgressObserver;
};