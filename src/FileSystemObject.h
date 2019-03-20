#pragma once
#include "pch.h"

class FileSystemObject;

using FileSystemObjectSharedPtr = std::shared_ptr<FileSystemObject>;

enum class FileSystemObjectType {Directory, File};

class FileSystemObject
{
public:
	FileSystemObject(/*const FileSystemObjectType objectType,*/ const std::wstring& fileSystemObjectPath, const std::wstring& fileSystemObjectName, const DWORD& fileSystemObjectSize);
	DWORD getFileSystemObjectSize() const;
	const std::wstring& getFileSystemObjectPath() const;
	const std::wstring& getFileSystemObjectName() const;
private:
	std::wstring fileSystemObjectPath;
	std::wstring fileSystemObjectName;
	DWORD fileSystemObjectSize;
};

