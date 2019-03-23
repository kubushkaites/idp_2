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
	static bool isSorted = false;
	for(auto& fileSystemObject : fileSystemObjects)
	{
		if (fileSystemObject->getFileSystemObjectType() == FileSystemObjectType::Directory)
		{
			if (foundDirectories.size() != amountOfFoldersToFind)
			{
				foundDirectories.push_back(fileSystemObject);
			}
			else
			{
				if (isSorted == false)
				{
					std::sort(foundDirectories.begin(), foundDirectories.end(),[] )
				}
			}			
		}
	}
	/*if (fileSystemObjects->getFileSystemObjectType() == FileSystemObjectType::Directory)
	{
		if (foundDirectories.size() != amountOfFoldersToFind)
		{
			foundDirectories.push_back(fileSystemObject);
		}
		else
		{	
			if (isSorted == false)
				foundDirectories.sort();
		}
	}*/
}
