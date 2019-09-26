#include "pch.h"
#include "FileHandleWrapper.h"

FileHandleWrapper::FileHandleWrapper(HANDLE handle)
	: BaseHandleWrapper(handle)
{
	verifyHandle(this->handle);
}

void FileHandleWrapper::reset()
{
	auto isReleased = handle == nullptr;
	if (!isReleased)
	{
		if (!CloseHandle(handle)) 
		{
			std::cerr << "CloseHandle failed! Error code: " << GetLastError() << std::endl;
		}
		else 
		{
			handle = nullptr;
		}
	}
}

FileHandleWrapper::~FileHandleWrapper()
{
	reset();
}

FileHandleWrapper & FileHandleWrapper::operator=(FileHandleWrapper && other)
{
	if (this != &other)
	{
		reset();
		handle = other.getHandle();
		other.handle = nullptr;
	}
	return *this;
}

FileHandleWrapper::FileHandleWrapper(FileHandleWrapper && other)
	: BaseHandleWrapper(nullptr)
{
	*this = std::move(other);
}

void FileHandleWrapper::verifyHandle(HANDLE handle)
{
	if (handle == nullptr || handle == INVALID_HANDLE_VALUE)
	{
		std::string errorMessage = "Error code : " + std::to_string(GetLastError());
		throw std::runtime_error(errorMessage);
	}
}