#define CATCH_CONFIG_MAIN
#include"../Tasks_2_term/catch.hpp"

#include"sortpack.h"

TEST_CASE("Sort") {
	ArrayOfInt beforeSort{ -1, -9, 33, 45, 18, 2, 0, -5, 40, 1, 4, 6 };
	ArrayOfInt expectedResult{ -9, -5, -1, 0, 1, 2, 4, 6, 18, 33, 40, 45 };

	SortPack sortPack;
	SECTION("bubble") {
		sortPack.attach(beforeSort);
		sortPack.bubble();
		bool isSorted = static_cast<ArrayOfInt&>(sortPack.getItems()) == expectedResult;
		REQUIRE(isSorted == true);
	}
	SECTION("insert") {
		sortPack.attach(beforeSort);
		sortPack.insert();
		bool isSorted = static_cast<ArrayOfInt&>(sortPack.getItems()) == expectedResult;
		REQUIRE(isSorted == true);
	}
	SECTION("select") {
		sortPack.attach(beforeSort);
		sortPack.select();
		bool isSorted = static_cast<ArrayOfInt&>(sortPack.getItems()) == expectedResult;
		REQUIRE(isSorted == true);
	}
	SECTION("quick") {
		sortPack.attach(beforeSort);
		sortPack.quick();
		bool isSorted = static_cast<ArrayOfInt&>(sortPack.getItems()) == expectedResult;
		REQUIRE(isSorted == true);
	}
	SECTION("shell") {
		sortPack.attach(beforeSort);
		sortPack.shell();
		bool isSorted = static_cast<ArrayOfInt&>(sortPack.getItems()) == expectedResult;
		REQUIRE(isSorted == true);
	}
}

TEST_CASE("0 elements") {
	ArrayOfInt beforeSort{};
	ArrayOfInt expectedResult{};

	SortPack sortPack;
	SECTION("bubble") {
		sortPack.attach(beforeSort);
		sortPack.bubble();
		bool isSorted = static_cast<ArrayOfInt&>(sortPack.getItems()) == expectedResult;
		REQUIRE(isSorted == true);
	}
	SECTION("insert") {
		sortPack.attach(beforeSort);
		sortPack.insert();
		bool isSorted = static_cast<ArrayOfInt&>(sortPack.getItems()) == expectedResult;
		REQUIRE(isSorted == true);
	}
	SECTION("select") {
		sortPack.attach(beforeSort);
		sortPack.select();
		bool isSorted = static_cast<ArrayOfInt&>(sortPack.getItems()) == expectedResult;
		REQUIRE(isSorted == true);
	}
	SECTION("quick") {
		sortPack.attach(beforeSort);
		sortPack.quick();
		bool isSorted = static_cast<ArrayOfInt&>(sortPack.getItems()) == expectedResult;
		REQUIRE(isSorted == true);
	}
	SECTION("shell") {
		sortPack.attach(beforeSort);
		sortPack.shell();
		bool isSorted = static_cast<ArrayOfInt&>(sortPack.getItems()) == expectedResult;
		REQUIRE(isSorted == true);
	}
}