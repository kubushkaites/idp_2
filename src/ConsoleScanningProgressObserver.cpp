#include "pch.h"
#include "ConsoleScanningProgressObserver.h"


void ConsoleScanningProgressObserver::onScanningProgress(const std::wstring & currentlyScanningDirectory, const std::wstring & currentlyScanningFileSystemObject)
{

}

void ConsoleScanningProgressObserver::onScanningResult(SearchGoal searchGoal, const std::vector<FileSystemObjectSharedPtr>& objectsMatchingToChosenSearchGoal)
{
	if (searchGoal == SearchGoal::FIND_LARGEST_FOLDERS)
	{
		std::cout << "Largest folders found: " << std::endl;
	}
	for (auto& fsObj : objectsMatchingToChosenSearchGoal)
	{
		std::cout << "-----------------------------" << std::endl;
		std::wcout << L"File system object path: " << fsObj->getFileSystemObjectPath() << std::endl;
		std::wcout << L"File system object name: " << fsObj->getFileSystemObjectName() << std::endl;
		std::wcout << L"File system object size(bytes): " << fsObj->getFileSystemObjectSize() << std::endl;
		std::cout << "-----------------------------" << std::endl;
	}
}
