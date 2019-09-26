#pragma once
#include "pch.h"

class BaseHandleWrapper 
{
public:
	virtual void verifyHandle(HANDLE handle) = 0;
	virtual void reset(HANDLE handle);
	virtual void reset() = 0;
	virtual HANDLE release();
	virtual HANDLE getHandle() const;
	virtual ~BaseHandleWrapper() = 0;	
protected:
	BaseHandleWrapper(HANDLE handle);
protected:
	HANDLE handle = nullptr;
};
