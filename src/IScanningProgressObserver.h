#pragma once
#include "pch.h"
#include "ScannerArgumentsProvider.h"
#include "FileSystemObject.h"

class IScanningProgressObserver;

using ScanningProgressObserverSharedPtr = std::shared_ptr<IScanningProgressObserver>;

class IScanningProgressObserver
{
public:
	virtual void onScanningProgress(const std::wstring& message) = 0;
	virtual void onScanningErrorOccurred(const std::wstring& errorMessage) = 0;
	virtual void onScanningResult(SearchGoal searchGoal, const std::list<FileSystemObjectSharedPtr>& objectsMatchingToChosenSearchGoal) = 0;
	virtual ~IScanningProgressObserver() {};
};