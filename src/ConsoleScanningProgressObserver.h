#pragma once
#include "IScanningProgressObserver.h"

class ConsoleScanningProgressObserver: public IScanningProgressObserver
{
public:
	virtual void onScanningProgress(const std::wstring& currentlyScanningDirectory, const std::wstring& currentlyScanningFileSystemObject) override;
	virtual void onScanningResult(SearchGoal searchGoal, const std::list<FileSystemObject>& objectsMatchingToChosenSearchGoal) override;
	virtual ~ConsoleScanningProgressObserver() {};
};