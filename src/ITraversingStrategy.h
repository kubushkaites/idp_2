#pragma once
#include "pch.h"
#include "FileSystemObject.h"

class ITraversingStrategy;

using TraversingStrategySharedPtr = std::shared_ptr<ITraversingStrategy>;

class ITraversingStrategy
{
public:
	virtual const std::tuple<bool, const std::list<FileSystemObjectSharedPtr>&> traverse(const std::wstring& traverseDir) = 0;
	virtual ~ITraversingStrategy() {}
};

