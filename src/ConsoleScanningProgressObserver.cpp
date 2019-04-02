#include "pch.h"
#include "ConsoleScanningProgressObserver.h"


void ConsoleScanningProgressObserver::onLargestFoldersFound(std::any largestFolders)
{
	std::cout << "Largest folders found: " << std::endl;
	auto folders = std::any_cast<std::vector<FileSystemObjectSharedPtr>*>(largestFolders);
	for (auto& folder : *folders)
	{
		printFileSystemObjectInfo(folder);
	}
}

void ConsoleScanningProgressObserver::onLargestFileFound(std::any largestFile)
{
	std::cout << "Largest file found: " << std::endl;
	auto file = std::any_cast<FileSystemObjectSharedPtr>(largestFile);
	printFileSystemObjectInfo(file);
}

void ConsoleScanningProgressObserver::onFilesByExtensionFound(std::any filesByExtension)
{
	std::wcout << L"Files with extension \"" << ScannerArgumentsProvider::Instance().getSearchFileExtension() <<L"\" found: " << std::endl;
	auto files = std::any_cast<std::list<FileSystemObjectSharedPtr>*>(filesByExtension);
	for (auto& file : *files)
	{
		printFileSystemObjectInfo(file);
	}
}

void ConsoleScanningProgressObserver::onDeletedFilesByName(std::any deletedFilesByName)
{
}

void ConsoleScanningProgressObserver::printFileSystemObjectInfo(FileSystemObjectSharedPtr fsObject)
{
	std::cout << "-----------------------------" << std::endl;
	std::wcout << L"File system object path: " << fsObject->getFileSystemObjectPath() << std::endl;
	std::wcout << L"File system object name: " << fsObject->getFileSystemObjectName() << std::endl;
	std::wcout << L"File system object size(bytes): " << fsObject->getFileSystemObjectSize() << std::endl;
	std::cout << "-----------------------------" << std::endl;
}

void ConsoleScanningProgressObserver::onScanningProgress(const std::wstring & currentlyScanningDirectory, const std::wstring & currentlyScanningFileSystemObject)
{

}



void ConsoleScanningProgressObserver::onScanningResult(SearchGoal searchGoal, std::any objectsMatchingChosenSearchGoal)
{
	if (searchGoal == SearchGoal::FIND_LARGEST_FOLDERS)
	{
		onLargestFoldersFound(objectsMatchingChosenSearchGoal);
		
	}
	else if (searchGoal == SearchGoal::FIND_LARGEST_FILE)
	{
		onLargestFileFound(objectsMatchingChosenSearchGoal);
	}
	else if (searchGoal == SearchGoal::FIND_FILES_BY_EXTENSION)
	{
		onFilesByExtensionFound(objectsMatchingChosenSearchGoal);
	}
	else if (searchGoal == SearchGoal::DELETE_FILE)
	{
		onDeletedFilesByName(objectsMatchingChosenSearchGoal);
	}
}
