#include "pch.h"
#include "DepthTraversingStrategy.h"
#include "HandleWrapper.h"

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

	HandleWrapper handleWrapper(hFind, HandleType::SEARCH_HANDLE);

	LONGLONG directorySize = 0;

	std::list<std::wstring> subDirsList;

	if (handleWrapper.GetHandle() != INVALID_HANDLE_VALUE)
	{
		logStream.str(L"");
		logStream << L"The first file found is: " << FindFileData.cFileName << std::endl;
		scanningProgressObserver->onScanningProgress(logStream.str());

		do {
			if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
			{
				auto filePath = traverseDir + FindFileData.cFileName;
				HANDLE hFile = CreateFileW(filePath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
				HandleWrapper handleWrapper(hFile, HandleType::FILE_HANDLE);
				if (handleWrapper.GetHandle() == INVALID_HANDLE_VALUE)
				{
					logStream.str(L"");
					logStream << "CreateFileW failed " << GetLastError() << std::endl;
					scanningProgressObserver->onScanningErrorOccurred(logStream.str());
				}
				else
				{
					LARGE_INTEGER fileSize;
					if (GetFileSizeEx(handleWrapper.GetHandle(), &fileSize))
					{
						auto fileSystemObject = FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::File, traverseDir,
							FindFileData.cFileName, fileSize.QuadPart));
						directorySize += fileSize.QuadPart;
						fileSystemObjects.emplace_back(fileSystemObject);
					}
					else
					{
						logStream.str(L"");
						logStream << "GetFileSizeEx failed " << GetLastError() << std::endl;
						scanningProgressObserver->onScanningErrorOccurred(logStream.str());
					}
				}
				/*auto fileSize = (FindFileData.nFileSizeHigh * (MAXDWORD + 1)) + FindFileData.nFileSizeLow;
				directorySize += fileSize;
				
				logStream.str(L"");
				logStream << "Found file: " << FindFileData.cFileName << std::endl;
				scanningProgressObserver->onScanningProgress(logStream.str());

				auto fileSystemObject = FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::File, traverseDir, FindFileData.cFileName, fileSize));
				fileSystemObjects.emplace_back(fileSystemObject);*/
			}
			else
			{
				if ((wcscmp(FindFileData.cFileName, L".") != 0) && (wcscmp(FindFileData.cFileName, L"..") != 0))
				{
					logStream.str(L"");
					logStream << "Found dir: " << FindFileData.cFileName << std::endl;
					scanningProgressObserver->onScanningProgress(logStream.str());

					auto nextDir = traverseDir + FindFileData.cFileName + L"\\";
					logStream.str(L"");
					logStream << L"-------------" << std::endl << L"Moving to next dir: " << nextDir << std::endl << "-------------" << std::endl;
					traverse(nextDir);

					/*subDirsList.emplace_back(traverseDir + FindFileData.cFileName + L"\\");*/
				}
			}
		} while (FindNextFile(handleWrapper.GetHandle(), &FindFileData));

		logStream.str();
		logStream << L"Directory \"" << traverseDir << L"\"size (bytes): " << directorySize << std::endl;
		scanningProgressObserver->onScanningProgress(logStream.str());

		auto fileSystemObject = FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::Directory, traverseDir, traverseDir, directorySize));
		fileSystemObjects.emplace_back(fileSystemObject);

		//while (subDirsList.size() != 0)
		//{
		//	auto front = subDirsList.front();

		//	logStream.str();
		//	logStream << L"-------------" << std::endl << L"Moving to next dir: " << front << std::endl << "-------------" << std::endl;
		//	scanningProgressObserver->onScanningProgress(logStream.str());

		//	subDirsList.pop_front();
		//	traverse(front);
		//}
	}
	else
	{
		logStream.str();
		logStream << "FindFirstFileEx failed " << GetLastError() << std::endl;
		scanningProgressObserver->onScanningProgress(logStream.str());
		return;
	}
	//FindClose(hFind);

	if (initialTraversingDir == traverseDir)
	{
		logStream = std::wstringstream();
		logStream << L"Depth traversing ended! Starting perform search goal action!" << std::endl;
		scanningProgressObserver->onScanningProgress(logStream.str());

		searchGoalStrategy->performSearchGoalAction(fileSystemObjects);
	}
}
