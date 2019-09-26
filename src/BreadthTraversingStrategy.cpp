#include "pch.h"
#include "BreadthTraversingStrategy.h"
#include "Utils.h"
#include "FileHandleWrapper.h"
#include "FindFileHandleWrapper.h"

BreadthTraversingStrategy::BreadthTraversingStrategy(ScanningProgressObserverSharedPtr scanningProgressObserver)
	: scanningProgressObserver(scanningProgressObserver)
{

}

const std::tuple<bool, const std::list<FileSystemObjectSharedPtr>&> BreadthTraversingStrategy::traverse(const std::wstring & traverseDir)
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

		WIN32_FIND_DATA findFileData;

		auto findFileHandleWrapper = FindFileHandleWrapper(FindFirstFileEx(nextSearchPathWithWildCard.c_str(), FindExInfoStandard, &findFileData,
			FindExSearchNameMatch, NULL, FIND_FIRST_EX_LARGE_FETCH));

		do
		{
			if ((findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
			{
				auto filePath = nextSearchPath + findFileData.cFileName;

				auto fileHandleWrapper = FileHandleWrapper(CreateFileW(filePath.c_str(),
					GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL));

				logStream.str(L"");
				logStream << L"Found file: " << findFileData.cFileName << std::endl;
				scanningProgressObserver->onScanningProgress(logStream.str());

				auto fileSize = FileUtils::getFileSize(fileHandleWrapper.getHandle());

				auto fileSystemObject = FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::File, nextSearchPath,
					findFileData.cFileName, fileSize));
				directorySize += fileSize;
				fileSystemObjects.emplace_back(fileSystemObject);
			}
			else
			{
				if ((wcscmp(findFileData.cFileName, L".") != 0) && (wcscmp(findFileData.cFileName, L"..") != 0))
				{
					logStream.str(L"");
					logStream << "Found dir: " << findFileData.cFileName << std::endl;
					scanningProgressObserver->onScanningProgress(logStream.str());
					subDirsList.emplace_back(nextSearchPath + findFileData.cFileName + L"\\");
				}
			}
		} while (FindNextFile(findFileHandleWrapper.getHandle(), &findFileData));

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

	return std::tuple<bool, const std::list<FileSystemObjectSharedPtr>&>(true, fileSystemObjects);
}
