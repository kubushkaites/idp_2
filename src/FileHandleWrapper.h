#pragma once
#include "BaseHandleWrapper.h"

class FileHandleWrapper : public BaseHandleWrapper
{
public:
	FileHandleWrapper(HANDLE handle);
	virtual void verifyHandle(HANDLE handle) override;
	virtual void reset() override;
	~FileHandleWrapper();
	FileHandleWrapper& operator=(FileHandleWrapper&& other);
	FileHandleWrapper(FileHandleWrapper&& other);
	FileHandleWrapper(const FileHandleWrapper&) = delete;
	FileHandleWrapper& operator= (const FileHandleWrapper&) = delete;
};