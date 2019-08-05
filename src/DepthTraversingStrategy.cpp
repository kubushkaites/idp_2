#include "pch.h"
#include "DepthTraversingStrategy.h"
#include "FindFileWrapper.h"
#include "FileWrapper.h"

DepthTraversingStrategy::DepthTraversingStrategy(ScanningProgressObserverSharedPtr scanningProgressObserver)
	: scanningProgressObserver(scanningProgressObserver)
{

}

const std::tuple<bool, const std::list<FileSystemObjectSharedPtr>&> DepthTraversingStrategy::traverse(const std::wstring & traverseDir)
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

	logStream.str(L"");
	logStream << L"The first file found is: " << findFileWrapper.getFoundFileData().cFileName << std::endl;
	scanningProgressObserver->onScanningProgress(logStream.str());

	do 
	{
		auto FindFileData = findFileWrapper.getFoundFileData();

		if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
		{
			auto filePath = traverseDir + FindFileData.cFileName;
			auto fileWrapper = FileWrapper(filePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

			logStream.str(L"");
			logStream << "Found file: " << FindFileData.cFileName << std::endl;
			scanningProgressObserver->onScanningProgress(logStream.str());

			auto fileSize = fileWrapper.getFileSize();
			auto fileSystemObject = FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::File, traverseDir,
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

	if (initialTraversingDir == traverseDir)
	{
		logStream.str(L"");
		logStream << L"Depth traversing ended! Starting perform search goal action!" << std::endl;
		scanningProgressObserver->onScanningProgress(logStream.str());

		return std::tuple<bool, const std::list<FileSystemObjectSharedPtr>&>(true, fileSystemObjects);
	}
}
