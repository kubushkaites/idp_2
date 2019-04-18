#include "pch.h"
#include "FindFileWrapper.h"

FindFileWrapper::FindFileWrapper(const std::wstring & fileName, const FINDEX_INFO_LEVELS findInfoLevels, 
	const FINDEX_SEARCH_OPS searchOptions, const DWORD additionalFlags)
	: fileName(fileName),
	findInfoLevels(findInfoLevels),
	searchOptions(searchOptions),
	additionalFlags(additionalFlags)
{
}

bool FindFileWrapper::findFirstFile()
{
	auto isSucceeded = false;
	hFind = FindFirstFileEx(fileName.c_str(), findInfoLevels, &findFileData,
		searchOptions, NULL, additionalFlags);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		isSucceeded = true;
	}
	return isSucceeded;
}

bool FindFileWrapper::findNextFile()
{
	return FindNextFile(hFind, &findFileData);
}

const WIN32_FIND_DATA & FindFileWrapper::getFoundFileData() const
{
	return findFileData;
}

FindFileWrapper::~FindFileWrapper()
{
	if (!FindClose(hFind))
	{
		std::cerr << "FindClose failed! Error code: " << GetLastError() << std::endl;
	}
}
