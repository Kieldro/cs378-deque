// ----------------------
// projects/deque/Deque.h
// Copyright (C) 2012
// Glenn P. Downing
#ifndef Deque_h
#define Deque_h
#define DEBUG true

// --------
// includes
#include <algorithm>	// copy, equal, lexicographical_compare, max, swap
#include <cassert>		// assert
#include <iterator>		// iterator, bidirectional_iterator_tag
#include <memory>		// allocator
#include <stdexcept>	// out_of_range
#include <utility>		// !=, <=, >, >=
#include <iostream>

// -----
// using
using std::rel_ops::operator!=;
using std::rel_ops::operator<=;
using std::rel_ops::operator>;
using std::rel_ops::operator>=;
using std::cerr;
using std::endl;

// -------
// destroy
template <typename A, typename BI>
BI destroy (A& a, BI b, BI e) {
	while (b != e) {
		--e;
		a.destroy(&*e);}
	return b;}

// ------------------
// uninitialized_copy
template <typename A, typename II, typename BI>
BI uninitialized_copy (A& a, II b, II e, BI x) {
	//if(DEBUG)cerr << "uninitialized_copy(): " << endl;
	BI p = x;
	assert(b!=e);
	try {
		while (b != e) {
			a.construct(&*x, *b);
			++b;
			++x;}}
	catch (...) {
		destroy(a, p, x);
		throw;}
	return x;}

// ------------------
// uninitialized_fill
template <typename A, typename BI, typename U>
BI uninitialized_fill (A& a, BI b, BI e, const U& v) {
	//if(DEBUG)cerr << "uninitialized_fill(): " << endl;
	BI p = b;
	assert(p == b);
	try {
		while (b != e) {
			a.construct(&*b, v);
			++b;}}
	catch (...) {
		destroy(a, p, b);
		throw;}
	return e;}

// -----
// MyDeque
template < typename T, typename A = std::allocator<T> >
class MyDeque {
	public:
		// --------
		// typedefs
		typedef A											allocator_type;
		typedef typename allocator_type::value_type			value_type;		// same as T*? why typedef?

		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::difference_type	difference_type;

		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;

		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		

	public:
		// -----------
		// operator ==
		/**
		 * <your documentation>
		 */
		friend bool operator == (const MyDeque& lhs, const MyDeque& rhs) {
			// <your code>
			// you must use std::equal()
			
			return true;}

		// ----------
		// operator <
		/**
		 * <your documentation>
		 */
		friend bool operator < (const MyDeque& lhs, const MyDeque& rhs) {
			// <your code>
			// you must use std::lexicographical_compare()
			return true;}

	private:
		// ----
		// data
		allocator_type _a;		// allocator
		
		pointer _front;
		pointer _begin;		// array to hold elements
		pointer _end;		// pointer to the end of used space
		pointer _back;		// pointer to the end of array?

	private:
		// -----
		// valid
		bool valid () const {
			
			return (!_front && !_begin && !_end && !_back) ||
				((_front <= _begin) && (_begin <= _end) && (_end <= _back));
		}

	public:
		// --------
		// iterator
		class iterator {
			public:
				// --------
				// typedefs
				typedef std::bidirectional_iterator_tag   iterator_category;
				typedef typename MyDeque::value_type	  value_type;
				typedef typename MyDeque::difference_type difference_type;
				typedef typename MyDeque::pointer		 pointer;
				typedef typename MyDeque::reference	   reference;
				//using MyDeque::size_type;

			public:
				// -----------
				// operator ==
				/**
				 * Returns whether two iterators are equal
				 */
				friend bool operator == (const iterator& lhs, const iterator& rhs) {
					return lhs._d == rhs._d && lhs.idx == rhs.idx;
				}

				/**
				 * Returns whether two iterators are not equal
				 */
				friend bool operator != (const iterator& lhs, const iterator& rhs) {
					return !(lhs == rhs);}

				// ----------
				// operator +
				/**
				 * Returns the iterator of the nth next element
				 */
				friend iterator operator + (iterator lhs, difference_type n) {
					return lhs += n;}

				// ----------
				// operator -
				/**
				 * Returns the iterator of the nth previous element
				 */
				friend iterator operator - (iterator lhs, difference_type n) {
					return lhs -= n;}

			private:
				// ----
				// data
				MyDeque* _d;
				MyDeque::size_type idx;
				

			private:
				// -----
				// valid
				bool valid () const {
					return idx >= 0;
				}

			public:
				// -----------
				// constructor
				/**
				 * <your documentation>
				 */
				iterator (MyDeque* d, MyDeque::size_type i = 0) :
				_d(d), idx(i)
				{
					assert(valid() );
				}

				// Default copy, destructor, and copy assignment.
				// iterator (const iterator&);
				// ~iterator ();
				/*iterator& operator = (const iterator&){
					
					;
				}*/

				// ----------
				// operator *
				/**
				 * Provides access to the actual element
				 */
				reference operator * () const {
					reference r = (*_d)[idx];
					
					return r;
				}

				// -----------
				// operator ->
				/**
				 * Provides access to a member of the actual element
				 */
				pointer operator -> () const {
					return &**this;}

				// -----------
				// operator ++
				/**
				 * Steps forward (returns new position)
				 */
				iterator& operator ++ () {
					++idx;
					assert(valid() );
					return *this;
				}

				/**
				 * Steps forward (returns old position)
				 */
				iterator operator ++ (int) {
					iterator x = *this;
					++(*this);
					assert(valid());
					return x;}

				// -----------
				// operator --
				/**
				 * Steps backward (returns new position)
				 */
				iterator& operator -- () {
					--idx;
					assert(valid());
					return *this;}

				/**
				 * Steps backward (returns old position)
				 */
				iterator operator -- (int) {
					iterator x = *this;
					--(*this);
					assert(valid());
					return x;}

				// -----------
				// operator +=
				/**
				 * Steps n elements forward (or backward, if n is negative)
				 */
				iterator& operator += (difference_type n) {
					idx += n;
					assert(valid());
					return *this;}

				// -----------
				// operator -=
				/**
				 * Steps n elements backward (or forward, if n is negative)
				 */
				iterator& operator -= (difference_type n) {
					idx -= n;
					assert(valid());
					return *this;}};

	public:
		// --------------
		// const_iterator
		class const_iterator {
			public:
				// --------
				// typedefs
				typedef std::bidirectional_iterator_tag   iterator_category;
				typedef typename MyDeque::value_type	  value_type;
				typedef typename MyDeque::difference_type difference_type;
				typedef typename MyDeque::const_pointer   pointer;
				typedef typename MyDeque::const_reference reference;

			public:
				// -----------
				// operator ==
				/**
				 * Returns whether two iterators are equal
				 */
				friend bool operator == (const const_iterator& lhs, const const_iterator& rhs) {
					// <your code>
					return lhs._d == rhs._d && lhs.idx == rhs.idx;}

				/**
				 * Returns whether two iterators are not equal
				 */
				friend bool operator != (const const_iterator& lhs, const const_iterator& rhs) {
					return !(lhs == rhs);}

				// ----------
				// operator +
				/**
				 * Returns the iterator of the nth next element
				 */
				friend const_iterator operator + (const_iterator lhs, difference_type n) {
					return lhs += n;}

				// ----------
				// operator -
				/**
				 * Returns the iterator of the nth previous element
				 */
				friend const_iterator operator - (const_iterator lhs, difference_type n) {
					return lhs -= n;}

			private:
				// ----
				// data
				const MyDeque* _d;
				MyDeque::size_type idx;

			private:
				// -----
				// valid
				bool valid () const {
					return idx >= 0;
				}

			public:
				// -----------
				// constructor
				/**
				 * <your documentation>
				 */
				const_iterator (const MyDeque* d, MyDeque::size_type i)
					: _d(d), idx(i) {assert(valid());}

				// Default copy, destructor, and copy assignment.
				// const_iterator (const const_iterator&);
				// ~const_iterator ();
				// const_iterator& operator = (const const_iterator&);

				// ----------
				// operator *
				/**
				 * Provides access to the actual element
				 */
				reference operator * () const {
					return (*_d)[idx];}

				// -----------
				// operator ->
				/**
				 * Provides access to a member of the actual element
				 */
				pointer operator -> () const {
					return &**this;}

				// -----------
				// operator ++

				/**
				 * Steps forward (returns new position)
				 */
				const_iterator& operator ++ () {
					++idx;
					assert(valid());
					return *this;}

				/**
				 * Steps forward (returns old position)
				 */
				const_iterator operator ++ (int) {
					const_iterator x = *this;
					++(*this);
					assert(valid());
					return x;}

				// -----------
				// operator --
				/**
				 * Steps backward (returns new position)
				 */
				const_iterator& operator -- () {
					--idx;
					assert(valid());
					return *this;}

				/**
				 * Steps backward (returns old position)
				 */
				const_iterator operator -- (int) {
					const_iterator x = *this;
					--(*this);
					assert(valid());
					return x;}

				// -----------
				// operator +=
				/**
				 * Steps n elements forward (or backward, if n is negative)
				 */
				const_iterator& operator += (difference_type n) {
					idx += n;
					assert(valid());
					return *this;
				}

				// -----------
				// operator -=
				/**
				 * Steps n elements backward (or forward, if n is negative)
				 */
				const_iterator& operator -= (difference_type n) {
					idx -= n;
					assert(valid());
					return *this;}};

	public:
		// ------------
		// constructors
		/**
		 * <your documentation>
		 */
		explicit MyDeque (const allocator_type& a = allocator_type() )
			: _a(a), _front(0), _begin(0), _end(0), _back(0)
		{
			assert(valid() );
		}

		/**
		 * <your documentation>
		 */
		explicit MyDeque (size_type s, const_reference v = value_type(), const allocator_type& a = allocator_type())
			: _a(a) {
			_front = _begin = _a.allocate(s);
			_end = _back = _begin + s;
			uninitialized_fill(_a, begin(), end(), v);
			assert(valid() );
		}

		/**
		 * <your documentation>
		 */
		MyDeque (const MyDeque& that) 
			: _a(that._a) {
			_front = _begin = _a.allocate(that.size());
			_end = _back = _begin + that.size();
			uninitialized_copy(_a, that.begin(), that.end(), begin()); 
			assert(valid() );
		}

		// ----------
		// destructor
		/**
		 * <your documentation>
		 */
		~MyDeque () {
			//if(DEBUG)cerr << "~MyDeque(): " << size() << endl;
			
			assert(valid() );
		}

		// ----------
		// operator =
		/**
		 * <your documentation>
		 */
		MyDeque& operator = (const MyDeque& rhs) {
			if (this == &rhs)
				return *this;
			if (rhs.size() == size())
				std::copy(rhs.begin(), rhs.end(), begin());
			else if (rhs.size() < size()) {
				std::copy(rhs.begin(), rhs.end(), begin());
				resize(rhs.size());
			}	
			else if (rhs.size() <= capacity()) {
				std::copy(rhs.begin(), rhs.begin() + size(), begin());
				_end = &(*uninitialized_copy(_a, rhs.begin() + size(), rhs.end(), end()));
			}
			else {
				clear();
				MyDeque x(rhs);
				swap(x);
			}
			assert(valid() );
			return *this;}

		// -----------
		// operator []
		/**
		 * <your documentation>
		 */
		reference operator [] (size_type index) {
			pointer r = _begin + index;
			
			return *r;
		}

		/**
		 * <your documentation>
		 */
		const_reference operator [] (size_type index) const {
			return const_cast<MyDeque*>(this)->operator[](index);}

		// --
		// at
		/**
		 * <your documentation>
		 */
		reference at (size_type index) {
			if (index >= size() )
				throw std::out_of_range("deque::_M_range_check");
			
			return (*this)[index];
		}

		/**
		 * <your documentation>
		 */
		const_reference at (size_type index) const {
			if (index >= size() )
				throw std::out_of_range("deque::_M_range_check");
			
			return const_cast<MyDeque*>(this)->at(index);
		}

		// ----
		// back
		/**
		 * <your documentation>
		 */
		reference back () {
			assert(! empty());
			return *(_end - 1);
		}

		/**
		 * <your documentation>
		 */
		const_reference back () const {
			return const_cast<MyDeque*>(this)->back();
		}

		// -----
		// begin
		/**
		 * <your documentation>
		 */
		iterator begin () {
			return iterator(this, 0);
		}

		/**
		 * <your documentation>
		 */
		const_iterator begin () const {
			return const_iterator(this, 0);}

		// -----
		// clear
		/**
		 * <your documentation>
		 */
		void clear () {
			resize(0);
			assert(valid());}

		// -----
		// empty
		/**
		 * <your documentation>
		 */
		bool empty () const {
			return !size();}

		// ---
		// end
		/**
		 * <your documentation>
		 */
		iterator end () {
			return iterator(this, size() );}

		/**
		 * <your documentation>
		 */
		const_iterator end () const {
			return const_iterator(this, size() );}

		// -----
		// erase
		/**
		 * <your documentation>
		 */
		iterator erase (iterator it) {
			if(it == end() )
				pop_back();
			else {
				std::copy(it+1, end(), it);
				resize(size()-1);
			}
			
			assert(valid() );
			return iterator(this);
		}

		// -----
		// front
		/**
		 * <your documentation>
		 */
		reference front () {
			assert(!empty() );
			return *(_begin);
		}

		/**
		 * <your documentation>
		 */
		const_reference front () const {
			return const_cast<MyDeque*>(this)->front();}

		// ------
		// insert
		/**
		 * <your documentation>
		 */
		iterator insert (iterator it, const_reference v) {
			if(it == end() )
				push_back(v);
			else {
				resize(size()+1);
				std::copy(it, end(), it+1);
				*it = v;
			}
			assert(valid() );
			return iterator(this);
		}

		// ---
		// pop
		/**
		 * <your documentation>
		 */
		void pop_back () {
			assert(!empty() );
			resize(size() - 1);
			assert(valid() );
		}

		/**
		 * <your documentation>
		 */
		void pop_front () {
			destroy(_a, begin(), begin()+1);
			++_begin;
			
			assert(valid() );
		}

		// ----
		// push
		/**
		 * <your documentation>
		 */
		void push_back (const_reference v) {
			resize(size() + 1, v);
			assert(valid() );
		}

		/**
		 * <your documentation>
		 */
		void push_front (const_reference v) {
			if(_front != _begin){		// if front has capacity
				--_begin;
				_a.construct(&*begin(), v);
			}
				
			
			assert(valid() );
		}

		// ------
		// resize
		/**
		 * <your documentation>
		 */
		void resize (size_type s, const_reference v = value_type()) {
			if (s == size() )
				return;
			if (s < size() )
				_end = &*destroy(_a, begin() + s, end() );
			else if ((unsigned)s <= _end -_front && (unsigned)s <= _back - _begin)
				_end = &*uninitialized_fill(_a, end(), begin() + s, v);
			else {		// allocate more capacity
				size_type capacity = std::max(s, 2 * size() );
				size_type temp1 = (capacity - s) / 2;
				size_type temp2 = (capacity - s) % 2? temp1 + 1: temp1;
				MyDeque x(capacity, v);
				std::copy(begin(), end(), x.begin()+temp1);
				destroy(x._a, x.begin(), x.begin()+temp1);
				destroy(x._a, x.end()-temp2, x.end());
				x._begin += temp1;
				x._end -= temp2;
				swap(x);
			}
			assert(valid() );
		}

		// ----
		// size
		/**
		 * <your documentation>
		 */
		size_type size () const {
			return _end - _begin;
		}

		// ----
		// swap
		/**
		 * <your documentation>
		 */
		void swap (MyDeque& that) {
			if (_a == that._a) {
				std::swap(_front, that._front);
				std::swap(_begin, that._begin);
				std::swap(_end, that._end);
				std::swap(_back, that._back);
			}
			else {
				MyDeque x(*this);
				*this = that;
				that = x;
			}
			assert(valid() );
		}

	private:
		// --------
		// capacity
		/**
		 * returns the capacity of this deque
		 */
		size_type capacity() const{
			return _back - _front;
		}
};
#endif // Deque_h
