/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Copyright (c) 1996,1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 2009
 * Su Shi
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

#ifndef THOR_ALLOC_H
#define THOR_ALLOC_H

#include "thor_construct.h"

#include <new>
#include <cstddef>
#include <cstdlib>
#include <climits>
#include <iostream>

namespace thor {

template<typename T>
inline T* _allocate(ptrdiff_t size, T*) {
  set_new_handler(NULL);
  T* tmp = static_cast<T*>(::operator new(size * sizeof(T)));
  if (tmp == NULL) {
    cerr << "Out of memmory!" << endl;
    exit(1);
  }

  return tmp;
}

template<typename T>
inline void _deallocate(T* buffer) {
  ::operator delete(buffer);
}

template<typename T>
class allocator {
 public:
  typedef T value_type;
  typedef T* pointer;
  typedef const T* const_pointer;
  typedef T& reference;
  typedef const T& const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

  // rebind allocator of type U
  template<typename U>
  struct rebind {
    typedef allocator<U> other;
  };

  pointer allocate(size_type n, const void* hint = 0) {
    return _allocate(static_cast<difference_type>(n),
                     static_cast<pointer>(0));
  }

  void deallocate(pointer p, size_type n) {
    _deallocate(p);
  }

  void construct(pointer p, const T& value) {
    _construct(p, value);
  }

  void destroy(pointer p) {
    _destroy(p);
  }

  pointer address(reference p) {
    return static_cast<pointer>(&x);
  }

  const_pointer const_address(const_reference p) {
    return static_cast<const_pointer>(&x);
  }

  size_t init_page_size() {
    return max(size_type(1), size_type(4096) / sizeof(T));
  }

  size_type max_size() const{
    return static_cast<size_type>(UINT_MAX / sizeof(T));
  }
};

}  // namespace thor


#endif  // THOR_ALLOC_H
