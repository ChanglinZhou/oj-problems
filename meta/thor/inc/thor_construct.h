#ifndef THOR_CONSTRUCT_H
#define THOR_CONSTRUCT_H

#include <new>

namespace thor {
template<typename T1, typename T2>
inline void _construct(T1* p, const T2& value) {
  new(p) T1(value);
}

template<typename T>
inline void _destroy(T* p) {
  p->~T();
}

}  // namespace thor

#endif  // THOR_CONSTRUCT_H
