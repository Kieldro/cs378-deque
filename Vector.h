// --------
// Vector.h
// --------

#ifndef Vector_h
#define Vector_h

#include <algorithm> // copy, equal, lexicographical_compare, max, swap
#include <cassert>   // assert
#include <memory>    // allocator
#include <stdexcept> // out_of_range
#include <utility>   // !=, <=, >, >=

#include "Memory.h"  // my_destroy, my_uninitialized_copy, my_uninitialized_fill

/*
namespace std     {
namespace rel_ops {

template <typename T>
inline bool operator != (const T& lhs, const T& rhs) {
    return !(lhs == rhs);}

template <typename T>
inline bool operator <= (const T& lhs, const T& rhs) {
    return !(rhs < lhs);}

template <typename T>
inline bool operator > (const T& lhs, const T& rhs) {
    return (rhs < lhs);}

template <typename T>
inline bool operator >= (const T& lhs, const T& rhs) {
    return !(lhs < rhs);}

} // rel_ops
} // std;
*/

using namespace std::rel_ops;
void printD(){
	cerr << "contents: ";
	for(int i = 0; i < d.size(); ++i)
		cerr << d[i];
	 cerr << endl;
}

template <typename T, typename A = std::allocator<T> >
class my_vector {
    public:
        typedef A                                        allocator_type;
        typedef typename allocator_type::value_type      value_type;

        typedef typename allocator_type::size_type       size_type;
        typedef typename allocator_type::difference_type difference_type;

        typedef typename allocator_type::pointer         pointer;
        typedef typename allocator_type::const_pointer   const_pointer;

        typedef typename allocator_type::reference       reference;
        typedef typename allocator_type::const_reference const_reference;

        typedef typename allocator_type::pointer         iterator;
        typedef typename allocator_type::const_pointer   const_iterator;

    public:
        friend bool operator == (const my_vector& lhs, const my_vector& rhs) {
            return (lhs.size() == rhs.size()) && std::equal(lhs.begin(), lhs.end(), rhs.begin());}

        friend bool operator < (const my_vector& lhs, const my_vector& rhs) {
            return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());}

        friend void swap (my_vector& x, my_vector& y) {
            x.swap(y);}

    private:
        allocator_type _a;

        pointer _b;
        pointer _e; // size
        pointer _l; // capacity

    private:
        bool valid () const {
            return (!_b && !_e && !_l) || (_b <= _e) && (_e <= _l);}

        my_vector (const my_vector& that, size_type c) :
                _a (that._a) {
            assert(c >= that.size());
            _b = _a.allocate(c);
            _e = _b + that.size();
            _l = _b + c;
            my_uninitialized_copy(_a, that.begin(), that.end(), begin());
            assert(valid());}

    public:
        explicit my_vector (const allocator_type& a = allocator_type()) :
                _a (a) {
            _b = _e = _l = 0;
            assert(valid());}

        explicit my_vector (size_type s, const_reference v = value_type(), const allocator_type& a = allocator_type()) :
                _a (a) {
            _b = _a.allocate(s);
            _e = _l = _b + s;
            my_uninitialized_fill(_a, begin(), end(), v);
            assert(valid());}

        my_vector (const my_vector& that) :
                _a (that._a) {
            _b = _a.allocate(that.size());
            _e = _l = _b + that.size();
            my_uninitialized_copy(_a, that.begin(), that.end(), begin());
            assert(valid());}

        ~my_vector () {
            if (_b) {
                clear();
                _a.deallocate(_b, capacity());}
            assert(valid());}

        my_vector& operator = (const my_vector& that) {
            if (this == &that)
                return *this;
            if (that.size() == size())
                std::copy(that.begin(), that.end(), begin());
            else if (that.size() < size()) {
                std::copy(that.begin(), that.end(), begin());
                resize(that.size());}
            else if (that.size() <= capacity()) {
                std::copy(that.begin(), that.begin() + size(), begin());
                _e = my_uninitialized_copy(_a, that.begin() + size(), that.end(), end());}
            else {
                clear();
                reserve(that.size());
                _e = my_uninitialized_copy(_a, that.begin(), that.end(), begin());}
            assert(valid());
            return *this;}

        reference operator [] (size_type i) {
            return begin()[i];}

        const_reference operator [] (size_type i) const {
            return const_cast<my_vector&>(*this)[i];}

        reference at (size_type i) throw (std::out_of_range) {
            if (i >= size())
                throw std::out_of_range("vector::_M_range_check");
            return (*this)[i];}

        const_reference at (size_type i) const {
            return const_cast<my_vector&>(*this).at(i);}

        reference back () {
            assert(!empty());
            return *(end() - 1);}

        const_reference back () const {
            return const_cast<my_vector&>(*this).back();}

        iterator begin () {
            return _b;}

        const_iterator begin () const {
            return const_cast<my_vector&>(*this).begin();}

        size_type capacity () const {
            return _l - _b;}

        void clear () {
            resize(0);
            assert(valid());}

        bool empty () const {
            return size() == 0;}

        iterator end () {
            return _e;}

        const_iterator end () const {
            return const_cast<my_vector&>(*this).end();}

        reference front () {
            assert(!empty());
            return *begin();}

        const_reference front () const {
            return const_cast<my_vector&>(*this).front();}

        void pop_back () {
            assert(!empty() );
            resize(size() - 1);
            assert(valid() );
        }

        void push_back (const_reference v) {
            resize(size() + 1, v);
            assert(valid());}

        void reserve (size_type c) {
            if (c > capacity()) {
                my_vector x(*this, c);
                swap(x);}
            assert(valid());}

        void resize (size_type s, const_reference v = value_type()) {
            if (s == size())
                return;
            if (s < size())
                _e = my_destroy(_a, begin() + s, end());
            else if (s <= capacity())
                _e = my_uninitialized_fill(_a, end(), begin() + s, v);
            else {
                reserve(std::max(2 * size(), s));
                resize(s, v);}
            assert(valid());}

        size_type size () const {
            return _e - _b;}

        void swap (my_vector& that) {
            if (_a == that._a) {
                std::swap(_b, that._b);
                std::swap(_e, that._e);
                std::swap(_l, that._l);}
            else {
                my_vector x(*this);
                *this = that;
                that  = x;}
            assert(valid());}};

#endif // Vector_h
