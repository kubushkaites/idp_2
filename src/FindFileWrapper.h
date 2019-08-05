#pragma once
#include "pch.h"

class FindFileWrapper
{
public:
	FindFileWrapper(const std::wstring& fileName, const FINDEX_INFO_LEVELS findInfoLevels, const FINDEX_SEARCH_OPS searchOptions,
		const DWORD additionalFlags);
	bool findNextFile();
	const WIN32_FIND_DATA& getFoundFileData() const;
	~FindFileWrapper();
private:
	std::wstring fileName;
	FINDEX_INFO_LEVELS findInfoLevels;
	FINDEX_SEARCH_OPS searchOptions;
	DWORD additionalFlags;
	WIN32_FIND_DATA findFileData;
	HANDLE hFind = nullptr;
};
