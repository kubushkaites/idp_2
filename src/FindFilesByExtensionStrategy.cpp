#include "pch.h"
#include "FindFilesByExtensionStrategy.h"

FindFilesByExtensionStrategy::FindFilesByExtensionStrategy(std::wstring fileExtension, ScanningProgressObserverSharedPtr scanningProgressObserver)
	:fileExtension(fileExtension),
	scanningProgressObserver(scanningProgressObserver)
{
}

const std::tuple<SearchGoal, const std::list<FileSystemObjectSharedPtr>&> FindFilesByExtensionStrategy::performSearchGoalAction(const std::list<FileSystemObjectSharedPtr>& fileSystemObjects)
{
	for (auto& fsObject : fileSystemObjects)
	{
		if (fsObject->getFileSystemObjectType() == FileSystemObjectType::File && fsObject->getFileSystemObjectName().rfind(fileExtension) != std::wstring::npos)
		{
			searchGoalFsObjects.push_back(fsObject);
		}
	}
	return std::tuple<SearchGoal, const std::list<FileSystemObjectSharedPtr>&>(SearchGoal::FIND_FILES_BY_EXTENSION, searchGoalFsObjects);
}
