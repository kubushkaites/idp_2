#include "pch.h"
#include "BreadthTraversingStrategy.h"
#include "FindFileWrapper.h"
#include "FileWrapper.h"
#include "Utils.h"

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
		LONGLONG directorySize = 0;

		auto findFileWrapper = FindFileWrapper(nextSearchPathWithWildCard, FindExInfoStandard, FindExSearchNameMatch, FIND_FIRST_EX_LARGE_FETCH);

		do
		{
			auto FindFileData = findFileWrapper.getFoundFileData();
			if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
			{
				auto filePath = nextSearchPath + FindFileData.cFileName;
				auto fileWrapper = FileWrapper(filePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

				logStream.str(L"");
				logStream << L"Found file: " << FindFileData.cFileName << std::endl;
				scanningProgressObserver->onScanningProgress(logStream.str());

				auto fileSize = fileWrapper.getFileSize();

				auto fileSystemObject = FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::File, nextSearchPath,
					FindFileData.cFileName, fileSize));
				directorySize += fileSize;
				fileSystemObjects.emplace_back(fileSystemObject);
			}
			else
			{
				if ((wcscmp(FindFileData.cFileName, L".") != 0) && (wcscmp(FindFileData.cFileName, L"..") != 0))
				{
					logStream.str(L"");
					logStream << "Found dir: " << FindFileData.cFileName << std::endl;
					scanningProgressObserver->onScanningProgress(logStream.str());
					subDirsList.emplace_back(nextSearchPath + FindFileData.cFileName + L"\\");
				}
			}
		} while (findFileWrapper.findNextFile());

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
	} while (continueSearch);

	logStream.str(L"");
	logStream << L"Breadth traversing ended! Starting perform search goal action!" << std::endl;
	scanningProgressObserver->onScanningProgress(logStream.str());

	searchGoalStrategy->performSearchGoalAction(fileSystemObjects);
}
