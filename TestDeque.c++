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
#include <deque>	 // deque
#include <sstream>   // ostringstream
#include <stdexcept> // invalid_argument
#include <string>	// ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"			 // TestFixture
#include "cppunit/TestSuite.h"			   // TestSuite
#include "cppunit/TextTestRunner.h"		  // TestRunner

#include "Deque.h"

// ---------
// TestDeque
template <typename C>
struct TestDeque : CppUnit::TestFixture {
	// ----
	// constructor
	void test_constructor_1 () {
		C x;
		CPPUNIT_ASSERT(x.size() == 0);
	}
	
	void test_constructor_2 () {
		C x(3);
		CPPUNIT_ASSERT(x.size() == 3);
	}
	
	void test_constructor_3 () {
		if(DEBUG)cerr << "test_constructor_3: " << endl;
		C x(3, 11);
		if(DEBUG)cerr << "x: " << x[0] << endl;
		CPPUNIT_ASSERT(x.size() == 3);
		CPPUNIT_ASSERT(x[0] == 11);
		CPPUNIT_ASSERT(x[1] == 11);
		CPPUNIT_ASSERT(x[2] == 11);
	}
	
	void test_constructor_4 () {
		C x(3, 11);
		C y(x);
		CPPUNIT_ASSERT(x[0] == 11);
		CPPUNIT_ASSERT(x[1] == 11);
		CPPUNIT_ASSERT(x[2] == 11);
		CPPUNIT_ASSERT(y.size() == 3);
		if(DEBUG)cerr << "y[0] = " << y[0] << endl;
		CPPUNIT_ASSERT(y[0] == 11);
		CPPUNIT_ASSERT(y[1] == 11);
		CPPUNIT_ASSERT(y[2] == 11);
	}
	
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
		C x(3,11);
		CPPUNIT_ASSERT(!x.empty() );
		CPPUNIT_ASSERT(x.back() == 11);
	}
	
	void test_back_3 () {
		C x;
		CPPUNIT_ASSERT(x.empty() );
		x.push_back(3);
		CPPUNIT_ASSERT(x.back() == 3);
	}

	// ----------
	// back const
	void test_back_const_1 () {
		const C x(1,3);
		CPPUNIT_ASSERT(x.back() == 3);
	}

	void test_back_const_2 () {
		const C x(3, 11);
		CPPUNIT_ASSERT(x.back() == 11);
	}

	void test_back_const_3 () {
		const C x(100, 7);
		CPPUNIT_ASSERT(x.back() == 7);
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
		C x(3,11);
		CPPUNIT_ASSERT(x.front() == 11);
	}

	void test_front_3 () {
		C x;
		CPPUNIT_ASSERT(x.empty());
		x.push_front(3);
		CPPUNIT_ASSERT(x.front() == 3);
	}
	
	// -----------
	// front_const
	void test_front_const_1 () {
		const C x(10, 3);
		CPPUNIT_ASSERT(x.front() == 3);
	}

	void test_front_const_2 () {
		const C x(3, 11);
		CPPUNIT_ASSERT(x.front() == 11);
	}

	void test_front_const_3 () {
		const C x(100, 7);
		CPPUNIT_ASSERT(x.front() == 7);
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
		C x(3,11);
		x.pop_back();
		CPPUNIT_ASSERT(x.size() == 2);
		CPPUNIT_ASSERT(x.back() == 11);
		x.pop_back();
		CPPUNIT_ASSERT(x.size() == 1);
		CPPUNIT_ASSERT(x.back() == 11);
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
		C x(3,11);
		x.pop_front();
		CPPUNIT_ASSERT(x.size() == 2);
		CPPUNIT_ASSERT(x.front() == 11);
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
		C x(3,11);
		CPPUNIT_ASSERT(x.at(0) == 11);
		CPPUNIT_ASSERT(x.at(1) == 11);
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
		C x(3,11);
		CPPUNIT_ASSERT(x[0] == 11);
		CPPUNIT_ASSERT(x[1] == 11);
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
	// begin
	void test_begin_1 () {
		C x;
		typename C::iterator b = x.begin();
		CPPUNIT_ASSERT(b == x.begin() );
	}
	
	void test_begin_2 () {
		C x(5);
		typename C::iterator b = x.begin();
		CPPUNIT_ASSERT(b == x.begin() );
	}
	
	void test_begin_3 () {
		C x(3, 2);
		typename C::iterator b = x.begin();
		CPPUNIT_ASSERT(*b == 2);
	}
	
	// ---
	// end
	void test_end_1 () {
		C x(5);
		typename C::iterator e = x.end();
		CPPUNIT_ASSERT(e == x.begin()+5 );
	}
	
	void test_end_2 () {
		C x;
		typename C::iterator e = x.end();
		CPPUNIT_ASSERT(e == x.begin() );
	}
	
	void test_end_3 () {
		C x(3, 2);
		typename C::iterator e = x.end();
		CPPUNIT_ASSERT(e != x.begin() );
		CPPUNIT_ASSERT(e == x.begin()+3 );
	}
	
	// ------
	// insert
	void test_insert_1 () {
		C x;
		x.insert(x.begin(), 5);
		CPPUNIT_ASSERT(x[0] == 5);
		CPPUNIT_ASSERT(x.size() == 1);
	}
	
	void test_insert_2 () {
		C x(3);
		x.insert(x.begin()+1, 7);
		CPPUNIT_ASSERT(x[1] == 7);
		CPPUNIT_ASSERT(x.size() == 4);
	}
	
	void test_insert_3 () {
		C x(3,11);
		x.insert(x.begin()+3, 13);
		CPPUNIT_ASSERT(x[3] == 13);
		CPPUNIT_ASSERT(x.size() == 4);
	}
	
	void test_insert_4 () {
		C x(3,11);
		x.insert(x.begin(), 13);
		CPPUNIT_ASSERT(x[0] == 13);
		CPPUNIT_ASSERT(x.size() == 4);
	}
	
	// ------
	// resize
	void test_resize_1 () {
		C x;
		CPPUNIT_ASSERT(x.size() == 0);
		x.resize(3);
		CPPUNIT_ASSERT(x.size() == 3);
	}
	
	void test_resize_2 () {
		C x(5);
		CPPUNIT_ASSERT(x.size() == 5);
		x.resize(7);
		CPPUNIT_ASSERT(x.size() == 7);
	}
	
	void test_resize_3 () {
		C x(5);
		CPPUNIT_ASSERT(x.size() == 5);
		x.resize(3);
		CPPUNIT_ASSERT(x.size() == 3);
	}
	
	void test_resize_4 () {
		C x(5);
		CPPUNIT_ASSERT(x.size() == 5);
		x.resize(11, 7);
		CPPUNIT_ASSERT(x.size() == 11);
		CPPUNIT_ASSERT(x[5] == 7);
		CPPUNIT_ASSERT(x[6] == 7);
		CPPUNIT_ASSERT(x[10] == 7);
	}
	
	void test_resize_5 () {
		C x(5,7);
		CPPUNIT_ASSERT(x.size() == 5);
		x.resize(3);
		CPPUNIT_ASSERT(x.size() == 3);
		CPPUNIT_ASSERT(x[0] == 7);
		CPPUNIT_ASSERT(x[1] == 7);
		CPPUNIT_ASSERT(x[2] == 7);
	}
	
	void test_resize_6 () {
		C x(5,7);
		CPPUNIT_ASSERT(x.size() == 5);
		x.resize(3, 2);
		CPPUNIT_ASSERT(x.size() == 3);
		CPPUNIT_ASSERT(x[0] == 7);
		CPPUNIT_ASSERT(x[1] == 7);
		CPPUNIT_ASSERT(x[2] == 7);
	}
	
	// -----
	// erase
	void test_erase_1 () {
		C x(5,17);
		x.erase(x.begin()+0);
		CPPUNIT_ASSERT(x.size() == 4);
		CPPUNIT_ASSERT(x[0] == 17);
	}
	
	void test_erase_2 () {
		C x(5,17);
		x.erase(x.begin()+2);
		CPPUNIT_ASSERT(x.size() == 4);
		CPPUNIT_ASSERT(x[0] == 17);
		CPPUNIT_ASSERT(x[1] == 17);
		CPPUNIT_ASSERT(x[2] == 17);
		CPPUNIT_ASSERT(x[3] == 17);
	}
	
	void test_erase_3 () {
		C x(5,17);
		x.erase(x.begin()+5);
		CPPUNIT_ASSERT(x.size() == 4);
		CPPUNIT_ASSERT(x[3] == 17);
	}
	
	// -----
	// swap
	void test_swap_1 () {
		C x(3, 7);
		C y(3, 5);
		x.swap(y);
		CPPUNIT_ASSERT(x.size() == 3);
		CPPUNIT_ASSERT(y.size() == 3);
		CPPUNIT_ASSERT(x[0] == 5);
		CPPUNIT_ASSERT(y[0] == 7);
	}
	
	void test_swap_2 () {
		C x(3, 7);
		C y(2, 5);
		x.swap(y);
		CPPUNIT_ASSERT(x.size() == 2);
		CPPUNIT_ASSERT(y.size() == 3);
		CPPUNIT_ASSERT(x[0] == 5);
		CPPUNIT_ASSERT(y[0] == 7);
	}
	
	void test_swap_3 () {
		C x(5, 17);
		C y(2, 5);
		x.swap(y);
		CPPUNIT_ASSERT(x.size() == 2);
		CPPUNIT_ASSERT(y.size() == 5);
		CPPUNIT_ASSERT(x[0] == 5);
		CPPUNIT_ASSERT(x[1] == 5);
		CPPUNIT_ASSERT(y[0] == 17);
		CPPUNIT_ASSERT(y[1] == 17);
		CPPUNIT_ASSERT(y[2] == 17);
		CPPUNIT_ASSERT(y[3] == 17);
		CPPUNIT_ASSERT(y[4] == 17);
	}
	
	// -----
	// clear
	void test_clear_1 () {
		C x(3, 7);
		x.clear();
		CPPUNIT_ASSERT(x.size() == 0);
	}
	
	void test_clear_2 () {
		C x;
		x.clear();
		CPPUNIT_ASSERT(x.size() == 0);
	}
	
	void test_clear_3 () {
		C x(3,17);
		x.clear();
		CPPUNIT_ASSERT(x.size() == 0);
		x.push_back(3);
		CPPUNIT_ASSERT(x[0] == 3);
	}
	
	// ------
	// op equal
	void test_op_equal_1 () {
		C x(5,17);
		C y(3, -2);
		y = x;
		CPPUNIT_ASSERT(y.size() == 5);
		CPPUNIT_ASSERT(x.size() == 5);
		CPPUNIT_ASSERT(y[0] == 17);
		CPPUNIT_ASSERT(y[1] == 17);
		CPPUNIT_ASSERT(y[2] == 17);
		CPPUNIT_ASSERT(y[3] == 17);
		CPPUNIT_ASSERT(y[4] == 17);
		y[1] = -23;
		CPPUNIT_ASSERT(x[1] == 17);
	}
	
	void test_op_equal_2 () {
		C x;
		C y(3, -2);
		y = x;
		CPPUNIT_ASSERT(y.size() == 0);
		CPPUNIT_ASSERT(x.size() == 0);
		CPPUNIT_ASSERT(y.empty() );
		y.push_front(1);
		CPPUNIT_ASSERT(x.empty() );
	}
	
	void test_op_equal_3 () {
		C x(3);
		C y(1);
		y = x;
		CPPUNIT_ASSERT(y.size() == 3);
		CPPUNIT_ASSERT(x.size() == 3);
		CPPUNIT_ASSERT(!y.empty() );
		y.push_back(1);
		CPPUNIT_ASSERT(x.size() == 3 );
	}
	
	// -----
	// suite
	CPPUNIT_TEST_SUITE(TestDeque);
	
	CPPUNIT_TEST(test_constructor_1);
	CPPUNIT_TEST(test_constructor_2);
	CPPUNIT_TEST(test_constructor_3);
	CPPUNIT_TEST(test_constructor_4);
	CPPUNIT_TEST(test_size_1);
	CPPUNIT_TEST(test_size_2);
	CPPUNIT_TEST(test_back_1);
	CPPUNIT_TEST(test_back_2);
	CPPUNIT_TEST(test_back_3);
	CPPUNIT_TEST(test_back_const_1);
        CPPUNIT_TEST(test_back_const_2);
        CPPUNIT_TEST(test_back_const_3);
	CPPUNIT_TEST(test_push_back_1);
	CPPUNIT_TEST(test_push_back_2);
	CPPUNIT_TEST(test_push_back_3);
	CPPUNIT_TEST(test_front_1);
	CPPUNIT_TEST(test_front_2);
	CPPUNIT_TEST(test_front_3);
	CPPUNIT_TEST(test_front_const_1);
        CPPUNIT_TEST(test_front_const_2);
        CPPUNIT_TEST(test_front_const_3);
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
	CPPUNIT_TEST(test_begin_1);
	CPPUNIT_TEST(test_begin_2);
	CPPUNIT_TEST(test_begin_3);
	CPPUNIT_TEST(test_end_1);
	CPPUNIT_TEST(test_end_2);
	CPPUNIT_TEST(test_end_3);
	CPPUNIT_TEST(test_insert_1);
	CPPUNIT_TEST(test_insert_2);
	CPPUNIT_TEST(test_insert_3);
	CPPUNIT_TEST(test_insert_4);
	CPPUNIT_TEST(test_resize_1);
	CPPUNIT_TEST(test_resize_2);
	CPPUNIT_TEST(test_resize_3);
	CPPUNIT_TEST(test_resize_4);
	CPPUNIT_TEST(test_resize_5);
	CPPUNIT_TEST(test_erase_1);
	CPPUNIT_TEST(test_erase_2);
	CPPUNIT_TEST(test_erase_3);
	CPPUNIT_TEST(test_swap_1);
	CPPUNIT_TEST(test_swap_2);
	CPPUNIT_TEST(test_swap_3);
	CPPUNIT_TEST(test_clear_1);
	CPPUNIT_TEST(test_clear_2);
	CPPUNIT_TEST(test_clear_3);
	CPPUNIT_TEST(test_op_equal_1);
	CPPUNIT_TEST(test_op_equal_2);
	CPPUNIT_TEST(test_op_equal_3);
	
	CPPUNIT_TEST_SUITE_END();
};

// ----
// main
int main () {
	using namespace std;
	ios_base::sync_with_stdio(false);		// turn off synchronization with C I/O
	cout << "TestDeque.c++" << endl << endl;

	CppUnit::TextTestRunner tr;
	tr.addTest(TestDeque<   deque<int> >::suite() );
	//tr.addTest(TestDeque< MyDeque<int> >::suite() );
	tr.run();

	cout << "Done." << endl;
	return 0;
}
