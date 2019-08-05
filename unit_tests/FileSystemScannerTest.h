#pragma once
#include "gtest\gtest.h"
#include "IScanningProgressObserver.h"

class FileSystemScannerTest: public ::testing::Test {
protected:
	void SetUp() override;
	void TearDown() override;

	ScanningProgressObserverSharedPtr scanningProgressObserver;
};