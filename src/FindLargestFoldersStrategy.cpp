#include "pch.h"
#include "FindLargestFoldersStrategy.h"
#include "FileSystemObject.h"

FindLargestFoldersStrategy::FindLargestFoldersStrategy(const int amountOfFoldersToFind, ScanningProgressObserverSharedPtr scanningProgressObserver)
	: amountOfFoldersToFind(amountOfFoldersToFind),
	foundDirectories(amountOfFoldersToFind),
	scanningProgressObserver(scanningProgressObserver)
{
}

void FindLargestFoldersStrategy::performSearchGoalAction(const std::list<FileSystemObjectSharedPtr>& fileSystemObjects)
{
	for (auto& fileSystemObject : fileSystemObjects)
	{
		if (fileSystemObject->getFileSystemObjectType() == FileSystemObjectType::Directory)
		{
			auto it = std::find_if(foundDirectories.begin(), foundDirectories.end(), [fileSystemObject](FileSystemObjectSharedPtr& fsObject)
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

			if (it != foundDirectories.end())
			{				
				if (*it != nullptr) 
				{
					foundDirectories.insert(it, fileSystemObject);
					foundDirectories.pop_back();
				}
				else 
				{
					*it = fileSystemObject;
				}
			}
		}
	}
	scanningProgressObserver->onScanningResult(SearchGoal::FIND_LARGEST_FOLDERS, foundDirectories);
}
