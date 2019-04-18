#include "pch.h"
#include "FileWrapper.h"
#include "IScanningProgressObserver.h"

FileWrapper::FileWrapper(std::wstring fileName, DWORD desiredAccess, DWORD shareMode, 
	LPSECURITY_ATTRIBUTES securityAttributes, DWORD creationDisposition, DWORD flagsAndAttributes, HANDLE templateFile)
	: fileName(fileName),
	desiredAccess(desiredAccess),
	shareMode(shareMode),
	securityAttributes(securityAttributes),
	creationDisposition(creationDisposition),
	flagsAndAttributes(flagsAndAttributes),
	templateFile(templateFile)
{
}

bool FileWrapper::openFile()
{
	auto isSucceeded = false;
	hFile = CreateFileW(fileName.c_str(), desiredAccess, shareMode, securityAttributes, creationDisposition, flagsAndAttributes, templateFile);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		isSucceeded = true;
	}
	return isSucceeded;
}

const LONGLONG & FileWrapper::getFileSize()
{
	if (hFile != nullptr && hFile != INVALID_HANDLE_VALUE)
	{
		LARGE_INTEGER size;
		if (GetFileSizeEx(hFile, &size))
		{
			fileSize = size.QuadPart;
		}
	}
	return fileSize;
}

FileWrapper::~FileWrapper()
{
	if (!CloseHandle(hFile))
	{
		std::cerr << "CloseHandle failed! Error code: " << GetLastError() << std::endl;
	}
}
