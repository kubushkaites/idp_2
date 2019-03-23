#pragma once
#include "pch.h"
#include "FileSystemObject.h"

class ISearchGoalStrategy;

using SearchGoalStrategySharedPtr = std::shared_ptr<ISearchGoalStrategy>;

class ISearchGoalStrategy
{
public:
	virtual void performSearchGoalAction(const std::list<FileSystemObjectSharedPtr>& fileSystemObjects) = 0;
	virtual ~ISearchGoalStrategy() {};
};

