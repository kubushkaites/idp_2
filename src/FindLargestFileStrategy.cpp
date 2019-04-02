#include "pch.h"
#include "FindLargestFileStrategy.h"

FindLargestFileStrategy::FindLargestFileStrategy(ScanningProgressObserverSharedPtr scanningProgressObserver)
	:scanningProgressObserver(scanningProgressObserver)
{
}

void FindLargestFileStrategy::performSearchGoalAction(const std::list<FileSystemObjectSharedPtr>& fileSystemObjects)
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
	scanningProgressObserver->onScanningResult(SearchGoal::FIND_LARGEST_FILE, largestFile);
}
