#pragma once
#include "ITraversingStrategy.h"
#include "ISearchGoalStrategy.h"
#include "IScanningProgressObserver.h"

class BreadthTraversingStrategy : public ITraversingStrategy
{
public:
	BreadthTraversingStrategy(SearchGoalStrategySharedPtr searchGoalStrategy, ScanningProgressObserverSharedPtr scanningProgressObserver, const std::wstring& traversingStartPath);
	virtual void traverse(const std::wstring& nextDir) override;
	virtual ~BreadthTraversingStrategy() {};
private:
	SearchGoalStrategySharedPtr searchGoalStrategy;
	ScanningProgressObserverSharedPtr scanningProgressObserver;
	std::wstring traversingStartPath;
};