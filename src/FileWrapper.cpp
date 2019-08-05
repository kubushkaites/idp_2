#include "pch.h"
#include "FileWrapper.h"
#include "IScanningProgressObserver.h"
#include "Utils.h"

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
	hFile = CreateFileW(fileName.c_str(), desiredAccess, shareMode, securityAttributes, creationDisposition, flagsAndAttributes, templateFile);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		std::string errorMessage = "INVALID_HANDLE_VALUE on CreateFileW! File path: " + Utf8Converter::utf8Encode(fileName);
		throw std::runtime_error(errorMessage);
	}
}

const LONGLONG & FileWrapper::getFileSize()
{
	LARGE_INTEGER size;
	if (GetFileSizeEx(hFile, &size))
	{
		fileSize = size.QuadPart;
	}
	else
	{
		std::stringstream error;
		error << "Getting file size failed! File: " << Utf8Converter::utf8Encode(fileName) << ". Error code: " << GetLastError() << std::endl;
		throw std::runtime_error(error.str());
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
