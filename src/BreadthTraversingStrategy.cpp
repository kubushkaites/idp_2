#include "pch.h"
#include "BreadthTraversingStrategy.h"

BreadthTraversingStrategy::BreadthTraversingStrategy(SearchGoalStrategySharedPtr searchGoalStrategy, ScanningProgressObserverSharedPtr scanningProgressObserver, const std::wstring & traversingStartPath)
	: searchGoalStrategy(searchGoalStrategy),
	  scanningProgressObserver(scanningProgressObserver),
      traversingStartPath(traversingStartPath)
{

}

void BreadthTraversingStrategy::traverse(const std::wstring & nextDir)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	std::wcout << L"Current traverse path: " << nextDir << std::endl;

	auto currentSearchDir = nextDir + L"*";
	hFind = FindFirstFileEx(currentSearchDir.c_str(), FindExInfoStandard, &FindFileData,
		FindExSearchNameMatch, NULL, FIND_FIRST_EX_LARGE_FETCH);

	DWORD directorySize = 0;

	std::list<std::wstring> subDirsList;

	if (hFind != INVALID_HANDLE_VALUE)
	{
		std::wcout << L"The first file found is: " << FindFileData.cFileName << std::endl;
		do {
			if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
			{
				directorySize += (FindFileData.nFileSizeHigh * (MAXDWORD + 1)) + FindFileData.nFileSizeLow;
				std::wcout << "Found file: " << FindFileData.cFileName << std::endl;
			}
			else
			{
				if ((wcscmp(FindFileData.cFileName, L".") != 0) && (wcscmp(FindFileData.cFileName, L"..") != 0))
				{
					std::wcout << "Found dir: " << FindFileData.cFileName << std::endl;
					subDirsList.emplace_back(nextDir + FindFileData.cFileName + L"\\");
				}
			}
		} while (FindNextFile(hFind, &FindFileData));
		std::cout << "Directory size (bytes): " << directorySize << std::endl;
		auto fileSystemObject = FileSystemObjectSharedPtr(new FileSystemObject(nextDir, nextDir, directorySize));
		searchGoalStrategy->performSearchGoalAction(fileSystemObject);
		while (subDirsList.size() != 0)
		{
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
