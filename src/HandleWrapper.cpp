#include "pch.h"
#include "HandleWrapper.h"

HandleWrapper::HandleWrapper(HANDLE handle, HandleType handleType)
	: handle(handle),
	handleType(handleType)
{
}

HANDLE HandleWrapper::GetHandle() const
{
	return handle;
}

HandleWrapper::~HandleWrapper()
{
	if (handleType == HandleType::SEARCH_HANDLE)
	{
		FindClose(handle);
	}
	else if (handleType == HandleType::FILE_HANDLE)
	{
		CloseHandle(handle);
	}
}
