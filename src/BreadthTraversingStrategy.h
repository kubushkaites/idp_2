#pragma once
#include "ITraversingStrategy.h"
#include "ISearchGoalStrategy.h"
#include "IScanningProgressObserver.h"

class BreadthTraversingStrategy : public ITraversingStrategy
{
public:
	BreadthTraversingStrategy(SearchGoalStrategySharedPtr searchGoalStrategy, ScanningProgressObserverSharedPtr scanningProgressObserver);
	virtual void traverse(const std::wstring& traverseDir) override;
private:
	std::list<FileSystemObjectSharedPtr> fileSystemObjects;
	SearchGoalStrategySharedPtr searchGoalStrategy;
	ScanningProgressObserverSharedPtr scanningProgressObserver;
};