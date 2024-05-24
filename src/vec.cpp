#include "libs.h"

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