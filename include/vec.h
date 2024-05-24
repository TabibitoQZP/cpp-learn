#ifndef VEC_H
#define VEC_H

#include "libs.h"

template <class T>
class Vec
{
public:
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef size_t size_type;
    typedef T value_type;
    Vec() { create(); }
    explicit Vec(size_type n, const T& t=T()) { create(n, t); }
    Vec(const Vec& v) { create(v.begin(), v.end()); }
    Vec& operator=(const Vec&);
    ~Vec() { uncreate(); }
    T& operator[](size_type i) { return data[i]; }

    void push_back(const T& t) {
        if (avail == limit) {
            grow();
        }
        unchecked_append(t);
    }

    size_type size() const { return avail - data; }
    const_iterator begin() const { return data; }
    const_iterator end() const { return avail; }

    iterator begin() { return data; }
    iterator end() { return avail; }

private:
    iterator data;
    iterator avail;
    iterator limit;

    std::allocator<T> alloc;
    void create();
    void create(size_type, const T&);
    void create(const_iterator, const_iterator);

    void uncreate();
    void grow();
    void unchecked_append(const T&);
};
#endif