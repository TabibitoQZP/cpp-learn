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

template <class T>
void Vec<T>::create() {
    data = avail = limit = nullptr;
}

template <class T>
void Vec<T>::create(size_type n, const T& t) {
    data = alloc.allocate(n);
    limit = avail = data + n;
    std::uninitialized_fill(data, avail, t);
}

template <class T>
void Vec<T>::create(const_iterator s, const_iterator e) {
    data = alloc.allocate(e - s);
    limit = avail = std::uninitialized_copy(s, e, data);
}

template <class T>
void Vec<T>::uncreate() {
    if (data) {
        iterator it = avail;
        while (it != data) {
            alloc.destroy(--it);
        }
        alloc.deallocate(data, limit - data);
        data = limit = avail = nullptr;
    }
}

template <class T>
Vec<T>& Vec<T>::operator=(const Vec& rhs) {
    if (&rhs != this) {
        uncreate();
        create(rhs.begin(), rhs.end());
    }
    return *this;
}

template <class T>
void Vec<T>::grow() {
    // This function is only used for increase the limit.
    size_type new_size = std::max(2*(limit - data), ptrdiff_t(1));
    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = std::uninitialized_copy(data, avail, new_data);
    uncreate();
    data = new_data;
    avail = new_avail;
    limit = data + new_size;
}

template <class T>
void Vec<T>::unchecked_append(const T& val) {
    // only append data without any check.
    alloc.construct(avail++, val);
}
#endif