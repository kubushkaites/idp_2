#pragma once
#include "BaseHandleWrapper.h"

class FindFileHandleWrapper : public BaseHandleWrapper
{
public:
	FindFileHandleWrapper(HANDLE handle);
	virtual void verifyHandle(HANDLE handle) override;
	virtual void reset() override;
	~FindFileHandleWrapper();
	FindFileHandleWrapper& operator=(FindFileHandleWrapper&& other);
	FindFileHandleWrapper(FindFileHandleWrapper&& other);
	FindFileHandleWrapper(const FindFileHandleWrapper&) = delete;
	FindFileHandleWrapper& operator= (const FindFileHandleWrapper&) = delete;
};