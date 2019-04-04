#include "pch.h"
#include "DeleteFilesByNameStrategy.h"


DeleteFilesByNameStrategy::DeleteFilesByNameStrategy(std::wstring fileNameToDelete, ScanningProgressObserverSharedPtr scanningProgressObserver)
	:fileNameToDelete(fileNameToDelete),
	scanningProgressObserver(scanningProgressObserver)
{
}

void DeleteFilesByNameStrategy::performSearchGoalAction(const std::list<FileSystemObjectSharedPtr>& fileSystemObjects)
{
	std::list<FileSystemObjectSharedPtr> deletedFiles;
	for (auto& fsObject : fileSystemObjects)
	{
		if (fsObject->getFileSystemObjectType() == FileSystemObjectType::File && fsObject->getFileSystemObjectName() == fileNameToDelete)
		{
			auto fileNameWithPath = fsObject->getFileSystemObjectPath() + fsObject->getFileSystemObjectName();
			if (DeleteFile(fileNameWithPath.c_str()))
			{
				deletedFiles.push_back(fsObject);
			}
			else
			{
				std::wstring errorMessage = L"Error occurred while deleting file \"" + fileNameWithPath + L"\"; errorCode: " + std::to_wstring(GetLastError());
				scanningProgressObserver->onScanningErrorOccurred(errorMessage);
			}
		}
	}
	scanningProgressObserver->onScanningResult(SearchGoal::DELETE_FILE, deletedFiles);
}
