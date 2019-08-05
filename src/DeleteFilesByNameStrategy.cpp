#include "pch.h"
#include "DeleteFilesByNameStrategy.h"


DeleteFilesByNameStrategy::DeleteFilesByNameStrategy(std::wstring fileNameToDelete, ScanningProgressObserverSharedPtr scanningProgressObserver)
	:fileNameToDelete(fileNameToDelete),
	scanningProgressObserver(scanningProgressObserver)
{
}

const std::tuple<SearchGoal, const std::list<FileSystemObjectSharedPtr>&> DeleteFilesByNameStrategy::performSearchGoalAction(const std::list<FileSystemObjectSharedPtr>& fileSystemObjects)
{
	for (auto& fsObject : fileSystemObjects)
	{
		if (fsObject->getFileSystemObjectType() == FileSystemObjectType::File && fsObject->getFileSystemObjectName() == fileNameToDelete)
		{
			auto fileNameWithPath = fsObject->getFileSystemObjectPath() + fsObject->getFileSystemObjectName();
			if (DeleteFile(fileNameWithPath.c_str()))
			{
				searchGoalFsObjects.push_back(fsObject);
			}
			else
			{
				std::wstring errorMessage = L"Error occurred while deleting file \"" + fileNameWithPath + L"\"; errorCode: " + std::to_wstring(GetLastError());
				scanningProgressObserver->onScanningErrorOccurred(errorMessage);
			}
		}
	}
	return std::tuple<SearchGoal, const std::list<FileSystemObjectSharedPtr>&>(SearchGoal::DELETE_FILE, searchGoalFsObjects);
}
