// OJ Problems.
// OJL Copyright(2010), all rights reserved.
//
// Problem: #1074 : To the Max
// Authur: Meta(carmack.shi@gmail.com)
//

// Header file
#include <iostream>
#include <vector>
#include <cassert>
#include <limits>

using namespace std;

vector<vector<int> > TopLeftSubMatrix;

// Pre-calculate the sum of sub-matrix in a table:
// top-left: matrix[0, 0]
// right-bottom: matrix[i, j], 0 <= i, j < n.
// Sum[matrix[0, 0, i, j]] =
//    Sum[matrix[0, 0, i-1, j]] +
//    Sum[matrix[0, 0, i, j-1]] -
//    Sum[matrix[0, 0, i-1, j-1]]
void Initialize(const vector<vector<int> >& matrix) {
  assert(matrix.size() == matrix[0].size());

  size_t n = matrix.size();
  vector<int> row(matrix[0].size(), 0);
  TopLeftSubMatrix.resize(matrix.size(), row);

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      TopLeftSubMatrix[i][j] += matrix[i][j];
      if (i > 0)
        TopLeftSubMatrix[i][j] += TopLeftSubMatrix[i - 1][j];
      if (j > 0)
        TopLeftSubMatrix[i][j] += TopLeftSubMatrix[i][j - 1];
      if (i > 0 && j > 0)
        TopLeftSubMatrix[i][j] -= TopLeftSubMatrix[i-1][j - 1];
    }
  }
}


int FindLargestSumInSubMatrix(const vector<vector<int> >& matrix) {
  assert(!matrix.empty() && matrix.size() == matrix[0].size());

  Initialize(matrix);

  size_t n = matrix.size();

  int max_sum = numeric_limits<int>::min();

  for (size_t top = 0; top < n; ++top) {
    for (size_t bottom = top; bottom < n; ++bottom) {
      for (size_t left = 0; left < n; ++left) {
        for (size_t right = left; right < n; ++right) {
          int new_sum = TopLeftSubMatrix[bottom][right];
          if (top > 0)
            new_sum -= TopLeftSubMatrix[top-1][right];
          if (left > 0)
            new_sum -= TopLeftSubMatrix[bottom][left-1];
          if (top > 0 && left > 0)
            new_sum += TopLeftSubMatrix[top-1][left-1];
          if (new_sum > max_sum)
            max_sum = new_sum;
        }
      }
    }
  }

  return max_sum;
}


int main() {
  size_t n;
  vector<vector<int> > matrix;

  while (cin >> n) {
    vector<int> row(n, 0);
    matrix.resize(n, row);
    for (size_t i = 0; i < n; ++i)
      for (size_t j = 0; j < n; ++j)
        cin >> matrix[i][j];

    cout << FindLargestSumInSubMatrix(matrix) << endl;
  }

  return 0;
}