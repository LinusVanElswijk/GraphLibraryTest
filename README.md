GraphLibraryTest
================

Unit test for GraphLibrary

This unit test program uses the boost test library to check if the
GraphLibrary is working the way it is expected to work.

Each test suite tests a single class of the GraphLibrary.
Each test case tests a setter function of a class.
All functions that change the state of a class/object are considered to be setters and these functions will all get their own test case. This includes constructors and destructors.
Functions that don't change the state of a class/object are considered to be getters.
In each test-case, the return values of all related getters are compared to the expected return values after a setter is called.
If a test fails, then either the set function didn't change the state correctly, or the get functions didn't return the right value for the state.
Because all tests are done this way, the unit test is completely implementation indepent.
 
Each cpp in the test library corresponds with a test suite (except Main.cpp).
