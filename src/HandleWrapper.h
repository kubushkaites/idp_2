#pragma once
#include "pch.h"

enum class HandleType{SEARCH_HANDLE, FILE_HANDLE};

class HandleWrapper {
public:
	HandleWrapper(HANDLE handle, HandleType handleType);
	HANDLE GetHandle() const;
	~HandleWrapper();
private:
	HANDLE handle;
	HandleType handleType;
};