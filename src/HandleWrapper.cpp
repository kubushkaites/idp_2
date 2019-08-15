#include "pch.h"
#include "HandleWrapper.h"

HandleWrapper::HandleWrapper(HANDLE handle, HandleType handleType)
{ 
	if (handle == INVALID_HANDLE_VALUE)
	{
		std::string errorMessage = "Error code : " + std::to_string(GetLastError());
		throw std::runtime_error(errorMessage);
	}
	else 
	{
		this->handle = handle;
		this->handleType = handleType;
	}
}

HANDLE HandleWrapper::getHandle() const
{
	return handle;
}

HandleWrapper::~HandleWrapper()
{
	if (handleType == HandleType::FILE_HANDLE) 
	{
		if (!CloseHandle(handle)) 
		{
			std::cerr << "CloseHandle failed! Error code: " << GetLastError() << std::endl;
		}
	}
	else if(handleType == HandleType::FIND_FILE_HANDLE)
	{
		if (!FindClose(handle))
		{
			std::cerr << "FindClose failed! Error code: " << GetLastError() << std::endl;
		}
	}
}
