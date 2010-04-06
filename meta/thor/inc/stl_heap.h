#ifndef STL_HEAP_H
#define STL_HEAP_H

namespace mySTL {

// Push the value into the max-heap. 
// The index of element in the heap is 0-based.
// Invariant:
// Pre: max-heap[topIndex, bottomIndex] except violation between holeIndex
// and its parent node.
// Post: max-heap[topIndex, bottomIndex].
template <typename RandomAccessIterator, typename Distance, typename T>
void __push_heap(RandomAccessIterator first, Distance holeIndex,
                 Distance topIndex, T value) {
  // left[i] = 2*i + 1, right[i] = 2*i + 2.
  Distance parent = (holeIndex - 1) / 2;
  // Siftup to maintain max-heap property until hit the top node or there's no
  // violation between it and its parent: array[parent] >= array[holeIndex].
  // The search path will try to find the first ancestor node,
  // which is >= value.
  // Actually, we can use swap mechanism from bottom up.
  while (holeIndex > topIndex && *(first + parent) < value) {
    *(first + holeIndex) = *(first + parent);
    holeIndex = parent;
    parent = (holeIndex - 1) / 2;
  }
  // Fill the value in the appropriate hole.
  *(first + holeIndex) = value;
}

template <typename RandomAccessIterator, typename Distance, typename T>
inline void __push_heap_aux(RandomAccessIterator first,
                            RandomAccessIterator last, Distance*, T*) {
  __push_heap(first, Distance(last - first) - 1,
              Distance(0), T(*(last - 1)));
}

template <typename RandomAccessIterator>
inline void push_heap(RandomAccessIterator first,
                      RandomAccessIterator last) {
  __push_heap_aux(first, last, distance_type(first), value_type(first));
}

}  // namespace mySTL

#endif  // STL_HEAP_H
