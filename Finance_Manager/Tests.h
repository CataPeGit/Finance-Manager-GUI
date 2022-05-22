#pragma once
#include "User.h"
#include "Repository.h"
#include <cassert>
class Tests {

public:
	static void runAllTests();

	static void test_user();
	static void test_null_user();

	static void test_repository();
};