#include "jugs.h"

#include <limits.h>

#include "gtest/gtest.h"
#include "tester.h"

extern Testharness g_testharness;
namespace {


TEST(JugsTest, State) {
	State s;
}

TEST(JugsTest, Wrapup) {
	g_testharness.printCoverage();
}
}  // namespace

