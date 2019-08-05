#include "pch.h"
#include "FindLargestFoldersStrategy.h"
#include "FileSystemObject.h"

FindLargestFoldersStrategy::FindLargestFoldersStrategy(const int amountOfFoldersToFind, ScanningProgressObserverSharedPtr scanningProgressObserver)
	: amountOfFoldersToFind(amountOfFoldersToFind),
	searchGoalFsObjects(amountOfFoldersToFind),
	scanningProgressObserver(scanningProgressObserver)
{
}

const std::tuple<SearchGoal, const std::list<FileSystemObjectSharedPtr>&> FindLargestFoldersStrategy::performSearchGoalAction(const std::list<FileSystemObjectSharedPtr>& fileSystemObjects)
{
	for (auto& fileSystemObject : fileSystemObjects)
	{
		if (fileSystemObject->getFileSystemObjectType() == FileSystemObjectType::Directory)
		{
			auto it = std::find_if(searchGoalFsObjects.begin(), searchGoalFsObjects.end(), [fileSystemObject](FileSystemObjectSharedPtr& fsObject)
			{
				auto ret = false;
				if (fsObject != nullptr)
				{
					ret =  fileSystemObject->getFileSystemObjectSize() > fsObject->getFileSystemObjectSize();
				}
				else if (fsObject == nullptr)
				{
					ret = true;
				}
				return ret;
			});

			if (it != searchGoalFsObjects.end())
			{				
				if (*it != nullptr) 
				{
					searchGoalFsObjects.insert(it, fileSystemObject);
					searchGoalFsObjects.pop_back();
				}
				else 
				{
					*it = fileSystemObject;
				}
			}
		}
	}
	return std::tuple<SearchGoal, const std::list<FileSystemObjectSharedPtr>&>(SearchGoal::FIND_LARGEST_FOLDERS, searchGoalFsObjects);
}
