#pragma once
#include "pch.h"
#include "ScannerArgumentsProvider.h"
#include "FileSystemObject.h"

class IScanningProgressObserver;

using ScanningProgressObserverSharedPtr = std::shared_ptr<IScanningProgressObserver>;
using FileSystemObjectsCollection = std::variant<const std::vector<FileSystemObjectSharedPtr>&, const std::list<FileSystemObjectSharedPtr>&>;

class IScanningProgressObserver
{
public:
	virtual void onScanningProgress(const std::wstring& currentlyScanningDirectory, const std::wstring& currentlyScanningFileSystemObject) = 0;
	virtual void onScanningResult(SearchGoal searchGoal, /*FileSystemObjectsCollection*/ std::any objectsMatchingToChosenSearchGoal) = 0;
	virtual ~IScanningProgressObserver() {};
};