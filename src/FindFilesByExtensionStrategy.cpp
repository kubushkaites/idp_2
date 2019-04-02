#include "pch.h"
#include "FindFilesByExtensionStrategy.h"

FindFilesByExtensionStrategy::FindFilesByExtensionStrategy(std::wstring fileExtension, ScanningProgressObserverSharedPtr scanningProgressObserver)
	:fileExtension(fileExtension),
	scanningProgressObserver(scanningProgressObserver)
{
}

void FindFilesByExtensionStrategy::performSearchGoalAction(const std::list<FileSystemObjectSharedPtr>& fileSystemObjects)
{
	std::list<FileSystemObjectSharedPtr> files;
	for (auto& fsObject : fileSystemObjects)
	{
		if (fsObject->getFileSystemObjectType() == FileSystemObjectType::File && fsObject->getFileSystemObjectName().rfind(fileExtension) != std::wstring::npos)
		{
			files.push_back(fsObject);
		}
	}
	scanningProgressObserver->onScanningResult(SearchGoal::FIND_FILES_BY_EXTENSION, files);
}
