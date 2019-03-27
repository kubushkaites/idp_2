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
	auto foundDirectoriesCounter = 0;
	for(auto& fileSystemObject : fileSystemObjects)
	{
		if (fileSystemObject->getFileSystemObjectType() == FileSystemObjectType::Directory)
		{
			if (foundDirectoriesCounter < amountOfFoldersToFind)
			{
				foundDirectories[foundDirectoriesCounter] = fileSystemObject;
				++foundDirectoriesCounter;
			}

			if (foundDirectoriesSorted == false && foundDirectoriesCounter == amountOfFoldersToFind)
			{
				std::sort(foundDirectories.begin(), foundDirectories.end(), [](FileSystemObjectSharedPtr& dirLeft, FileSystemObjectSharedPtr& dirRight)
				{
					return dirLeft->getFileSystemObjectSize() > dirRight->getFileSystemObjectSize();
				});
				foundDirectoriesSorted = true;
			}
			else if(foundDirectoriesSorted && foundDirectoriesCounter == amountOfFoldersToFind)
			{
				auto it = std::find_if(foundDirectories.begin(), foundDirectories.end(), [fileSystemObject](FileSystemObjectSharedPtr& fsObject)
				{
					return fileSystemObject->getFileSystemObjectSize() > fsObject->getFileSystemObjectSize();
				});
				if (it != foundDirectories.end())
				{
					*it = fileSystemObject;
					auto itIdx = it - foundDirectories.begin();
					for (auto idx = foundDirectories.size() - 1; idx > itIdx; idx--)
					{
						foundDirectories[idx] = foundDirectories[idx - 1];
					}				
				}
			}					
		}
	}
	scanningProgressObserver->onScanningResult(SearchGoal::FIND_LARGEST_FOLDERS, foundDirectories);
}
