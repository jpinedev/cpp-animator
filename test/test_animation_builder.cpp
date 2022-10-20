/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#define _CXXTEST_HAVE_EH
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_AnimationBuilderTestSuite_init = false;
#include "animation_builder.cxxtest.hpp"

static AnimationBuilderTestSuite suite_AnimationBuilderTestSuite;

static CxxTest::List Tests_AnimationBuilderTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_AnimationBuilderTestSuite( "animation_builder.cxxtest.hpp", 19, "AnimationBuilderTestSuite", suite_AnimationBuilderTestSuite, Tests_AnimationBuilderTestSuite );

static class TestDescription_suite_AnimationBuilderTestSuite_test_build_empty_file : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_AnimationBuilderTestSuite_test_build_empty_file() : CxxTest::RealTestDescription( Tests_AnimationBuilderTestSuite, suiteDescription_AnimationBuilderTestSuite, 23, "test_build_empty_file" ) {}
 void runTest() { suite_AnimationBuilderTestSuite.test_build_empty_file(); }
} testDescription_suite_AnimationBuilderTestSuite_test_build_empty_file;

static class TestDescription_suite_AnimationBuilderTestSuite_test_build_no_file : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_AnimationBuilderTestSuite_test_build_no_file() : CxxTest::RealTestDescription( Tests_AnimationBuilderTestSuite, suiteDescription_AnimationBuilderTestSuite, 27, "test_build_no_file" ) {}
 void runTest() { suite_AnimationBuilderTestSuite.test_build_no_file(); }
} testDescription_suite_AnimationBuilderTestSuite_test_build_no_file;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
