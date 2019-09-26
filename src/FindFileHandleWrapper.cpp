#include "pch.h"
#include "FindFileHandleWrapper.h"

FindFileHandleWrapper::FindFileHandleWrapper(HANDLE handle)
	: BaseHandleWrapper(handle)
{
	verifyHandle(this->handle);
}

void FindFileHandleWrapper::reset()
{
	auto isReleased = handle == nullptr;
	if (!isReleased)
	{
		if(!FindClose(handle))
		{
			std::cerr << "FindClose failed! Error code: " << GetLastError() << std::endl;
		}
		else
		{
			handle = nullptr;
		}		
	}
}

FindFileHandleWrapper::~FindFileHandleWrapper()
{
	reset();
}

FindFileHandleWrapper & FindFileHandleWrapper::operator=(FindFileHandleWrapper && other)
{
	if (this != &other)
	{
		reset();
		handle = other.getHandle();
		other.handle = nullptr;
	}
	return *this;
}

FindFileHandleWrapper::FindFileHandleWrapper(FindFileHandleWrapper && other)
	: BaseHandleWrapper(nullptr)
{
	*this = std::move(other);
}

void FindFileHandleWrapper::verifyHandle(HANDLE handle)
{
	if (handle == nullptr || handle == INVALID_HANDLE_VALUE)
	{
		std::string errorMessage = "Error code : " + std::to_string(GetLastError());
		throw std::runtime_error(errorMessage);
	}
}
