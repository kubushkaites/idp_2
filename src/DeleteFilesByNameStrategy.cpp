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
			//TODO delete file, push to deleted file and infor scannign progress observer
		}
	}
}
