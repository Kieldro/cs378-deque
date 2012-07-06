// ----------------------------
// projects/deque/TestDeque.c++
// Copyright (C) 2012
// Glenn P. Downing
/*
To test the program:
	% g++ -ansi -pedantic -lcppunit -ldl -Wall TestDeque.c++ -o TestDeque.c++.app
	% valgrind TestDeque.c++.app >& TestDeque.out
*/

// --------
// includes
#include <algorithm> // equal
#include <cstring>   // strcmp
#include <deque>     // deque
#include <sstream>   // ostringstream
#include <stdexcept> // invalid_argument
#include <string>    // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TestSuite.h"               // TestSuite
#include "cppunit/TextTestRunner.h"          // TestRunner

#include "Deque.h"

// ---------
// TestDeque
template <typename C>
struct TestDeque : CppUnit::TestFixture {
	// ----
	// size
	void test_size_1 () {
		const C x;
		CPPUNIT_ASSERT(x.size() == 0);
	}
	
	void test_size_2 () {
		const C x(2);
		CPPUNIT_ASSERT(x.size() == 2);
	}
	
	void test_size_3 () {
		const C x (1000, 8);
		CPPUNIT_ASSERT(x.size() == 1000);
	}
	
	// ----
	// push_back
	void test_push_back_1 () {
		C x;
		x.push_back(4);
		CPPUNIT_ASSERT(x.size() == 1);
		CPPUNIT_ASSERT(x.back() == 4);
	}
	
	void test_push_back_2 () {
		C x;
		x.push_back(4);
		CPPUNIT_ASSERT(x.size() == 1);
		CPPUNIT_ASSERT(x.back() == 4);
	}
	
	void test_push_back_3 () {
		C x (1);
		x.push_back(4);
		CPPUNIT_ASSERT(x.size() == 2);
		CPPUNIT_ASSERT(x.back() == 4);
	}

	// -----
	// suite
	CPPUNIT_TEST_SUITE(TestDeque);
	
	CPPUNIT_TEST(test_size_1);
	CPPUNIT_TEST(test_size_2);
	CPPUNIT_TEST(test_size_3);
	CPPUNIT_TEST(test_push_back_1);
	CPPUNIT_TEST(test_push_back_2);
	CPPUNIT_TEST(test_push_back_3);
	
	CPPUNIT_TEST_SUITE_END();};

// ----
// main
int main () {
	using namespace std;
	ios_base::sync_with_stdio(false);        // turn off synchronization with C I/O
	cout << "TestDeque.c++" << endl << endl;

	CppUnit::TextTestRunner tr;
	tr.addTest(TestDeque<   deque<int> >::suite());
//	tr.addTest(TestDeque< MyDeque<int> >::suite());
	tr.run();

	cout << "Done." << endl;
	return 0;
}