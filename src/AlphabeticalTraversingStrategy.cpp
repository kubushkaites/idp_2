#include "pch.h"
#include "AlphabeticalTraversingStrategy.h"

AlphabeticalTraversingStrategy::AlphabeticalTraversingStrategy(SearchGoalStrategySharedPtr searchGoalStrategy, ScanningProgressObserverSharedPtr scanningProgressObserver)
	: searchGoalStrategy(searchGoalStrategy),
	scanningProgressObserver(scanningProgressObserver)
{
}

void AlphabeticalTraversingStrategy::traverse(const std::wstring & traverseDir)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	std::wcout << L"Current traverse path: " << traverseDir << std::endl;

	auto currentTraverseDir = traverseDir + L"*";
	hFind = FindFirstFileEx(currentTraverseDir.c_str(), FindExInfoStandard, &FindFileData,
		FindExSearchNameMatch, NULL, FIND_FIRST_EX_LARGE_FETCH);

	DWORD directorySize = 0;

	std::list<std::wstring> subDirsList;

	if (hFind != INVALID_HANDLE_VALUE)
	{
		std::wcout << L"The first file found is: " << FindFileData.cFileName << std::endl;
		do {
			if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
			{
				auto fileSize = (FindFileData.nFileSizeHigh * (MAXDWORD + 1)) + FindFileData.nFileSizeLow;
				directorySize += fileSize;
				std::wcout << "Found file: " << FindFileData.cFileName << std::endl;
				auto fileSystemObject = FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::File, traverseDir, FindFileData.cFileName, fileSize));
				searchGoalStrategy->performSearchGoalAction(fileSystemObject);
			}
			else
			{
				if ((wcscmp(FindFileData.cFileName, L".") != 0) && (wcscmp(FindFileData.cFileName, L"..") != 0))
				{
					std::wcout << "Found dir: " << FindFileData.cFileName << std::endl;
					subDirsList.emplace_back(traverseDir + FindFileData.cFileName + L"\\");
				}
			}
		} while (FindNextFile(hFind, &FindFileData));
		std::cout << "Directory size (bytes): " << directorySize << std::endl;
		auto fileSystemObject = FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::Directory, traverseDir, traverseDir, directorySize));
		searchGoalStrategy->performSearchGoalAction(fileSystemObject);
		while (subDirsList.size() != 0)
		{
			subDirsList.sort();
			auto front = subDirsList.front();
			std::wcout << L"-------------" << std::endl << L"Moving to next dir: " << front << std::endl << "-------------" << std::endl;
			subDirsList.pop_front();
			traverse(front);
		}
	}
	else
	{
		std::cout << "FindFirstFileEx failed " << GetLastError() << std::endl;
		return;
	}
	FindClose(hFind);
}
