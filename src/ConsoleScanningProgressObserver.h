#pragma once
#include "IScanningProgressObserver.h"

class ConsoleScanningProgressObserver: public IScanningProgressObserver
{
private:
	void onLargestFoldersFound(std::any largestFolders);
	void onLargestFileFound(std::any largestFile);
	void onFilesByExtensionFound(std::any filesByExtension);
	void onDeletedFilesByName(std::any deletedFilesByName);
	void printFileSystemObjectInfo(FileSystemObjectSharedPtr fsObject);
public:
	virtual void onScanningProgress(const std::wstring& message) override;
	virtual void onScanningErrorOccurred(const std::wstring& errorMessage) override;
	virtual void onScanningResult(SearchGoal searchGoal, std::any objectsMatchingToChosenSearchGoal) override;
	virtual ~ConsoleScanningProgressObserver() {};
};