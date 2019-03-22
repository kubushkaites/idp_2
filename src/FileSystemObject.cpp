#include "pch.h"
#include "FileSystemObject.h"

FileSystemObject::FileSystemObject(const FileSystemObjectType fsObjectType, const std::wstring & fileSystemObjectPath, const std::wstring & fileSystemObjectName, const DWORD & fileSystemObjectSize)
	: fsObjectType(fsObjectType),
	fileSystemObjectPath(fileSystemObjectPath),
	fileSystemObjectName(fileSystemObjectName),
	fileSystemObjectSize(fileSystemObjectSize)
{
}

FileSystemObjectType FileSystemObject::getFileSystemObjectType() const
{
	return fsObjectType;
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
