// Copyright (C) 2010 OJ Problems
// Author: Su Shi(carmack.shi@gmail.com)
// Problem: Excercise 4
//

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int FindMax(const vector<int> elements, size_t size) {
  assert(1 <= size && elements.size() >= size);

  if (size == 1)
    return elements[size - 1];
  else
    return MAX(elements[size - 1], FindMax(elements, size - 1));
}

int main() {
  size_t size;
  cin >> size;

  vector<int> elements;
  elements.reserve(size);

  for (size_t i = 0; i < size; ++i)
    elements.push_back(i);

  cout << "Max element = " << FindMax(elements, size) << endl;

  return 0;
}