#pragma once
#include "pch.h"

enum class HandleType{ FILE_HANDLE, FIND_FILE_HANDLE};

class HandleWrapper 
{
public:
	HandleWrapper(HANDLE handle, HandleType handleType);
	HANDLE getHandle() const;
	~HandleWrapper();
private:
	HANDLE handle;
	HandleType handleType;
};
