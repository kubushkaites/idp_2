#pragma once
#include "ITraversingStrategy.h"
#include "ISearchGoalStrategy.h"
#include "IScanningProgressObserver.h"

class AlphabeticalTraversingStrategy : public ITraversingStrategy
{
public:
	AlphabeticalTraversingStrategy(SearchGoalStrategySharedPtr searchGoalStrategy, ScanningProgressObserverSharedPtr scanningProgressObserver);
	virtual void traverse(const std::wstring& traverseDir) override;
	virtual ~AlphabeticalTraversingStrategy() {};
private:
	std::list<FileSystemObjectSharedPtr> fileSystemObjects;
	SearchGoalStrategySharedPtr searchGoalStrategy;
	ScanningProgressObserverSharedPtr scanningProgressObserver;
};
