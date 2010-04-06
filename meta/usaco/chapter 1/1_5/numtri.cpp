/*
ID: amble_s1
LANG: C++
TASK: numtri
*/

#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

// Dynamic Programming to construct the optimal solutions for sub-problems by
// bottom-up way.
int find_higest_sum(const vector<vector<int> >& number_triangle) {
  // Total rows of number triangle.
  size_t row_count = number_triangle.size();
  // Optimal solutions to sub-prolbem sums[i][j], which means the highest sum
  // traversing from top to the jth element in the ith row of number triangle.
  vector<vector<int> > sum_table(row_count);
  for (size_t i = 0; i < row_count; ++i) {
    // Intialize the each row of sum_table.
    size_t row_size = number_triangle[i].size();
    vector<int> sum_row(row_size);
    // Calculates the each element in the sums from bottom up by the
    // following recurrence:
    //              { triangle[i][j], i = 0                                 }
    //              { triangle[i][j] + sums[i - 1][j - 1] + sums[i - 1][j], }
    //              {     i > 0 and 0 < j < i                               }
    // sums[i][j] = { triangle[i][j] + sums[i - 1][j - 1], i > 0 and j = i  }
    //              { triangle[i][j] + sums[i - 1][j], i > 0 and j = 0      }
    //              {                                                       }
    for (size_t j = 0; j < row_size; ++j) {
      sum_row[j] = number_triangle[i][j];
      int left_upper, right_upper, max_upper;
      max_upper = left_upper = right_upper = 0;

      if (j > 0)
        left_upper = sum_table[i - 1][j - 1];
      if (j < row_size - 1)
        right_upper = sum_table[i - 1][j];

      max_upper = max(left_upper, right_upper);
      sum_row[j] += max_upper;
    }
    sum_table[i] = sum_row;
  }

  // Find the highest elment in the last row of sum_table.
  int highest = 0;
  if (!sum_table.empty()) {
    const vector<int>& last_sum_row = sum_table.back();
    for (size_t k = 0; k < last_sum_row.size(); ++k) {
      int value = last_sum_row[k];
      if (value > highest)
        highest = value;
    }
  }

  return highest;
}

int main() {
  ifstream infile("numtri.in");
  ofstream outfile("numtri.out");
  if (!infile && !outfile) return -1;

  // Read file to initialize number triangle.
  int R;
  vector<vector<int> > number_triangle;
  while (infile >> R) {
    number_triangle.resize(R);
    for (int i = 0; i < R; ++i) {
      vector<int> row(i + 1);
      for (int j = 0; j <= i; ++j) {
        infile >> row[j];
      }
      number_triangle[i] = row;
    }
    outfile << find_higest_sum(number_triangle) << endl;
  }

  return 0;
}