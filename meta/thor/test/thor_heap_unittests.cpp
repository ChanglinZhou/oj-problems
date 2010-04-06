// Copyright (c) 2010, Su Shi <carmack.shi [at] gmail.com>
//
// All rights reserved.

#include <gtest/gtest.h>

#include "thor_binomial_heap.h"

typedef thor::BinomialHeap<int> IBHeap;

TEST(IBHeapTest, MinimumElement) {
  IBHeap ib_heap;

  // Insert some elements in any order.
  ib_heap.Insert(40);
  ib_heap.Insert(60);
  ib_heap.Insert(10);
  ib_heap.Insert(30);

  EXPECT_EQ(10, ib_heap.Minimum());

  ib_heap.ExtractMinimum();
  EXPECT_EQ(30, ib_heap.Minimum());
}
