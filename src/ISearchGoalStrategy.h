#pragma once
#include "pch.h"
#include "FileSystemObject.h"
#include "ScannerArgumentsProvider.h"

class ISearchGoalStrategy;

using SearchGoalStrategySharedPtr = std::shared_ptr<ISearchGoalStrategy>;

class ISearchGoalStrategy
{
public:
	virtual const std::tuple<SearchGoal, const std::list<FileSystemObjectSharedPtr>&> performSearchGoalAction(const std::list<FileSystemObjectSharedPtr>& fileSystemObjects) = 0;
	virtual ~ISearchGoalStrategy() {};
};

