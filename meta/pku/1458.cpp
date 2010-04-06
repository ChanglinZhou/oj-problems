/*
 * Problem: Common Subsequence(1458)@POJ
 * Algorithm: LCS of DP
 * Author: meta
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int LCS_Length(const string& X, const string& Y)
{
  if (X.length() == 0 || Y.length() == 0)
    return 0;

  // x1, x2, ..., xm
  int m = X.length();
  // y1, y2, ..., yn
  int n = Y.length();
  // Stores the length of LCS for sub-problem: Xi & Yj
  // 0 <= i <= m, 0 <= j <= n
  vector<int> c_row(n + 1);
  vector<vector<int> > c(m + 1, c_row);

  int i, j;
  // Xi & Y0
  for (i = 0; i <= m; ++i) {
    c[i][0] = 0;
  }
  // X0 & Yj
  for (j = 1; j <= n; ++j) {
    c[0][j] = 0;
  }

  // 1 <= i <= m & 1 <= j <= n
  for (i = 1; i <= m; ++i) {
    for (j = 1; j <= n; ++j) {
      if (X[i - 1] == Y[j - 1]) {
        c[i][j] = c[i - 1][j - 1] + 1;
      } else {  // xi != yj
        c[i][j] = max(c[i - 1][j], c[i][j - 1]);
      }
    }
  }

  return c[m][n];
}

int main()
{
  string X, Y;
  while (cin >> X >> Y) {
    cout << LCS_Length(X, Y) << endl;
  }

  return 0;
}