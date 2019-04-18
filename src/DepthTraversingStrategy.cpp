#include "pch.h"
#include "DepthTraversingStrategy.h"
#include "FindFileWrapper.h"
#include "FileWrapper.h"

DepthTraversingStrategy::DepthTraversingStrategy(SearchGoalStrategySharedPtr searchGoalStrategy, ScanningProgressObserverSharedPtr scanningProgressObserver)
	: searchGoalStrategy(searchGoalStrategy),
	scanningProgressObserver(scanningProgressObserver)
{

}

void DepthTraversingStrategy::traverse(const std::wstring & traverseDir)
{
	if (initialTraversingDir.empty())
	{
		initialTraversingDir = traverseDir;
	}
	
	std::wstringstream logStream;
	logStream << L"Current traverse path: " << traverseDir << std::endl;
	scanningProgressObserver->onScanningProgress(logStream.str());

	auto currentTraverseDir = traverseDir + L"*";

	auto findFileWrapper = FindFileWrapper(currentTraverseDir, FindExInfoStandard, FindExSearchNameMatch, FIND_FIRST_EX_LARGE_FETCH);

	LONGLONG directorySize = 0;

	std::list<std::wstring> subDirsList;

	if (findFileWrapper.findFirstFile())
	{
		logStream.str(L"");
		logStream << L"The first file found is: " << findFileWrapper.getFoundFileData().cFileName << std::endl;
		scanningProgressObserver->onScanningProgress(logStream.str());

		do {

			auto FindFileData = findFileWrapper.getFoundFileData();

			if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
			{
				auto filePath = traverseDir + FindFileData.cFileName;
				auto fileWrapper = FileWrapper(filePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

				if (!fileWrapper.openFile())
				{
					logStream.str(L"");
					logStream << "File opening failed! File: "<< filePath << ". Error code: " << GetLastError() << std::endl;
					scanningProgressObserver->onScanningErrorOccurred(logStream.str());
				}
				else
				{
					logStream.str(L"");
					logStream << "Found file: " << FindFileData.cFileName << std::endl;
					scanningProgressObserver->onScanningProgress(logStream.str());

					auto fileSize = fileWrapper.getFileSize();
					if (fileSize != -1)
					{
						auto fileSystemObject = FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::File, traverseDir,
							FindFileData.cFileName, fileSize));
						directorySize += fileSize;
						fileSystemObjects.emplace_back(fileSystemObject);
					}
					else
					{
						logStream.str(L"");
						logStream << "Getting file size failed! File: "<< filePath << ". Error code: " << GetLastError() << std::endl;
						scanningProgressObserver->onScanningErrorOccurred(logStream.str());
					}
				}
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
				}
			}
		} while (findFileWrapper.findNextFile());

		logStream.str(L"");
		logStream << L"Directory \"" << traverseDir << L"\"size (bytes): " << directorySize << std::endl;
		scanningProgressObserver->onScanningProgress(logStream.str());

		auto fileSystemObject = FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::Directory, traverseDir, traverseDir, directorySize));
		fileSystemObjects.emplace_back(fileSystemObject);
	}
	else
	{
		logStream.str(L"");
		logStream << "Find first file failed! Path: "<< traverseDir <<"Error code: " << GetLastError() << std::endl;
		scanningProgressObserver->onScanningProgress(logStream.str());
		return;
	}

	if (initialTraversingDir == traverseDir)
	{
		logStream.str(L"");
		logStream << L"Depth traversing ended! Starting perform search goal action!" << std::endl;
		scanningProgressObserver->onScanningProgress(logStream.str());

		searchGoalStrategy->performSearchGoalAction(fileSystemObjects);
	}
}
