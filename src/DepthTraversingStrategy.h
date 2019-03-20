#pragma once
#include "ITraversingStrategy.h"
#include "ISearchGoalStrategy.h"
#include "IScanningProgressObserver.h"

class DepthTraversingStrategy : public ITraversingStrategy
{
public:
	DepthTraversingStrategy(SearchGoalStrategySharedPtr searchGoalStrategy, ScanningProgressObserverSharedPtr scanningProgressObserver);
	virtual void traverse(const std::wstring& traverseDir) override;
	virtual ~DepthTraversingStrategy() {};
private:
	SearchGoalStrategySharedPtr searchGoalStrategy;
	ScanningProgressObserverSharedPtr scanningProgressObserver;
};
