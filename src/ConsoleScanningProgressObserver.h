#pragma once
#include "IScanningProgressObserver.h"

class ConsoleScanningProgressObserver: public IScanningProgressObserver
{
public:
	virtual void onScanningProgress(const std::wstring& currentlyScanningDirectory, const std::wstring& currentlyScanningFileSystemObject) override;
	virtual void onScanningResult(SearchGoal searchGoal, /*FileSystemObjectsCollection objectsMatchingToChosenSearchGoal*/ std::any objectsMatchingToChosenSearchGoal) override;
	virtual ~ConsoleScanningProgressObserver() {};
};