#include "pch.h"
#include "ConsoleScanningProgressObserver.h"


void ConsoleScanningProgressObserver::printFileSystemObjectInfo(FileSystemObjectSharedPtr fsObject)
{
	std::cout << "-----------------------------" << std::endl;
	std::wcout << L"File system object path: " << fsObject->getFileSystemObjectPath() << std::endl;
	std::wcout << L"File system object name: " << fsObject->getFileSystemObjectName() << std::endl;
	std::wcout << L"File system object size(bytes): " << fsObject->getFileSystemObjectSize() << std::endl;
	std::cout << "-----------------------------" << std::endl;
}

void ConsoleScanningProgressObserver::onScanningProgress(const std::wstring & message)
{
	std::wcout << message;
}

void ConsoleScanningProgressObserver::onScanningErrorOccurred(const std::wstring & errorMessage)
{
	std::wcout<<L"Scanning error occurred: "<<std::endl<<L"\""<<errorMessage<<L"\""<<std::endl;
}

void ConsoleScanningProgressObserver::onScanningResult(SearchGoal searchGoal, const std::list<FileSystemObjectSharedPtr>& objectsMatchingChosenSearchGoal)
{
	if (searchGoal == SearchGoal::FIND_LARGEST_FOLDERS)
	{
		std::cout << "Largest folders found: " << std::endl;
	}
	else if (searchGoal == SearchGoal::FIND_FILES_BY_EXTENSION)
	{
		std::cout << "Search files by extension ended: " << std::endl;
	}
	else if (searchGoal == SearchGoal::DELETE_FILE)
	{
		std::cout << "The following files were deleted: " << std::endl;
	}
	for (auto& objectMatchingChosenSearchGoal : objectsMatchingChosenSearchGoal)
	{
		printFileSystemObjectInfo(objectMatchingChosenSearchGoal);
	}
}

void ConsoleScanningProgressObserver::onScanningResult(SearchGoal searchGoal, const FileSystemObjectSharedPtr objectMatchingToChosenSearchGoal)
{
	if (searchGoal == SearchGoal::FIND_LARGEST_FILE)
	{
		std::cout << "Largest file found: " << std::endl;
	}
	printFileSystemObjectInfo(objectMatchingToChosenSearchGoal);
}


