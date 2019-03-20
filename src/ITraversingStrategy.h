#pragma once
#include "pch.h"

class ITraversingStrategy;

using TraversingStrategySharedPtr = std::shared_ptr<ITraversingStrategy>;

class ITraversingStrategy
{
public:
	virtual void traverse(const std::wstring& nextDir) = 0;
	virtual ~ITraversingStrategy() {}
};

