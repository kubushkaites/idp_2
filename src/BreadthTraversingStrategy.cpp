#include "pch.h"
#include "BreadthTraversingStrategy.h"

BreadthTraversingStrategy::BreadthTraversingStrategy(SearchGoalStrategySharedPtr searchGoalStrategy, ScanningProgressObserverSharedPtr scanningProgressObserver)
	: searchGoalStrategy(searchGoalStrategy),
	scanningProgressObserver(scanningProgressObserver)
{

}

void BreadthTraversingStrategy::traverse(const std::wstring & traverseDir)
{
	std::wcout << L"Current traverse path: " << traverseDir << std::endl;

	auto nextSearchDir = traverseDir;
	auto nextSearchDirWithWildCard = nextSearchDir + L"*";

	std::list<std::wstring> subDirsList;

	auto continueSearch = true;
	do
	{
		DWORD directorySize = 0;
		WIN32_FIND_DATA FindFileData;
		HANDLE hFind;
		hFind = FindFirstFileEx(nextSearchDirWithWildCard.c_str(), FindExInfoStandard, &FindFileData,
			FindExSearchNameMatch, NULL, FIND_FIRST_EX_LARGE_FETCH);
		if (hFind != INVALID_HANDLE_VALUE)
		{
			do
			{
				if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
				{
					auto fileSize = (FindFileData.nFileSizeHigh * (MAXDWORD + 1)) + FindFileData.nFileSizeLow;
					directorySize += fileSize;
					std::wcout << "Found file: " << FindFileData.cFileName << std::endl;
					auto fileSystemObject = FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::File, nextSearchDir, FindFileData.cFileName, fileSize));
					fileSystemObjects.emplace_back(fileSystemObject);
					/*searchGoalStrategy->performSearchGoalAction(fileSystemObject);*/
				}
				else
				{
					if ((wcscmp(FindFileData.cFileName, L".") != 0) && (wcscmp(FindFileData.cFileName, L"..") != 0))
					{
						std::wcout << "Found dir: " << FindFileData.cFileName << std::endl;
						subDirsList.emplace_back(nextSearchDir + FindFileData.cFileName + L"\\");
					}
				}
			} while (FindNextFile(hFind, &FindFileData));
		}
		else
		{
			std::cout << "FindFirstFileEx failed " << GetLastError() << std::endl;
			return;
		}
		
		std::wcout << L"Directory \"" << nextSearchDir << L"\"size (bytes): " << directorySize << std::endl;
		auto fileSystemObject = FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::Directory, nextSearchDir, nextSearchDir, directorySize));
		fileSystemObjects.emplace_back(fileSystemObject);
		/*searchGoalStrategy->performSearchGoalAction(fileSystemObject);*/

		if (subDirsList.size() != 0)
		{			
			nextSearchDir = subDirsList.front();
			nextSearchDirWithWildCard = nextSearchDir + L"*";
			std::wcout << L"-------------" << std::endl << L"Moving to next dir: " << nextSearchDir << std::endl << "-------------" << std::endl;
			subDirsList.pop_front();
		}
		else
		{
			continueSearch = false;
		}
		FindClose(hFind);
	} while (continueSearch);
	searchGoalStrategy->performSearchGoalAction(fileSystemObjects);
}
