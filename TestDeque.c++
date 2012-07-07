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
	// back
	void test_back_1 () {
		C x(10, 3);
		CPPUNIT_ASSERT(x.back() == 3);
	}
	
	void test_back_2 () {
		int a[] = {3, 7, 11};
		C x(a, a+3);
		
		if(DEBUG)cerr << "x.back(): " << x.back() << endl;
		CPPUNIT_ASSERT(!x.empty() );
		CPPUNIT_ASSERT(x.back() == 11);
	}
	
	void test_back_3 () {
		C x;
		CPPUNIT_ASSERT(x.empty() );
		x.push_back(3);
		CPPUNIT_ASSERT(x.back() == 3);
	}
	
	// ---------
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
		x.push_back(7);
		CPPUNIT_ASSERT(x.size() == 2);
		CPPUNIT_ASSERT(x.back() == 7);
	}
	
	void test_push_back_3 () {
		C x (1);
		x.push_back(4);
		CPPUNIT_ASSERT(x.size() == 2);
		CPPUNIT_ASSERT(x.back() == 4);
	}

	// ----
	// front
	void test_front_1 () {
		C x(10, 3);
		CPPUNIT_ASSERT(x.front() == 3);
	}

	void test_front_2 () {
		int a[] = {3, 7, 11};
                C x(a, a+3);
		CPPUNIT_ASSERT(x.front() == 3);
	}

	void test_front_3 () {
		C x;
		CPPUNIT_ASSERT(x.empty());
		x.push_front(3);
		CPPUNIT_ASSERT(x.front() == 3);
	}

    // ----------
    // push_front
    void test_push_front_1 () {
        C x;
		x.push_front(4);
		CPPUNIT_ASSERT(x.size() == 1);
		CPPUNIT_ASSERT(x.front() == 4);
    }

    void test_push_front_2 () {
        C x;
        x.push_front(4);
        x.push_front(7);
        CPPUNIT_ASSERT(x.size() == 2);
        CPPUNIT_ASSERT(x.front() == 7);
    }

    void test_push_front_3 () {
        C x(1);
        x.push_front(4);
        CPPUNIT_ASSERT(x.size() == 2);
        CPPUNIT_ASSERT(x.front() == 4);
    }

    // --------
    // pop_back
    void test_pop_back_1 () {
        int a[] = {3, 7, 11};
		C x(a, a+3);
        x.pop_back();
        CPPUNIT_ASSERT(x.size() == 2);
        CPPUNIT_ASSERT(x.back() == 7);
        x.pop_back();
        CPPUNIT_ASSERT(x.size() == 1);
        CPPUNIT_ASSERT(x.back() == 3);
        x.pop_back();
        CPPUNIT_ASSERT(x.size() == 0);
    }
    
    void test_pop_back_2 () {
    	C x(2, 3);
    	x.pop_back();
    	CPPUNIT_ASSERT(x.size() == 1);
    	CPPUNIT_ASSERT(x.back() == 3);
    }
    
    void test_pop_back_3 () {
    	C x(1);
    	x.pop_back();
    	CPPUNIT_ASSERT(x.size() == 0);
    }
    
    // ---------
    // pop_front
    void test_pop_front_1 () {
    	int a[] = {3, 7, 11};
		C x(a, a+3);
        x.pop_front();
        CPPUNIT_ASSERT(x.size() == 2);
        CPPUNIT_ASSERT(x.front() == 7);
        x.pop_front();
        CPPUNIT_ASSERT(x.size() == 1);
        CPPUNIT_ASSERT(x.front() == 11);
        x.pop_front();
        CPPUNIT_ASSERT(x.size() == 0);
    }
    
    void test_pop_front_2 () {
    	C x(2, 3);
    	x.pop_front();
    	CPPUNIT_ASSERT(x.size() == 1);
    	CPPUNIT_ASSERT(x.front() == 3);
    }
    
    void test_pop_front_3 () {
    	C x(1);
    	x.pop_front();
    	CPPUNIT_ASSERT(x.size() == 0);
    }
    
    // --
    // at
    void test_at_1 () {
    	int a[] = {3, 7, 11};
		C x(a, a+3);
		CPPUNIT_ASSERT(x.at(0) == 3);
		CPPUNIT_ASSERT(x.at(1) == 7);
		CPPUNIT_ASSERT(x.at(2) == 11);
    }
    
    void test_at_2 () {
    	C x(2,3);
    	CPPUNIT_ASSERT(x.at(0) == 3);
    	CPPUNIT_ASSERT(x.at(1) == 3);
    }
    
    void test_at_3 () {
    	C x;
    	x.push_back(3);
    	CPPUNIT_ASSERT(x.at(0) == 3);
    }
    
    void test_at_4 () {
    	C x;
    	try {
    		x.at(0);
    		CPPUNIT_ASSERT(false);
    	}
    	catch (std::out_of_range e) {
    		CPPUNIT_ASSERT(true);
    	}
    }
    
    // ---------
    // subscript
    void test_subscript_1 () {
    	int a[] = {3, 7, 11};
		C x(a, a+3);
		CPPUNIT_ASSERT(x[0] == 3);
		CPPUNIT_ASSERT(x[1] == 7);
		CPPUNIT_ASSERT(x[2] == 11);
    }
    
    void test_subscript_2 () {
    	C x(2,3);
    	CPPUNIT_ASSERT(x[0] == 3);
    	CPPUNIT_ASSERT(x[1] == 3);
    }
    
    void test_subscript_3 () {
    	C x;
    	x.push_back(3);
    	CPPUNIT_ASSERT(x[0] == 3);
    }
	// -----
	// suite
	CPPUNIT_TEST_SUITE(TestDeque);
	
	CPPUNIT_TEST(test_size_1);
	CPPUNIT_TEST(test_size_2);
	CPPUNIT_TEST(test_size_3);
	CPPUNIT_TEST(test_back_1);
	CPPUNIT_TEST(test_back_2);
	CPPUNIT_TEST(test_back_3);
	CPPUNIT_TEST(test_push_back_1);
	CPPUNIT_TEST(test_push_back_2);
	CPPUNIT_TEST(test_push_back_3);
	CPPUNIT_TEST(test_front_1);
	CPPUNIT_TEST(test_front_2);
	CPPUNIT_TEST(test_front_3);
	CPPUNIT_TEST(test_push_front_1);
	CPPUNIT_TEST(test_push_front_2);
	CPPUNIT_TEST(test_push_front_3);
	CPPUNIT_TEST(test_pop_back_1);
	CPPUNIT_TEST(test_pop_back_2);
	CPPUNIT_TEST(test_pop_back_3);
	CPPUNIT_TEST(test_pop_front_1);
	CPPUNIT_TEST(test_pop_front_2);
	CPPUNIT_TEST(test_pop_front_3);
	CPPUNIT_TEST(test_at_1);
	CPPUNIT_TEST(test_at_2);
	CPPUNIT_TEST(test_at_3);
	CPPUNIT_TEST(test_at_4);
	CPPUNIT_TEST(test_subscript_1);
	CPPUNIT_TEST(test_subscript_2);
	CPPUNIT_TEST(test_subscript_3);
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
