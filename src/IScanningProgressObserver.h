#pragma once
#include "pch.h"
#include "ScannerArgumentsProvider.h"
#include "FileSystemObject.h"

class IScanningProgressObserver;

using ScanningProgressObserverSharedPtr = std::shared_ptr<IScanningProgressObserver>;

class IScanningProgressObserver
{
public:
	virtual void onScanningProgress(const std::wstring& currentlyScanningDirectory, const std::wstring& currentlyScanningFileSystemObject) = 0;
	virtual void onScanningResult(SearchGoal searchGoal, const std::vector<FileSystemObjectSharedPtr>& objectsMatchingToChosenSearchGoal) = 0;
	virtual ~IScanningProgressObserver() {};
};