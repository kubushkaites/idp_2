#include "pch.h"
#include "ConsoleScanningProgressObserver.h"


void ConsoleScanningProgressObserver::onScanningProgress(const std::wstring & currentlyScanningDirectory, const std::wstring & currentlyScanningFileSystemObject)
{

}

void ConsoleScanningProgressObserver::onScanningResult(SearchGoal searchGoal, std::any objectsMatchingToChosenSearchGoal/*FileSystemObjectsCollection objectsMatchingToChosenSearchGoal*/)
{
	//const std::vector<FileSystemObjectSharedPtr>* vec;
	//const FileS
	//const std::list<FileSystemObjectSharedPtr>* lis;
	if (searchGoal == SearchGoal::FIND_LARGEST_FOLDERS)
	{
		std::cout << "Largest folders found: " << std::endl;
		auto vec = std::any_cast<std::vector<FileSystemObjectSharedPtr>*>(objectsMatchingToChosenSearchGoal);
		for (auto& fsObj : *vec)
		{
			std::cout << "-----------------------------" << std::endl;
			std::wcout << L"File system object path: " << fsObj->getFileSystemObjectPath() << std::endl;
			std::wcout << L"File system object name: " << fsObj->getFileSystemObjectName() << std::endl;
			std::wcout << L"File system object size(bytes): " << fsObj->getFileSystemObjectSize() << std::endl;
			std::cout << "-----------------------------" << std::endl;
		}
	}
	else if (searchGoal == SearchGoal::FIND_LARGEST_FILE)
	{
		/*FileSystemObjectSharedPtr fsObject = std::any_cast<*/
	}
}
