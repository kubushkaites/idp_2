#pragma once
#include "pch.h"

namespace Utf8Converter {
	std::string utf8Encode(const std::wstring &wstr);
	std::wstring utf8Decode(const std::string &str);
};

namespace FileUtils {
	const LONGLONG getFileSize(HANDLE handle);	
};
