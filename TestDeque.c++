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

	// ITERATOR TESTS
	// ------------------
	// test_iter_equality
	void test_iter_equality_1() {
		C d(9, 5);
		typename C::iterator it1 = d.begin();
		typename C::iterator it2 = d.begin();
		CPPUNIT_ASSERT(it1 == it2);
		it1 = d.begin() + 9;
	    CPPUNIT_ASSERT(it1 != it2);
		it2 = d.end();
		CPPUNIT_ASSERT(it1 == it2);
	}

	void test_iter_equality_2() {
		C d(13, 200);
		C e(13, 200);
		typename C::iterator it1 = d.begin();
		typename C::iterator it2 = e.begin();
		CPPUNIT_ASSERT(it1 != it2);
		it1 = d.end();
		it2 = e.end();
		CPPUNIT_ASSERT(it1 != it2);
	}

	void test_iter_equality_3() {
		C d(10, 3);
		typename C::iterator it1 = d.begin() + 3;
		typename C::iterator it2 = d.begin() + 7;
		CPPUNIT_ASSERT(it1 != it2);
		it1 = it2;
		CPPUNIT_ASSERT(it1 == it2);
		--it1;
		CPPUNIT_ASSERT(it1 != it2);
		++it1;
		CPPUNIT_ASSERT(it1 == it2);
	}

	void test_iter_equality_4() {
		C d(808, 300);
		typename C::iterator it1 = d.begin() + 3;
		typename C::iterator it2 = d.begin() + 7;
		CPPUNIT_ASSERT(it1 != it2);
		it1 = it2;
		CPPUNIT_ASSERT(it1 == it2);
		it1 = it2 = d.end();
		CPPUNIT_ASSERT(it1 == it2);
		--it1;
		CPPUNIT_ASSERT(it1 != it2);
		++it1;
		CPPUNIT_ASSERT(it1 == it2);
	}

	// --------------
	// test_iter_plus
	void test_iter_plus_1() {
		C d(9, 5);
		typename C::iterator it1 = d.begin();
		it1 = it1 + 9;
		typename C::iterator it2 = d.end();
		CPPUNIT_ASSERT(it1 == it2);
	}

	void test_iter_plus_2() {
		const int x = 3;
		const int y = 200;
		C d(x, y);
		typename C::iterator it1 = d.begin();

		for (int i = 0; i < x; ++i) {
			CPPUNIT_ASSERT(*it1 == y);
			it1 = it1 + 1;
		}
		CPPUNIT_ASSERT(it1 == d.end());
	}

	void test_iter_plus_3() {
		C d(1, 100);
		d.push_front(99);
		d.push_back(101);
		typename C::iterator it1 = d.begin();
        CPPUNIT_ASSERT(*it1 == 99);
		it1 += 1;
		CPPUNIT_ASSERT(*it1 == 100);
		++it1;
		CPPUNIT_ASSERT(*it1 == 101);
	}

	void test_iter_plus_4() {
		C d(512, 5);
		typename C::iterator it1 = d.begin();
		it1 = it1 + 512;
		typename C::iterator it2 = d.end();
		CPPUNIT_ASSERT(it1 == it2);
	}

	// ---------------
	// test_iter_minus
	void test_iter_minus_1() {
		C d(9, 5);
		typename C::iterator it1 = d.end();
		it1 = it1 - 9;
		typename C::iterator it2 = d.begin();
		CPPUNIT_ASSERT(it1 == it2);
	}

	void test_iter_minus_2() {
		const int x = 3;
		const int y = 200;
		C d(x, y);
		typename C::iterator it1 = d.end();

		for (int i = x; i > 0; --i) {
            --it1;
			CPPUNIT_ASSERT(*it1 == y);
		}
		CPPUNIT_ASSERT(it1 == d.begin());
	}

	void test_iter_minus_3() {
		C d(1, 100);
		d.push_front(99);
		d.push_back(101);
		typename C::iterator it1 = d.end() - 1;
        CPPUNIT_ASSERT(*it1 == 101);
		it1 -= 1;
		CPPUNIT_ASSERT(*it1 == 100);
		--it1;
		CPPUNIT_ASSERT(*it1 == 99);
	}

	void test_iter_minus_4() {
		C d(512, 5);
		typename C::iterator it1 = d.end();
		it1 = it1 - 512;
		typename C::iterator it2 = d.begin();
		CPPUNIT_ASSERT(it1 == it2);
	}

	// ---------------------
	// test_iter_dereference
	void test_iter_dereference_1() {
		C d(11, 6);
		for(int i = 0; i < 6; ++i)
		    d.push_back(i);
		typename C::iterator it1 = d.end() - 6;
		CPPUNIT_ASSERT(*it1 == 0);
		typename C::iterator it2 = d.begin() + 10;
		CPPUNIT_ASSERT(*it2 == 6);
		++it2;

		// it1 and it2 both point to 0, after the 11 6's
		for(int i = 0; i < 6; ++i) {
			CPPUNIT_ASSERT(*it2 == i);
			CPPUNIT_ASSERT(*it1 == *it2);
			CPPUNIT_ASSERT(it1 == it2);
			++it1;
			++it2;
		}

		typename C::iterator it3 = d.begin();
		for (int i = 0; i < 17; ++i) {
			*it3 = i + 10;
			++it3;
		}
		it3 = d.begin();
		for (int i = 0; i < 17; ++i) {
			CPPUNIT_ASSERT(*it3 == i + 10);
			++it3;
		}
	}

	void test_iter_dereference_2() {
		C d;
		d.push_back(5); 
		d.push_front(0);
		d.push_back(11);
		typename C::iterator it1 = d.begin();
		CPPUNIT_ASSERT(*it1 == 0);
		CPPUNIT_ASSERT(*(d.end() - 1) == 11);
		++it1;
		CPPUNIT_ASSERT(*it1 == 5);
		*it1 = 2000;
		CPPUNIT_ASSERT(*it1 == 2000);
	}

	void test_iter_dereference_3() {
		C d(9, 0);
		d.push_back(-1); 
		d.push_front(-1);
		CPPUNIT_ASSERT(*(d.begin()) == -1);
		CPPUNIT_ASSERT(*(d.end() - 1) == -1);
		typename C::iterator it1 = d.end();
		it1 -= 5;
		CPPUNIT_ASSERT(*it1 == 0);
		*it1 = 777;
		CPPUNIT_ASSERT(*it1 == 777);
	}

	void test_iter_dereference_4() {
		C d(900, 6);
		for(int i = 0; i < 6; ++i)
		    d.push_back(i);
		typename C::iterator it1 = d.end() - 6;
		CPPUNIT_ASSERT(*it1 == 0);
		typename C::iterator it2 = d.begin() + 899;
		CPPUNIT_ASSERT(*it2 == 6);
		++it2;

		for(int i = 0; i < 6; ++i) {
			CPPUNIT_ASSERT(*it2 == i);
			CPPUNIT_ASSERT(*it1 == *it2);
			CPPUNIT_ASSERT(it1 == it2);
			++it1;
			++it2;
		}
	}

	// --------------
	// iter_increment
	void test_iter_increment_1() {
		C d;
		for (int i = 0; i < 600; ++i)
			d.push_back(i);

		typename C::iterator it = d.begin();
		for (int i = 0; i < 600; ++i) {
			CPPUNIT_ASSERT(*it == i);
			++it;
		}

		typename C::iterator it2 = d.end();
		CPPUNIT_ASSERT(it == it2);
	}

	void test_iter_increment_2() {
		C d(1, 5);
		typename C::iterator it1 = d.begin();
		CPPUNIT_ASSERT(*it1 == 5);
		++it1;
		typename C::iterator it2 = d.end();
		CPPUNIT_ASSERT(it1 == it2);
	}

	void test_iter_increment_3() {
		C d;
		d.push_back(10);
		d.push_back(11);

		typename C::iterator it1 = d.begin();
		typename C::iterator it2 = it1++;
		CPPUNIT_ASSERT(*it1 == 11);
		CPPUNIT_ASSERT(*it2 == 10);
		it1++;
		CPPUNIT_ASSERT(it1 == d.end());
	}

	// --------------
	// iter_decrement
	void test_iter_decrement_1() {
		C d;
		for (int i = 0; i < 600; ++i)
			d.push_back(i);

		typename C::iterator it = d.end();
		for (int i = 599; i >= 0; --i) {
			--it;
			CPPUNIT_ASSERT(*it == i);
		}

		typename C::iterator it2 = d.begin();
		CPPUNIT_ASSERT(it == it2);
	}

	void test_iter_decrement_2() {
		C d(1, 5);
		typename C::iterator it1 = d.end();
		--it1;
		CPPUNIT_ASSERT(*it1 == 5);
		typename C::iterator it2 = d.begin();
		CPPUNIT_ASSERT(it1 == it2);
	}

	void test_iter_decrement_3() {
		C d;
		d.push_back(10);
		d.push_back(11);

		typename C::iterator it1 = d.end();
		typename C::iterator it2 = it1--;
		CPPUNIT_ASSERT(it2 == d.end());
		CPPUNIT_ASSERT(*it1 == 11);
		it1--;
		CPPUNIT_ASSERT(*it1 == 10);
		CPPUNIT_ASSERT(it1 == d.begin());
	}

	// ---------------------
	// test_iter_plus_equals
	void test_iter_plus_equals_1() {
		C d(9, 5);
		typename C::iterator it1 = d.begin();
		it1 += 9;
		typename C::iterator it2 = d.end();
		CPPUNIT_ASSERT(it1 == it2);
	}

	void test_iter_plus_equals_2() {
		const int x = 3;
		const int y = 200;
		C d(x, y);
		typename C::iterator it1 = d.begin();

		for (int i = 0; i < x; ++i) {
			CPPUNIT_ASSERT(*it1 == y);
			it1 += 1;
		}
		CPPUNIT_ASSERT(it1 == d.end());
	}

	void test_iter_plus_equals_3() {
		C d(512, 5);
		typename C::iterator it1 = d.begin();
		it1 += 512;
		typename C::iterator it2 = d.end();
		CPPUNIT_ASSERT(it1 == it2);
	}

	// ----------------------
	// test_iter_minus_equals
	void test_iter_minus_equals_1() {
		C d(9, 5);
		typename C::iterator it1 = d.end();
		it1 -= 9;
		typename C::iterator it2 = d.begin();
		CPPUNIT_ASSERT(it1 == it2);
	}

	void test_iter_minus_equals_2() {
		const int x = 3;
		const int y = 200;
		C d(x, y);
		typename C::iterator it1 = d.end();

		for (int i = x; i > 0; --i) {
            it1 -= 1;
			CPPUNIT_ASSERT(*it1 == y);
		}
		CPPUNIT_ASSERT(it1 == d.begin());
	}

	void test_iter_minus_equals_3() {
		C d(1, 100);
		d.push_front(99);
		d.push_back(101);
		typename C::iterator it1 = d.end();
		it1 -= 1;
        CPPUNIT_ASSERT(*it1 == 101);
		it1 -= 1;
		CPPUNIT_ASSERT(*it1 == 100);
		it1 -= 1;
		CPPUNIT_ASSERT(*it1 == 99);
	}

	void test_iter_minus_equals_4() {
		C d(512, 5);
		typename C::iterator it1 = d.end();
		it1 -= 512;
		typename C::iterator it2 = d.begin();
		CPPUNIT_ASSERT(it1 == it2);
	}

	// CONST_ITERATOR TESTS

	// ------------------------
	// test_const_iter_equality
	void test_const_iter_equality_1() {
		const C d(9, 5);
		typename C::const_iterator it1 = d.begin();
		typename C::const_iterator it2 = d.begin();
		CPPUNIT_ASSERT(it1 == it2);
		it1 = d.begin() + 9;
	    CPPUNIT_ASSERT(it1 != it2);
		it2 = d.end();
		CPPUNIT_ASSERT(it1 == it2);
	}

	void test_const_iter_equality_2() {
		const C d(13, 200);
		const C e(13, 200);
		typename C::const_iterator it1 = d.begin();
		typename C::const_iterator it2 = e.begin();
		CPPUNIT_ASSERT(it1 != it2);
		it1 = d.end();
		it2 = e.end();
		CPPUNIT_ASSERT(it1 != it2);
	}

	void test_const_iter_equality_3() {
		const C d(10, 3);
		typename C::const_iterator it1 = d.begin() + 3;
		typename C::const_iterator it2 = d.begin() + 7;
		CPPUNIT_ASSERT(it1 != it2);
		it1 = it2;
		CPPUNIT_ASSERT(it1 == it2);
		--it1;
		CPPUNIT_ASSERT(it1 != it2);
		++it1;
		CPPUNIT_ASSERT(it1 == it2);
	}

	void test_const_iter_equality_4() {
		const C d(808, 300);
		typename C::const_iterator it1 = d.begin() + 3;
		typename C::const_iterator it2 = d.begin() + 7;
		CPPUNIT_ASSERT(it1 != it2);
		it1 = it2;
		CPPUNIT_ASSERT(it1 == it2);
		it1 = it2 = d.end();
		CPPUNIT_ASSERT(it1 == it2);
		--it1;
		CPPUNIT_ASSERT(it1 != it2);
		++it1;
		CPPUNIT_ASSERT(it1 == it2);
	}

	// --------------------
	// test_const_iter_plus
	void test_const_iter_plus_1() {
		const C d(9, 5);
		typename C::const_iterator it1 = d.begin();
		it1 = it1 + 9;
		typename C::const_iterator it2 = d.end();
		CPPUNIT_ASSERT(it1 == it2);
	}

	void test_const_iter_plus_2() {
		const int x = 3;
		const int y = 200;
		const C d(x, y);
		typename C::const_iterator it1 = d.begin();

		for (int i = 0; i < x; ++i) {
			CPPUNIT_ASSERT(*it1 == y);
			it1 = it1 + 1;
		}
		CPPUNIT_ASSERT(it1 == d.end());
	}

	void test_const_iter_plus_3() {
		C d(1, 100);
		d.push_front(99);
		d.push_back(101);
		const C e(d);

		typename C::const_iterator it1 = e.begin();
        CPPUNIT_ASSERT(*it1 == 99);
		it1 += 1;
		CPPUNIT_ASSERT(*it1 == 100);
		++it1;
		CPPUNIT_ASSERT(*it1 == 101);
	}

	void test_const_iter_plus_4() {
		const C d(512, 5);
		typename C::const_iterator it1 = d.begin();
		it1 = it1 + 512;
		typename C::const_iterator it2 = d.end();
		CPPUNIT_ASSERT(it1 == it2);
	}

	// ---------------------
	// test_const_iter_minus
	void test_const_iter_minus_1() {
		const C d(9, 5);
		typename C::const_iterator it1 = d.end();
		it1 = it1 - 9;
		typename C::const_iterator it2 = d.begin();
		CPPUNIT_ASSERT(it1 == it2);
	}

	void test_const_iter_minus_2() {
		const int x = 3;
		const int y = 200;
		const C d(x, y);
		typename C::const_iterator it1 = d.end();

		for (int i = x; i > 0; --i) {
            --it1;
			CPPUNIT_ASSERT(*it1 == y);
		}
		CPPUNIT_ASSERT(it1 == d.begin());
	}

	void test_const_iter_minus_3() {
		C e(1, 100);
		e.push_front(99);
		e.push_back(101);
		const C d(e);

		typename C::const_iterator it1 = d.end() - 1;
        CPPUNIT_ASSERT(*it1 == 101);
		it1 -= 1;
		CPPUNIT_ASSERT(*it1 == 100);
		--it1;
		CPPUNIT_ASSERT(*it1 == 99);
	}

	void test_const_iter_minus_4() {
		const C d(512, 5);
		typename C::const_iterator it1 = d.end();
		it1 = it1 - 512;
		typename C::const_iterator it2 = d.begin();
		CPPUNIT_ASSERT(it1 == it2);
	}

	// ---------------------------
	// test_const_iter_dereference
	void test_const_iter_dereference_1() {
		C e(11, 6);
		for(int i = 0; i < 6; ++i)
		    e.push_back(i);
		const C d(e);
		typename C::const_iterator it1 = d.end() - 6;
		CPPUNIT_ASSERT(*it1 == 0);
		typename C::const_iterator it2 = d.begin() + 10;
		CPPUNIT_ASSERT(*it2 == 6);
		++it2;

		// it1 and it2 both point to 0, after the 11 6's
		for(int i = 0; i < 6; ++i) {
			CPPUNIT_ASSERT(*it2 == i);
			CPPUNIT_ASSERT(*it1 == *it2);
			CPPUNIT_ASSERT(it1 == it2);
			++it1;
			++it2;
		}
	}

	void test_const_iter_dereference_2() {
		C e;
		e.push_back(5); 
		e.push_front(0);
		e.push_back(11);
		const C d(e);

		typename C::const_iterator it1 = d.begin();
		CPPUNIT_ASSERT(*it1 == 0);
		CPPUNIT_ASSERT(*(d.end() - 1) == 11);
		++it1;
		CPPUNIT_ASSERT(*it1 == 5);
	}

	void test_const_iter_dereference_3() {
		C e(9, 0);
		e.push_back(-1); 
		e.push_front(-1);
		const C d(e);

		CPPUNIT_ASSERT(*(d.begin()) == -1);
		CPPUNIT_ASSERT(*(d.end() - 1) == -1);
		typename C::const_iterator it1 = d.end();
		it1 -= 5;
		CPPUNIT_ASSERT(*it1 == 0);
	}

	void test_const_iter_dereference_4() {
		C e(900, 6);
		for(int i = 0; i < 6; ++i)
		    e.push_back(i);
		const C d(e);

		typename C::const_iterator it1 = d.end() - 6;
		CPPUNIT_ASSERT(*it1 == 0);
		typename C::const_iterator it2 = d.begin() + 899;
		CPPUNIT_ASSERT(*it2 == 6);
		++it2;

		for(int i = 0; i < 6; ++i) {
			CPPUNIT_ASSERT(*it2 == i);
			CPPUNIT_ASSERT(*it1 == *it2);
			CPPUNIT_ASSERT(it1 == it2);
			++it1;
			++it2;
		}
	}

	// --------------------
	// const_iter_increment
	void test_const_iter_increment_1() {
		C e;
		for (int i = 0; i < 600; ++i)
			e.push_back(i);
		const C d(e);

		typename C::const_iterator it = d.begin();
		for (int i = 0; i < 600; ++i) {
			CPPUNIT_ASSERT(*it == i);
			++it;
		}

		typename C::const_iterator it2 = d.end();
		CPPUNIT_ASSERT(it == it2);
	}

	void test_const_iter_increment_2() {
		const C d(1, 5);
		typename C::const_iterator it1 = d.begin();
		CPPUNIT_ASSERT(*it1 == 5);
		++it1;
		typename C::const_iterator it2 = d.end();
		CPPUNIT_ASSERT(it1 == it2);
	}

	void test_const_iter_increment_3() {
		C e;
		e.push_back(10);
		e.push_back(11);
		const C d(e);

		typename C::const_iterator it1 = d.begin();
		typename C::const_iterator it2 = it1++;
		CPPUNIT_ASSERT(*it1 == 11);
		CPPUNIT_ASSERT(*it2 == 10);
		it1++;
		CPPUNIT_ASSERT(it1 == d.end());
	}

	// --------------------
	// const_iter_decrement
	void test_const_iter_decrement_1() {
		C e;
		for (int i = 0; i < 600; ++i)
			e.push_back(i);
		const C d(e);

		typename C::const_iterator it = d.end();
		for (int i = 599; i >= 0; --i) {
			--it;
			CPPUNIT_ASSERT(*it == i);
		}

		typename C::const_iterator it2 = d.begin();
		CPPUNIT_ASSERT(it == it2);
	}

	void test_const_iter_decrement_2() {
		const C d(1, 5);
		typename C::const_iterator it1 = d.end();
		--it1;
		CPPUNIT_ASSERT(*it1 == 5);
		typename C::const_iterator it2 = d.begin();
		CPPUNIT_ASSERT(it1 == it2);
	}

	void test_const_iter_decrement_3() {
		C e;
		e.push_back(10);
		e.push_back(11);
		const C d(e);

		typename C::const_iterator it1 = d.end();
		typename C::const_iterator it2 = it1--;
		CPPUNIT_ASSERT(it2 == d.end());
		CPPUNIT_ASSERT(*it1 == 11);
		it1--;
		CPPUNIT_ASSERT(*it1 == 10);
		CPPUNIT_ASSERT(it1 == d.begin());
	}

	// ---------------------------
	// test_const_iter_plus_equals
	void test_const_iter_plus_equals_1() {
		const C d(9, 5);
		typename C::const_iterator it1 = d.begin();
		it1 += 9;
		typename C::const_iterator it2 = d.end();
		CPPUNIT_ASSERT(it1 == it2);
	}

	void test_const_iter_plus_equals_2() {
		const int x = 3;
		const int y = 200;
		const C d(x, y);
		typename C::const_iterator it1 = d.begin();

		for (int i = 0; i < x; ++i) {
			CPPUNIT_ASSERT(*it1 == y);
			it1 += 1;
		}
		CPPUNIT_ASSERT(it1 == d.end());
	}

	void test_const_iter_plus_equals_3() {
		const C d(512, 5);
		typename C::const_iterator it1 = d.begin();
		it1 += 512;
		typename C::const_iterator it2 = d.end();
		CPPUNIT_ASSERT(it1 == it2);
	}

	// ----------------------------
	// test_const_iter_minus_equals
	void test_const_iter_minus_equals_1() {
		const C d(9, 5);
		typename C::const_iterator it1 = d.end();
		it1 -= 9;
		typename C::const_iterator it2 = d.begin();
		CPPUNIT_ASSERT(it1 == it2);
	}

	void test_const_iter_minus_equals_2() {
		const int x = 3;
		const int y = 200;
		const C d(x, y);
		typename C::const_iterator it1 = d.end();

		for (int i = x; i > 0; --i) {
            it1 -= 1;
			CPPUNIT_ASSERT(*it1 == y);
		}
		CPPUNIT_ASSERT(it1 == d.begin());
	}

	void test_const_iter_minus_equals_3() {
		C e(1, 100);
		e.push_front(99);
		e.push_back(101);
		const C d(e);

		typename C::const_iterator it1 = d.end();
		it1 -= 1;
        CPPUNIT_ASSERT(*it1 == 101);
		it1 -= 1;
		CPPUNIT_ASSERT(*it1 == 100);
		it1 -= 1;
		CPPUNIT_ASSERT(*it1 == 99);
	}

	void test_const_iter_minus_equals_4() {
		const C d(512, 5);
		typename C::const_iterator it1 = d.end();
		it1 -= 512;
		typename C::const_iterator it2 = d.begin();
		CPPUNIT_ASSERT(it1 == it2);
	}

	// -----------
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
		C x(3, 11);
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
	// back_const
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
		C x(3);
		x.push_back(7);
		x.push_front(11);
		CPPUNIT_ASSERT(x.size() == 5);
		CPPUNIT_ASSERT(x.front() == 11);
	}
	
	void test_push_front_2 () {
		C x;
		x.push_front(4);
		CPPUNIT_ASSERT(x.size() == 1);
		CPPUNIT_ASSERT(x.front() == 4);
	}

	void test_push_front_3 () {
		C x;
		x.push_front(4);
		x.push_front(7);
		CPPUNIT_ASSERT(x.size() == 2);
		CPPUNIT_ASSERT(x.front() == 7);
	}

	void test_push_front_4 () {
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
		C x(1);
		CPPUNIT_ASSERT(x.size() == 1);
		x.pop_front();
		CPPUNIT_ASSERT(x.size() != 1);
		CPPUNIT_ASSERT(x.size() == 0);
	}
	
	void test_pop_front_2 () {
		C x(2, 3);
		x.pop_front();
		CPPUNIT_ASSERT(x.size() == 1);
		CPPUNIT_ASSERT(x.front() == 3);
	}
	
	void test_pop_front_3 () {
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
	
	// --------
	// at_const
	void test_at_const_1 () {
		const C x(3,11);
		CPPUNIT_ASSERT(x.at(0) == 11);
		CPPUNIT_ASSERT(x.at(1) == 11);
		CPPUNIT_ASSERT(x.at(2) == 11);
	}
	
	void test_at_const_2 () {
		const C x(2,3);
		CPPUNIT_ASSERT(x.at(0) == 3);
		CPPUNIT_ASSERT(x.at(1) == 3);
	}
	
	void test_at_const_3 () {
		const C x;
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
	
	// ---------------
	// const subscript
	void test_subscript_const_1 () {
		const C x(3,11);
		CPPUNIT_ASSERT(x[0] == 11);
		CPPUNIT_ASSERT(x[1] == 11);
		CPPUNIT_ASSERT(x[2] == 11);
	}
	
	void test_subscript_const_2 () {
		const C x(2,3);
		CPPUNIT_ASSERT(x[0] == 3);
		CPPUNIT_ASSERT(x[1] == 3);
	}
	
	void test_subscript_const_3 () {
		const C x(1000);
		CPPUNIT_ASSERT(x[0] == 0);
		CPPUNIT_ASSERT(x[500] == 0);
		CPPUNIT_ASSERT(x[x.size()-1] == 0);
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
		++b;
		CPPUNIT_ASSERT(*b == 2);
		++b;
		CPPUNIT_ASSERT(*b == 2);
	}

	// -----------
	// begin_const
	void test_begin_const_1 () {
		const C x;
		typename C::const_iterator b = x.begin();
		CPPUNIT_ASSERT(b == x.begin());
	}

	void test_begin_const_2 () {
		const C x(5);
		typename C::const_iterator b = x.begin();
		CPPUNIT_ASSERT(b == x.begin());
	}

	void test_begin_const_3 () {
		const C x(3, 2);
		typename C::const_iterator b = x.begin();
		CPPUNIT_ASSERT(*b == 2);
		++b;
		CPPUNIT_ASSERT(*b == 2);
		++b;
		CPPUNIT_ASSERT(*b == 2);
	}
	
	// ---
	// end
	void test_end_1 () {
		C x;
		typename C::iterator e = x.end();
		CPPUNIT_ASSERT(e == x.begin() );
	}
	
	void test_end_2 () {
 		C x(5);
		typename C::iterator e = x.end();
		CPPUNIT_ASSERT(e == x.begin()+5 );
	}
	
	void test_end_3 () {
		C x(3, 2);
		typename C::iterator e = x.end();
		CPPUNIT_ASSERT(e != x.begin() );
		CPPUNIT_ASSERT(e == x.begin()+3 );
	}

	// ---------
	// end_const
	void test_end_const_1 () {
		const C x;
		typename C::const_iterator e = x.end();
		CPPUNIT_ASSERT(e == x.begin());
	}	

	void test_end_const_2 () {
		const C x(5);
		typename C::const_iterator e = x.end();
		CPPUNIT_ASSERT(e == x.begin()+5);
	}

	void test_end_const_3 () {
		const C x(3, 2);
		typename C::const_iterator e = x.end();
		CPPUNIT_ASSERT(e != x.begin());
		CPPUNIT_ASSERT(e == x.begin()+3);
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
		x.insert(x.end(), 13);
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
	void test_resize_0 () {
		C x(3);
		CPPUNIT_ASSERT(x.size() == 3);
		x.resize(3);
		CPPUNIT_ASSERT(x.size() == 3);
	}

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

	void test_resize_7 () {
		C x(4);
		CPPUNIT_ASSERT(x.size() == 4);
		x.resize(6);
		CPPUNIT_ASSERT(x.size() == 6);
	}

	void test_resize_8 () {
		C x(4);
		CPPUNIT_ASSERT(x.size() == 4);
		x.resize(8);
		CPPUNIT_ASSERT(x.size() == 8);
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
		x.erase(x.begin()+4);
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
	// assignment
	void test_assignment_1 () {
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
	
	void test_assignment_2 () {
		C x;
		C y(3, -2);
		y = x;
		CPPUNIT_ASSERT(y.size() == 0);
		CPPUNIT_ASSERT(x.size() == 0);
		CPPUNIT_ASSERT(y.empty() );
		y.push_front(1);
		CPPUNIT_ASSERT(x.empty() );
	}
	
	void test_assignment_3 () {
		C x(3);
		C y(1);
		y = x;
		CPPUNIT_ASSERT(y.size() == 3);
		CPPUNIT_ASSERT(x.size() == 3);
		CPPUNIT_ASSERT(!y.empty() );
		y.push_back(1);
		CPPUNIT_ASSERT(x.size() == 3 );
	}
	
	// -------------
	// test_equality
	void test_equality_1 () {
		C x;
		C y;
		CPPUNIT_ASSERT(x == x);
		CPPUNIT_ASSERT(x == y);
	}

	void test_equality_2 () {
		C x(1);
		C y;
		CPPUNIT_ASSERT(x == x);
		CPPUNIT_ASSERT(!(x == y));
	}

	void test_equality_3 () {
		C x(1);
		C y(3);
		CPPUNIT_ASSERT(y == y);
		CPPUNIT_ASSERT(!(x == y));
	}

	void test_equality_4 () {
		C x(1);
		C y(1);
		CPPUNIT_ASSERT(x == y);
	}

	void test_equality_5 () {
		C x(3, 5);
		C y(3, 7);
		CPPUNIT_ASSERT(!(x == y));
	}

	void test_equality_6 () {
		C x(3, 5);
		C y(3, 5);
		CPPUNIT_ASSERT(x == y);
	}

	void test_equality_7 () {
		C x(3, 5);
		C y(3, 5);
		y.push_back(3);
		CPPUNIT_ASSERT(!(x == y));
	}

	void test_equality_8 () {
		C x(3, 5);
		C y(3, 5);
		y[2] = 7;
		CPPUNIT_ASSERT(!(x == y));
	}
	
	// -------------
	// test_less_than
	void test_less_than_1 () {
		C x;
		C y;
		CPPUNIT_ASSERT(!(x < x));
		CPPUNIT_ASSERT(!(x < y));
	}

	void test_less_than_2 () {
		C x(1);
		C y;
		CPPUNIT_ASSERT(!(x < x));
		CPPUNIT_ASSERT(y < x);
	}

	void test_less_than_3 () {
		C x(1, -2);
		C y(1);
		CPPUNIT_ASSERT(x < y);
	}
	
	// -----------------
	// iterator_equality
	void test_iterator_equality_1 () {
		C x;
		typename C::iterator b = x.begin();
		CPPUNIT_ASSERT(x.begin == b);
	}
	
	void test_iterator_equality_2 () {
		C x(1000);
		typename C::iterator b = x.begin();
		CPPUNIT_ASSERT(x.begin == b);
	}
	
	void test_iterator_equality_3 () {
		C x(1000, 7);
		typename C::iterator b = x.begin();
		CPPUNIT_ASSERT(x.begin == b);
	}
	
	// -----
	// suite
	CPPUNIT_TEST_SUITE(TestDeque);

	CPPUNIT_TEST(test_iter_equality_1);
	CPPUNIT_TEST(test_iter_equality_2);
	CPPUNIT_TEST(test_iter_equality_3);
	CPPUNIT_TEST(test_iter_equality_4);
	CPPUNIT_TEST(test_iter_plus_1);
	CPPUNIT_TEST(test_iter_plus_2);
	CPPUNIT_TEST(test_iter_plus_3);
	CPPUNIT_TEST(test_iter_plus_4);
	CPPUNIT_TEST(test_iter_minus_1);
	CPPUNIT_TEST(test_iter_minus_2);
	CPPUNIT_TEST(test_iter_minus_3);
	CPPUNIT_TEST(test_iter_minus_4);
	CPPUNIT_TEST(test_iter_dereference_1);
	CPPUNIT_TEST(test_iter_dereference_2);
	CPPUNIT_TEST(test_iter_dereference_3); 
	CPPUNIT_TEST(test_iter_dereference_4); 
	CPPUNIT_TEST(test_iter_increment_1);
	CPPUNIT_TEST(test_iter_increment_2);
	CPPUNIT_TEST(test_iter_increment_3);
	CPPUNIT_TEST(test_iter_decrement_1);
	CPPUNIT_TEST(test_iter_decrement_2);
	CPPUNIT_TEST(test_iter_decrement_3);
	CPPUNIT_TEST(test_iter_plus_equals_1);
	CPPUNIT_TEST(test_iter_plus_equals_2);
	CPPUNIT_TEST(test_iter_plus_equals_3);
	CPPUNIT_TEST(test_iter_minus_equals_1);
	CPPUNIT_TEST(test_iter_minus_equals_2);
	CPPUNIT_TEST(test_iter_minus_equals_3);
	CPPUNIT_TEST(test_iter_minus_equals_4);
/*
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
	CPPUNIT_TEST(test_push_front_4);
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
	CPPUNIT_TEST(test_at_const_1);
	CPPUNIT_TEST(test_at_const_2);
	CPPUNIT_TEST(test_at_const_3);
	CPPUNIT_TEST(test_subscript_1);
	CPPUNIT_TEST(test_subscript_2);
	CPPUNIT_TEST(test_subscript_3);
	CPPUNIT_TEST(test_subscript_const_1);
	CPPUNIT_TEST(test_subscript_const_2);
	CPPUNIT_TEST(test_subscript_const_3);
	CPPUNIT_TEST(test_begin_1);
	CPPUNIT_TEST(test_begin_2);
	CPPUNIT_TEST(test_begin_3);
	CPPUNIT_TEST(test_begin_const_1);
	CPPUNIT_TEST(test_begin_const_2);
	CPPUNIT_TEST(test_begin_const_3);
	CPPUNIT_TEST(test_end_1);
	CPPUNIT_TEST(test_end_2); 
	CPPUNIT_TEST(test_end_3);
	CPPUNIT_TEST(test_end_const_1);
	CPPUNIT_TEST(test_end_const_2);
	CPPUNIT_TEST(test_end_const_3);
	CPPUNIT_TEST(test_insert_1);
	CPPUNIT_TEST(test_insert_2);
	CPPUNIT_TEST(test_insert_3);
	CPPUNIT_TEST(test_insert_4);
	CPPUNIT_TEST(test_resize_0);
	CPPUNIT_TEST(test_resize_1); 
	CPPUNIT_TEST(test_resize_2); 
	CPPUNIT_TEST(test_resize_3);
	CPPUNIT_TEST(test_resize_4); 
	CPPUNIT_TEST(test_resize_5);
	CPPUNIT_TEST(test_resize_6);
	CPPUNIT_TEST(test_resize_7);
	CPPUNIT_TEST(test_resize_8);
	CPPUNIT_TEST(test_erase_1); 
	CPPUNIT_TEST(test_erase_2); 
	CPPUNIT_TEST(test_erase_3); 
	CPPUNIT_TEST(test_swap_1);
	CPPUNIT_TEST(test_swap_2);
	CPPUNIT_TEST(test_swap_3);
	CPPUNIT_TEST(test_clear_1);
	CPPUNIT_TEST(test_clear_2);
	CPPUNIT_TEST(test_clear_3);
	CPPUNIT_TEST(test_assignment_1);
	CPPUNIT_TEST(test_assignment_2);
	CPPUNIT_TEST(test_assignment_3);
	CPPUNIT_TEST(test_equality_1);
	CPPUNIT_TEST(test_equality_2);
	CPPUNIT_TEST(test_equality_3);
	CPPUNIT_TEST(test_equality_4);
	CPPUNIT_TEST(test_equality_5);
	CPPUNIT_TEST(test_equality_6);
	CPPUNIT_TEST(test_equality_7);
	CPPUNIT_TEST(test_equality_8);
	CPPUNIT_TEST(test_less_than_1);
	CPPUNIT_TEST(test_less_than_2);
	CPPUNIT_TEST(test_less_than_3);
*/	CPPUNIT_TEST_SUITE_END();
};

// ----
// main
int main () {
	using namespace std;
	ios_base::sync_with_stdio(false);		// turn off synchronization with C I/O
	cout << "TestDeque.c++" << endl << endl;

	CppUnit::TextTestRunner tr;
	//tr.addTest(TestDeque<   deque<int> >::suite() );
	tr.addTest(TestDeque< MyDeque<int> >::suite() );
	tr.run();

	cout << "Done." << endl;
	return 0;
}
