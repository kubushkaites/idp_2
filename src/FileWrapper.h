#pragma once
#include "pch.h"

class FileWrapper
{
public:
	FileWrapper(std::wstring fileName, DWORD desiredAccess, DWORD shareMode, LPSECURITY_ATTRIBUTES securityAttibutes,
		DWORD creationDisposition, DWORD flagsAndAttibutes, HANDLE templateFile);
	const LONGLONG& getFileSize();
	~FileWrapper();
private:
	std::wstring fileName;
	DWORD desiredAccess;
	DWORD shareMode;
	LPSECURITY_ATTRIBUTES securityAttributes;
	DWORD creationDisposition;
	DWORD flagsAndAttributes;
	HANDLE templateFile;
	LONGLONG fileSize = -1;
	HANDLE hFile = nullptr;
};