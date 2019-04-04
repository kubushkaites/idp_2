#include "pch.h"
#include "BreadthTraversingStrategy.h"

BreadthTraversingStrategy::BreadthTraversingStrategy(SearchGoalStrategySharedPtr searchGoalStrategy, ScanningProgressObserverSharedPtr scanningProgressObserver)
	: searchGoalStrategy(searchGoalStrategy),
	scanningProgressObserver(scanningProgressObserver)
{

}

void BreadthTraversingStrategy::traverse(const std::wstring & traverseDir)
{
	std::wstringstream logStream;
	logStream << L"Current traverse path: " + traverseDir;
	scanningProgressObserver->onScanningProgress(L"Current traverse path: " + traverseDir);

	auto nextSearchPath = traverseDir;
	auto nextSearchPathWithWildCard = nextSearchPath + L"*";

	std::list<std::wstring> subDirsList;

	auto continueSearch = true;
	do
	{
		DWORD directorySize = 0;
		WIN32_FIND_DATA FindFileData;
		HANDLE hFind;
		hFind = FindFirstFileEx(nextSearchPathWithWildCard.c_str(), FindExInfoStandard, &FindFileData,
			FindExSearchNameMatch, NULL, FIND_FIRST_EX_LARGE_FETCH);
		if (hFind != INVALID_HANDLE_VALUE)
		{
			do
			{
				if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
				{
					auto fileSize = (FindFileData.nFileSizeHigh * (MAXDWORD + 1)) + FindFileData.nFileSizeLow;
					directorySize += fileSize;
					{
						logStream.str(L"");
						logStream << L"Found file: " << FindFileData.cFileName << std::endl;
						scanningProgressObserver->onScanningProgress(logStream.str());
					}
					auto fileSystemObject = FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::File, nextSearchPath, FindFileData.cFileName, fileSize));
					fileSystemObjects.emplace_back(fileSystemObject);
				}
				else
				{
					if ((wcscmp(FindFileData.cFileName, L".") != 0) && (wcscmp(FindFileData.cFileName, L"..") != 0))
					{
						logStream.str(L"");
						logStream << "Found dir: " << FindFileData.cFileName <<std::endl;
						scanningProgressObserver->onScanningProgress(logStream.str());
						subDirsList.emplace_back(nextSearchPath + FindFileData.cFileName + L"\\");
					}
				}
			} while (FindNextFile(hFind, &FindFileData));
		}
		else
		{
			logStream.str(L"");
			logStream << "FindFirstFileEx failed " << GetLastError() << std::endl;
			scanningProgressObserver->onScanningErrorOccurred(logStream.str());
			return;
		}

		logStream.str(L"");
		logStream << L"Directory \"" << nextSearchPath << L"\"size (bytes): " << directorySize << std::endl;
		scanningProgressObserver->onScanningProgress(logStream.str());

		auto fileSystemObject = FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::Directory, nextSearchPath, nextSearchPath, directorySize));
		fileSystemObjects.emplace_back(fileSystemObject);

		if (subDirsList.size() != 0)
		{
			nextSearchPath = subDirsList.front();
			nextSearchPathWithWildCard = nextSearchPath + L"*";
			logStream.str(L"");
			logStream << L"-------------" << std::endl << L"Moving to next dir: " << nextSearchPath << std::endl << "-------------" << std::endl;
			scanningProgressObserver->onScanningProgress(logStream.str());
			subDirsList.pop_front();
		}
		else
		{
			continueSearch = false;
		}
		FindClose(hFind);
	} while (continueSearch);

	logStream = std::wstringstream();
	logStream << L"Breadth traversing ended! Starting perform search goal action!" << std::endl;
	scanningProgressObserver->onScanningProgress(logStream.str());

	searchGoalStrategy->performSearchGoalAction(fileSystemObjects);
}
