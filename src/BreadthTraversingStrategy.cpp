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

	auto nextDir = traverseDir;
	auto nextSearchDir = nextDir + L"*";

	std::list<std::wstring> subDirsList;

	auto continueSearch = true;
	do
	{
		DWORD directorySize = 0;
		WIN32_FIND_DATA FindFileData;
		HANDLE hFind;
		hFind = FindFirstFileEx(nextSearchDir.c_str(), FindExInfoStandard, &FindFileData,
			FindExSearchNameMatch, NULL, FIND_FIRST_EX_LARGE_FETCH);
		if (hFind != INVALID_HANDLE_VALUE)
		{
			do
			{
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
		}
		else
		{
			std::cout << "FindFirstFileEx failed " << GetLastError() << std::endl;
			return;
		}
		
		std::wcout << L"Directory \"" << nextDir << L"\"size (bytes): " << directorySize << std::endl;

		if (subDirsList.size() != 0)
		{			
			nextDir = subDirsList.front();
			nextSearchDir = nextDir + L"*";
			std::wcout << L"-------------" << std::endl << L"Moving to next dir: " << nextDir << std::endl << "-------------" << std::endl;
			subDirsList.pop_front();
		}
		else
		{
			continueSearch = false;
		}
		FindClose(hFind);
	} while (continueSearch);
}
