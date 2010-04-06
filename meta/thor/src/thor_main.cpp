// Copyright (c) 2010, Su Shi <carmack.shi [at] gmail.com>
//
// All rights reserved.

// STL
#include <iostream>
using namespace std;

#include "thor_binomial_heap.h"

typedef thor::BinomialHeap<int> IntegerHeap;

int main(int argc, char **argv) {

  IntegerHeap heap;

  heap.Insert(1);
  heap.Insert(4);
  heap.Insert(2);

  cout << heap.Minimum() << endl;
  return 0;
}