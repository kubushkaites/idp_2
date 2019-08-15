#include "FileSystemScannerTest.h"
#include "FindLargestFoldersStrategy.h"
#include "FindLargestFileStrategy.h"
#include "FindFilesByExtensionStrategy.h"
#include "DeleteFilesByNameStrategy.h"
#include "ConsoleScanningProgressObserver.h"
#include "HandleWrapper.h"

void FileSystemScannerTest::SetUp()
{
	scanningProgressObserver = ScanningProgressObserverSharedPtr(new ConsoleScanningProgressObserver());
}

void FileSystemScannerTest::TearDown()
{

}

TEST_F(FileSystemScannerTest, FindLargestFolders) 
{
	std::list<FileSystemObjectSharedPtr> fsObjects;
	fsObjects.push_back(FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::Directory, L"C:\\testDir\\", L"C:\\testDir\\", 25687)));
	fsObjects.push_back(FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::Directory, L"C:\\testDir1\\", L"C:\\testDir1\\", 25879987)));
	fsObjects.push_back(FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::Directory, L"C:\\testDir2\\", L"C:\\testDir2\\", 989985687)));
	fsObjects.push_back(FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::Directory, L"C:\\testDir3\\", L"C:\\testDir3\\", 87126387)));
	fsObjects.push_back(FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::Directory, L"C:\\testDir4\\", L"C:\\testDir4\\", 256)));
	fsObjects.push_back(FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::Directory, L"C:\\testDir5\\", L"C:\\testDir5\\", 25687)));
	fsObjects.push_back(FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::Directory, L"C:\\testDir6\\", L"C:\\testDir6\\", 444)));
	fsObjects.push_back(FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::Directory, L"C:\\testDir7\\", L"C:\\testDir7\\", 25687)));
	fsObjects.push_back(FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::Directory, L"C:\\testDir8\\", L"C:\\testDir8\\", 763476762)));
	fsObjects.push_back(FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::Directory, L"C:\\testDir9\\", L"C:\\testDir9\\", 25687)));
	fsObjects.push_back(FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::Directory, L"C:\\testDir10\\", L"C:\\testDir10\\", 25687)));

	auto strategy = FindLargestFoldersStrategy(3, scanningProgressObserver);

	auto result = strategy.performSearchGoalAction(fsObjects);
	auto foundDirs = std::get<1>(result);

	std::list<FileSystemObjectSharedPtr> expectedDirs;
	expectedDirs.push_back(FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::Directory, L"C:\\testDir2\\", L"C:\\testDir2\\", 989985687)));
	expectedDirs.push_back(FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::Directory, L"C:\\testDir8\\", L"C:\\testDir8\\", 763476762)));
	expectedDirs.push_back(FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::Directory, L"C:\\testDir3\\", L"C:\\testDir3\\", 87126387)));

	EXPECT_PRED2([](size_t actual, size_t expected) { return actual == expected;}, foundDirs.size(), expectedDirs.size());

	for (auto& dir : foundDirs)
	{
		ASSERT_EQ(dir->getFileSystemObjectName(), expectedDirs.front()->getFileSystemObjectName());
		expectedDirs.pop_front();
	}
}

TEST_F(FileSystemScannerTest, FindLargestFile) 
{
	std::list<FileSystemObjectSharedPtr> fsObjects;
	fsObjects.push_back(FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::File, L"C:\\testDir\\", L"file1", 25687)));
	fsObjects.push_back(FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::File, L"C:\\testDir\\", L"file2", 666877676)));
	fsObjects.push_back(FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::File, L"C:\\testDir\\", L"file3", 98392489384)));
	fsObjects.push_back(FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::File, L"C:\\testDir\\", L"file4", 123)));
	fsObjects.push_back(FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::File, L"C:\\testDir\\", L"file5", 3434)));
	fsObjects.push_back(FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::File, L"C:\\testDir\\", L"file6", 345435345)));

	auto strategy = FindLargestFileStrategy(scanningProgressObserver);

	auto result = strategy.performSearchGoalAction(fsObjects);
	auto foundFiles = std::get<1>(result);

	std::list<FileSystemObjectSharedPtr> expectedFiles;
	expectedFiles.push_back(FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::File, L"C:\\testDir\\", L"file3", 98392489384)));

	EXPECT_PRED2([](size_t actual, size_t expected) { return actual == expected;}, foundFiles.size(), expectedFiles.size());

	for (auto& dir : foundFiles)
	{
		ASSERT_EQ(dir->getFileSystemObjectName(), expectedFiles.front()->getFileSystemObjectName());
		expectedFiles.pop_front();
	}
}

TEST_F(FileSystemScannerTest, FindFilesByExtension) 
{
	std::list<FileSystemObjectSharedPtr> fsObjects;
	fsObjects.push_back(FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::File, L"C:\\testDir\\", L"file1.txt", 25687)));
	fsObjects.push_back(FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::File, L"C:\\testDir\\", L"file2.txt", 666877676)));
	fsObjects.push_back(FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::File, L"C:\\testDir\\", L"file3.rtf", 98392489384)));
	fsObjects.push_back(FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::File, L"C:\\testDir\\", L"file4.exe", 123)));
	fsObjects.push_back(FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::File, L"C:\\testDir\\", L"file5.pdf", 3434)));
	fsObjects.push_back(FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::File, L"C:\\testDir\\", L"file6.pdf", 345435345)));
	fsObjects.push_back(FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::File, L"C:\\testDir\\", L"file7.exe", 783849)));
	fsObjects.push_back(FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::File, L"C:\\testDir\\", L"file8.pdf", 3454999999945)));
	fsObjects.push_back(FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::File, L"C:\\testDir\\", L"file9.pdf", 124365148923)));

	auto strategy = FindFilesByExtensionStrategy(L"exe", scanningProgressObserver);

	auto result = strategy.performSearchGoalAction(fsObjects);
	auto foundFiles = std::get<1>(result);

	std::list<FileSystemObjectSharedPtr> expectedFiles;
	expectedFiles.push_back(FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::File, L"C:\\testDir\\", L"file4.exe", 123)));
	expectedFiles.push_back(FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::File, L"C:\\testDir\\", L"file7.exe", 783849)));
	
	EXPECT_PRED2([](size_t actual, size_t expected) { return actual == expected;}, foundFiles.size(), expectedFiles.size());

	for (auto& dir : foundFiles)
	{
		ASSERT_EQ(dir->getFileSystemObjectName(), expectedFiles.front()->getFileSystemObjectName());
		expectedFiles.pop_front();
	}
}

TEST_F(FileSystemScannerTest, DeleteFilesByName) 
{
	{
		auto fileHandleWrapper = HandleWrapper(CreateFileW(L"file1",
			GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL), HandleType::FILE_HANDLE);
	}

	std::list<FileSystemObjectSharedPtr> fsObjects;
	fsObjects.push_back(FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::File, L"", L"file1", 0)));

	auto strategy = DeleteFilesByNameStrategy(L"file1", scanningProgressObserver);
	auto result = strategy.performSearchGoalAction(fsObjects);

	auto removedFiles = std::get<1>(result);

	std::list<FileSystemObjectSharedPtr> expectedRemovedFiles;
	expectedRemovedFiles.push_back(FileSystemObjectSharedPtr(new FileSystemObject(FileSystemObjectType::File, L"", L"file1", 0)));

	EXPECT_PRED2([](size_t actual, size_t expected) { return actual == expected;}, removedFiles.size(), expectedRemovedFiles.size());

	for (auto& file : removedFiles)
	{
		ASSERT_EQ(file->getFileSystemObjectName(), expectedRemovedFiles.front()->getFileSystemObjectName());
		expectedRemovedFiles.pop_front();
	}
}

