#pragma once
#include "IScanningProgressObserver.h"

class ConsoleScanningProgressObserver: public IScanningProgressObserver
{
private:
	void printFileSystemObjectInfo(FileSystemObjectSharedPtr fsObject);
public:
	virtual void onScanningProgress(const std::wstring& message) override;
	virtual void onScanningErrorOccurred(const std::wstring& errorMessage) override;
	virtual void onScanningResult(SearchGoal searchGoal, const std::list<FileSystemObjectSharedPtr>& objectsMatchingToChosenSearchGoal) override;
	virtual void onScanningResult(SearchGoal searchGoal, const FileSystemObjectSharedPtr objectMatchingToChosenSearchGoal) override;
};