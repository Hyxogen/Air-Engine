#include "pch.h"

TEST(TestOne, TestYes) {
	ASSERT_EQ(true, true);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}