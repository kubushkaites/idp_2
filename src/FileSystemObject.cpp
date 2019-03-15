#include "pch.h"
#include "FileSystemObject.h"

FileSystemObject::FileSystemObject(const std::wstring & fileSystemObjectPath, const std::wstring & fileSystemObjectName, const DWORD & fileSystemObjectSize)
	: fileSystemObjectPath(fileSystemObjectPath),
	fileSystemObjectName(fileSystemObjectName),
	fileSystemObjectSize(fileSystemObjectSize)
{
}

DWORD FileSystemObject::getFileSystemObjectSize() const
{
	return fileSystemObjectSize;
}

const std::wstring & FileSystemObject::getFileSystemObjectPath() const
{
	return fileSystemObjectPath;
}

const std::wstring & FileSystemObject::getFileSystemObjectName() const
{
	return fileSystemObjectName;
}
