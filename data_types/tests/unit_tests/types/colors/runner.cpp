/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
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
bool suite_vector_tests_init = false;
#include "/home/mehoggan/Devel/Sandbox/data_types/tests/unit_tests/types/points/type_point.h"

static vector_tests suite_vector_tests;

static CxxTest::List Tests_vector_tests = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_vector_tests( "type_point.h", 12, "vector_tests", suite_vector_tests, Tests_vector_tests );

static class TestDescription_suite_vector_tests_test_point_2d_float : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_vector_tests_test_point_2d_float() : CxxTest::RealTestDescription( Tests_vector_tests, suiteDescription_vector_tests, 15, "test_point_2d_float" ) {}
 void runTest() { suite_vector_tests.test_point_2d_float(); }
} testDescription_suite_vector_tests_test_point_2d_float;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
