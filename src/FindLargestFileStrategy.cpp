#include "pch.h"
#include "FindLargestFileStrategy.h"

FindLargestFileStrategy::FindLargestFileStrategy(ScanningProgressObserverSharedPtr scanningProgressObserver)
	:scanningProgressObserver(scanningProgressObserver)
{
}

const std::tuple<SearchGoal, const std::list<FileSystemObjectSharedPtr>&> FindLargestFileStrategy::performSearchGoalAction(const std::list<FileSystemObjectSharedPtr>& fileSystemObjects)
{
	FileSystemObjectSharedPtr largestFile = nullptr;
	for (auto& fsObject : fileSystemObjects)
	{
		if (fsObject->getFileSystemObjectType() == FileSystemObjectType::File)
		{
			if (largestFile == nullptr)
			{
				largestFile = fsObject;
			}
			else if (largestFile->getFileSystemObjectSize() < fsObject->getFileSystemObjectSize())
			{
				largestFile = fsObject;
			}
		}
	}
	searchGoalFsObjects.push_back(largestFile);
	return std::tuple<SearchGoal, const std::list<FileSystemObjectSharedPtr>&>(SearchGoal::FIND_LARGEST_FILE, searchGoalFsObjects);
}
