#include "pch.h"
#include "BaseHandleWrapper.h"

BaseHandleWrapper::BaseHandleWrapper(HANDLE handle)
	: handle(handle)
{
}

void BaseHandleWrapper::reset(HANDLE handle)
{
	verifyHandle(handle);
	reset();
	this->handle = handle;
}

HANDLE BaseHandleWrapper::release()
{
	auto tmp = handle;
	handle = nullptr;
	return tmp;
}

HANDLE BaseHandleWrapper::getHandle() const
{
	return handle;
}

BaseHandleWrapper::~BaseHandleWrapper() { }
