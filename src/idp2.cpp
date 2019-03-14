// idp2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "ScannerArgumentsProvider.h"


int main()
{
	std::map<std::wstring, std::wstring> traverseModeMatches = { {L"1", ScannerArgumentsProviderConstants::breadthTraverseMode}, 
																{L"2", ScannerArgumentsProviderConstants::depthTraverseMode}, 
																{L"3", ScannerArgumentsProviderConstants::alphabeticalTraverseMode} };
	std::map<std::wstring, std::wstring> searchGoalMatches = { {L"1", ScannerArgumentsProviderConstants::findLargestFoldersGoal}, 
															   {L"2", ScannerArgumentsProviderConstants::findLargestFileGoal}, 
															   {L"3", ScannerArgumentsProviderConstants::findFilesByExtensionGoal},
															   {L"4", ScannerArgumentsProviderConstants::deleteFileGoal} };

	std::map<std::wstring, std::wstring> scannerArguments;
	std::cout << "Enter start search path (e.g. \"C:\\\":" << std::endl;
	std::wstring traversingStartPath;
	std::getline(std::wcin, traversingStartPath);
	scannerArguments[ScannerArgumentsProviderConstants::traversingStartPath] = traversingStartPath;

	std::cout << "Choose traverse mode:" << std::endl << "1 - Breadth traverse mode" << std::endl << "2 - Depth traverse mode" << std::endl
			  <<"3 - Alphabetical traverse mode";
	std::wstring traverseMode;
	std::getline(std::wcin, traverseMode);
	scannerArguments[ScannerArgumentsProviderConstants::traverseMode] = traverseModeMatches.at(traverseMode);

	std::cout << "Choose search goal:" << std::endl << "1 - Find largest folders goal" << std::endl << "2 - Find largest file goal" << std::endl
		<< "3 - Find files by extension goal" << std::endl << "4 - Delete file goal" << std::endl;
	std::wstring searchGoal;
	std::getline(std::wcin, searchGoal);
	scannerArguments[ScannerArgumentsProviderConstants::searchGoal] = searchGoalMatches.at(searchGoal);

	if (searchGoal == L"1")
	{
		std::cout << "Enter amount of folders to find:" << std::endl;
		std::wstring amountOfFoldersToFind;
		std::getline(std::wcin, amountOfFoldersToFind);
		scannerArguments[ScannerArgumentsProviderConstants::amountOfFoldersToFind] = amountOfFoldersToFind;
	}
	else if (searchGoal == L"3")
	{
		std::cout << "Enter file extension (e.g. \"exe\"):" << std::endl;
		std::wstring searchFileExtension;
		std::getline(std::wcin, searchFileExtension);
		scannerArguments[ScannerArgumentsProviderConstants::searchFileExtension] = searchFileExtension;
	}
	else if (searchGoal == L"4")
	{
		std::cout << "Enter file to remove (e.g. \"abc.txt\"):" << std::endl;
		std::wstring fileToRemoveName;
		std::getline(std::wcin, fileToRemoveName);
		scannerArguments[ScannerArgumentsProviderConstants::fileToRemoveName] = fileToRemoveName;
	}

	ScannerArgumentsProvider::Instance().parseArguments(std::move(scannerArguments));

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
