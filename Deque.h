// ----------------------
// projects/deque/Deque.h
// Copyright (C) 2012
// Glenn P. Downing
#ifndef Deque_h
#define Deque_h
#define DEBUG !true
#define WIDTH 50 // length of sub-arrays

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
		typedef A						allocator_type;
		typedef typename allocator_type::value_type		value_type;	// T		

		typedef typename allocator_type::size_type		size_type;
		typedef typename allocator_type::difference_type	difference_type;

		typedef typename allocator_type::pointer		pointer;	// T*
		typedef typename allocator_type::const_pointer		const_pointer;

		typedef typename allocator_type::reference		reference;
		typedef typename allocator_type::const_reference	const_reference;
		
		typedef typename allocator_type::template rebind<T*>::other pointer_allocator_type;
		typedef typename pointer_allocator_type::pointer	pointer_pointer; // T**

	public:
		// -----------
		// operator ==
		/**
		 * <your documentation>
		 */
		friend bool operator == (const MyDeque& lhs, const MyDeque& rhs) {
			return lhs.size() == rhs.size() and
				std::equal(lhs.begin(), lhs.end(), rhs.begin() );}

		// ----------
		// operator <
		/**
		 * <your documentation>
		 */
		friend bool operator < (const MyDeque& lhs, const MyDeque& rhs) {
			return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end() );}

	private:
		// ----
		// data
		allocator_type _a;	// T allocator
		pointer_allocator_type _pa; // T* allocator
		
		pointer_pointer _fr;	// front of outer array
		pointer_pointer _ba;	// back of outer array
		pointer _b;		// beginning of inner array
		pointer _e;		// end of inner array

		pointer _front;		// front of allocated space
		pointer _begin;		// beginning of used space
		pointer _end;		// end of used space
		pointer _back;		// back of allocated space

	private:
		// -----
		// valid
		bool valid () const {
			
			return (!_front && !_begin && !_end && !_back) ||
				((_front <= _begin) && (_begin <= _end) && (_end <= _back));}

	public:
		// --------
		// iterator
		class iterator {
			public:
				// --------
				// typedefs
				typedef std::bidirectional_iterator_tag   	iterator_category;
				typedef typename MyDeque::value_type	  	value_type;
				typedef typename MyDeque::difference_type 	difference_type;
				typedef typename MyDeque::pointer	  		pointer;
				typedef typename MyDeque::reference	  		reference;
				typedef typename MyDeque::size_type 	  	size_type;

			public:
				// -----------
				// operator ==
				/**
				 * Returns whether two iterators are equal
				 */
				friend bool operator == (const iterator& lhs, const iterator& rhs) {
					return lhs._d == rhs._d && lhs.idx == rhs.idx;}

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
				size_type idx;

			private:
				// -----
				// valid
				bool valid () const {
					return idx >= 0;}

			public:
				// -----------
				// constructor
				/**
				 * <your documentation>
				 */
				iterator (MyDeque* d, size_type i = 0) :
					_d(d), idx(i) {assert(valid() );}

				// Default copy, destructor, and copy assignment.
				// iterator (const iterator&);
				// ~iterator ();
				// iterator& operator = (const iterator&);

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
				iterator& operator ++ () {
					++idx;
					assert(valid());
					return *this;}

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
				typedef typename MyDeque::size_type 	  size_type;

			public:
				// -----------
				// operator ==
				/**
				 * Returns whether two iterators are equal
				 */
				friend bool operator == (const const_iterator& lhs, const const_iterator& rhs) {
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
				const MyDeque*  _d;
				size_type 	idx;

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
				 * Returns a const_iterator for d
				 */
				const_iterator (const MyDeque* d, size_type i)
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
					return *this;}

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
		 * Returns a Deque with the specified allocator
		 */
		explicit MyDeque (const allocator_type& a = allocator_type() )
			: _a(a), _pa(), _fr(0), _ba(0), _b(0), _e(0), _front(0), _begin(0), _end(0), _back(0){
				assert(valid() );}

		/**
		 * Returns a Deque with the specified size, values, and allocator
		 */
		explicit MyDeque (size_type s, const_reference v = value_type(), const allocator_type& a = allocator_type())
			: _a(a), _pa() {

			// we need s / WIDTH full arrays, and possibly 1 partial array
			size_type num_arrays = s / WIDTH + (s % WIDTH? 1 : 0);
			// allocate outer array and save pointer to front
			_fr = _pa.allocate(num_arrays);
			// allocate inner arrays
			for (size_type i = 0; i < num_arrays; ++i) {
				_fr[i] = _a.allocate(WIDTH);
			}
			// set pointer to back
			_ba = _fr + num_arrays;
			// set pointer to beginning of data
			_b = _fr[0];
			// offset < WIDTH if we have a partial array
			size_type offset = WIDTH - (WIDTH * num_arrays - s); 
			assert 	(0 < offset and offset <= WIDTH);
			// set pointer to end of data
			_e = _fr[num_arrays - 1] + offset;
			// fill inner arrays with default value
			for (size_type i = 0; i < num_arrays - 1; ++i) {
				uninitialized_fill(_a, _fr[i], _fr[i] + WIDTH, v);
			}
			if (num_arrays > 0) // fill last array (might be partial)
				uninitialized_fill(_a, _fr[num_arrays - 1], _e, v);

			// v1.0
			_front = _begin = _a.allocate(s);
			_end = _back = _begin + s;
			uninitialized_fill(_a, begin(), end(), v);
			assert(valid());}

		/**
		 * Returns a Deque that is a copy of the specified Deque
		 */
		MyDeque (const MyDeque& that) 
			: _a(that._a) {
			_pa = pointer_allocator_type();

			_front = _begin = _a.allocate(that.size());
			_end = _back = _begin + that.size();
			uninitialized_copy(_a, that.begin(), that.end(), begin()); 
			assert(valid());}

		// ----------
		// destructor
		/**
		 * Destroys this Deque
		 */
		~MyDeque () {
			if (_front) {
				clear();
				_a.deallocate(_front, (_back - _front));}
			assert(valid() );}

		// ----------
		// operator =
		/**
		 * Returns a reference of this Deque after copying the specified Deque
		 */
		MyDeque& operator = (const MyDeque& rhs) {
			if (this == &rhs)
				return *this;
			if (rhs.size() == size())
				std::copy(rhs.begin(), rhs.end(), begin());
			else if (rhs.size() < size()) {
				std::copy(rhs.begin(), rhs.end(), begin());
				resize(rhs.size());}	
			else if ((unsigned)rhs.size() <= (unsigned)(_back - _begin)) {
				std::copy(rhs.begin(), rhs.begin() + size(), begin());
				_end = &(*uninitialized_copy(_a, rhs.begin() + size(), rhs.end(), end()));}
			else {
				clear();
				MyDeque x(rhs);
				swap(x);}
			assert(valid() );
			return *this;}

		// -----------
		// operator []
		/**
		 * Returns a reference to the nth element
		 */
		reference operator [] (size_type n) {
			pointer r = _begin + n;
			return *r;}

		/**
		 * Returns a constant reference to the nth element
		 */
		const_reference operator [] (size_type n) const {
			return const_cast<MyDeque*>(this)->operator[](n);}

		// --
		// at
		/**
		 * Returns a reference to the nth element
		 * Throws an exception if n is out of bounds
		 */
		reference at (size_type n) {
			if (n >= size() )
				throw std::out_of_range("deque::_M_range_check");
			return (*this)[n];}

		/**
		 * Returns a constant reference to the nth element
 		 * Throws an exception if n is out of bounds 
		 */
		const_reference at (size_type index) const {
			if (index >= size() )
				throw std::out_of_range("deque::_M_range_check");
			return const_cast<MyDeque*>(this)->at(index);}

		// ----
		// back
		/**
		 * Returns a reference of the element at the back
		 */
		reference back () {
			assert(! empty());
			return *(_end - 1);}

		/**
		 * Returns a constant reference of the element at the back
		 */
		const_reference back () const {
			return const_cast<MyDeque*>(this)->back();}

		// -----
		// begin
		/**
		 * Returns a random-access iterator for the first element
		 */
		iterator begin () {
			return iterator(this, 0);}

		/**
		 * Returns a constant random-access iterator for the first element
		 */
		const_iterator begin () const {
			return const_iterator(this, 0);}

		// -----
		// clear
		/**
		 * Removes all elements (empties the container)
		 */
		void clear () {
			resize(0);
			assert(valid());}

		// -----
		// empty
		/**
		 * Returns whether the container is empty
		 */
		bool empty () const {
			return !size();}

		// ---
		// end
		/**
		 * Returns a random-access iterator to the position after the last element
		 */
		iterator end () {
			return iterator(this, size() );}

		/**
		 * Returns a constant random-access iterator to the position after the last element
		 */
		const_iterator end () const {
			return const_iterator(this, size() );}

		// -----
		// erase
		/**
		 * Removes the element at iterator position pos and returns the position of the next element
		 */
		iterator erase (iterator pos) {
			if(pos == end() - 1)
				pop_back();
			else {
				std::copy(pos+1, end(), pos);
				resize(size()-1);}
			assert(valid() );
			return iterator(this);}

		// -----
		// front
		/**
		 * Returns the first element
		 */
		reference front () {
			return *(_begin);}

		/**
		 * Returns the first element
		 */
		const_reference front () const {
			return const_cast<MyDeque*>(this)->front();}

		// ------
		// insert
		/**
		 * Inserts a copy of v before iterator position pos and returns the position of the new element
		 */
		iterator insert (iterator pos, const_reference v) {
			if(pos == end() )
				push_back(v);
			else {
				resize(size()+1);
				std::copy(pos, end(), pos+1);
				*pos = v;}
			assert(valid());
			return iterator(this);}

		// --------
		// pop_back
		/**
		 * Removes the last element (does not return it)
		 */
		void pop_back () {
			assert(!empty() );
			resize(size() - 1);
			assert(valid());}

		/**
		 * Removes the first element (doest not return it)
		 */
		void pop_front () {
			destroy(_a, begin(), begin()+1);
			++_begin;
			assert(valid() );}

		// ---------
		// push_back
		/**
		 * Appends a copy of v at the end
		 */
		void push_back (const_reference v) {
			resize(size() + 1, v);
			assert(valid());}

		// ----------
		// push_front
		/**
		 * Inserts a copy of v at the beginning
		 */
		void push_front (const_reference v) {
			if (_front == _begin) {
				resize(size() + 1);
				pop_back();}	
			--_begin;
			_a.construct(&*begin(), v);	
			assert(valid());}

		// ------
		// resize
		/**
		 * Changes the number of elements to num (if size() grows new elements are created by their default constructor)
		 */
		void resize (size_type s, const_reference v = value_type()) {
			if (s == size() )
				return;
			if (s < size() )
				_end = &*destroy(_a, begin() + s, end() );
			else if ((unsigned)s <= (unsigned)(_end -_front) && (unsigned)s <= (unsigned)(_back - _begin))
				_end = &*uninitialized_fill(_a, end(), begin() + s, v);
			else {		// allocate more capacity
				size_type capacity = std::max(s, 2 * size());
				size_type temp1 = (capacity - s) / 2;
				if (temp1 == 0) {
					capacity += 3;}
				temp1 = (capacity - s) / 2;
				size_type temp2 = (capacity - s) % 2? temp1 + 1: temp1;
				MyDeque x(capacity, v);
				std::copy(begin(), end(), x.begin()+temp1);
				destroy(x._a, x.begin(), x.begin()+temp1);
				destroy(x._a, x.end()-temp2, x.end());
				x._begin += temp1;
				x._end -= temp2;
				swap(x);}
			assert(valid() );}

		// ----
		// size
		/**
		 * Returns the current number of elements
		 */
		size_type size () const {
			return _end - _begin;}

		// ----
		// swap
		/**
		 * Swaps the data of this with the data of that
		 */
		void swap (MyDeque& that) {
			if (_a == that._a) {
				std::swap(_front, that._front);
				std::swap(_begin, that._begin);
				std::swap(_end, that._end);
				std::swap(_back, that._back);}
			else {
				MyDeque x(*this);
				*this = that;
				that = x;}
			assert(valid() );}};
#endif // Deque_h
