#include "pch.h"

TEST(TestOne, TestTrue) {
	ASSERT_EQ(true, false);
}

TEST(TestOne, TestFalse) {
	ASSERT_EQ(true, true);
}

TEST(TestOne, TestOther) {
	ASSERT_EQ(true, 3);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}