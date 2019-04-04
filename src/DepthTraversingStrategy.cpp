#include "pch.h"
#include "DepthTraversingStrategy.h"

DepthTraversingStrategy::DepthTraversingStrategy(SearchGoalStrategySharedPtr searchGoalStrategy, ScanningProgressObserverSharedPtr scanningProgressObserver)
	: searchGoalStrategy(searchGoalStrategy),
	scanningProgressObserver(scanningProgressObserver)
{

}

void DepthTraversingStrategy::traverse(const std::wstring & traverseDir)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	if (initialTraversingDir.empty())
	{
		initialTraversingDir = traverseDir;
	}
	
	std::wstringstream logStream;
	logStream << L"Current traverse path: " << traverseDir << std::endl;
	scanningProgressObserver->onScanningProgress(logStream.str());

	auto currentTraverseDir = traverseDir + L"*";
	hFind = FindFirstFileEx(currentTraverseDir.c_str(), FindExInfoStandard, &FindFileData,
		FindExSearchNameMatch, NULL, FIND_FIRST_EX_LARGE_FETCH);

	DWORD directorySize = 0;

	std::list<std::wstring> subDirsList;

	if (hFind != INVALID_HANDLE_VALUE)
	{
		logStream.str(L"");
		logStream << L"The first file found is: " << FindFileData.cFileName << std::endl;
		scanningProgressObserver->onScanningProgress(logStream.str());

		do {
			if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
			{
				auto fileSize = (FindFileData.nFileSizeHigh * (MAXDWORD + 1)) + FindFileData.nFileSizeLow;
				directorySize += fileSize;
				
				logStream.str(L"");
				logStream << "Found file: " << FindFileData.cFileName << std::endl;
				scanningProgressObserver->onScanningProgress(logStream.str());

				auto fileSystemObject = FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::File, traverseDir, FindFileData.cFileName, fileSize));
				fileSystemObjects.emplace_back(fileSystemObject);
			}
			else
			{
				if ((wcscmp(FindFileData.cFileName, L".") != 0) && (wcscmp(FindFileData.cFileName, L"..") != 0))
				{
					logStream.str(L"");
					logStream << "Found dir: " << FindFileData.cFileName << std::endl;
					scanningProgressObserver->onScanningProgress(logStream.str());

					subDirsList.emplace_back(traverseDir + FindFileData.cFileName + L"\\");
				}
			}
		} while (FindNextFile(hFind, &FindFileData));

		logStream.str();
		logStream << L"Directory \"" << traverseDir << L"\"size (bytes): " << directorySize << std::endl;
		scanningProgressObserver->onScanningProgress(logStream.str());

		auto fileSystemObject = FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::Directory, traverseDir, traverseDir, directorySize));
		fileSystemObjects.emplace_back(fileSystemObject);

		while (subDirsList.size() != 0)
		{
			auto front = subDirsList.front();

			logStream.str();
			logStream << L"-------------" << std::endl << L"Moving to next dir: " << front << std::endl << "-------------" << std::endl;
			scanningProgressObserver->onScanningProgress(logStream.str());

			subDirsList.pop_front();
			traverse(front);
		}
	}
	else
	{
		logStream.str();
		logStream << "FindFirstFileEx failed " << GetLastError() << std::endl;
		scanningProgressObserver->onScanningProgress(logStream.str());
		return;
	}
	FindClose(hFind);

	if (initialTraversingDir == traverseDir)
	{
		logStream = std::wstringstream();
		logStream << L"Depth traversing ended! Starting perform search goal action!" << std::endl;
		scanningProgressObserver->onScanningProgress(logStream.str());

		searchGoalStrategy->performSearchGoalAction(fileSystemObjects);
	}
}
