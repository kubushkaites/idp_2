#pragma once
#include "ITraversingStrategy.h"
#include "ISearchGoalStrategy.h"
#include "IScanningProgressObserver.h"

class DepthTraversingStrategy : public ITraversingStrategy
{
public:
	DepthTraversingStrategy(SearchGoalStrategySharedPtr searchGoalStrategy, ScanningProgressObserverSharedPtr scanningProgressObserver, const std::wstring& traversingStartPath);
	virtual void traverse(const std::wstring& nextDir) override;
	virtual ~DepthTraversingStrategy() {};
private:
	SearchGoalStrategySharedPtr searchGoalStrategy;
	ScanningProgressObserverSharedPtr scanningProgressObserver;
	std::wstring traversingStartPath;
};
