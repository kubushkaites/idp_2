#include "pch.h"
#include "Utils.h"

std::string Utf8Converter::utf8Encode(const std::wstring &wstr)
{
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
	std::string strTo(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
	return strTo;
}

std::wstring Utf8Converter::utf8Decode(const std::string &str)
{
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	std::wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
}

const LONGLONG FileUtils::getFileSize(HANDLE handle)
{
	LARGE_INTEGER size;
	if (GetFileSizeEx(handle, &size))
	{
		return size.QuadPart;
	}
	else
	{
		std::stringstream error;
		error << "Getting file size failed! Error code : " << GetLastError() << std::endl;
		throw std::runtime_error(error.str());
	}
}
