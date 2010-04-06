/*
 * Sample: LCS
 * Algorithm: DP
 * Author: meta
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef enum _DecisionType{
  kNONE,
  kLEFT,
  kUP,
  kLEFT_UP
} DecisionType;

bool init_data(const string& X, const string& Y,
                vector<vector<int> >& lengths,
                vector<vector<DecisionType> >& decisions) {
  // Clear length & decision tables
  lengths.clear();
  decisions.clear();

  if (X.length() == 0 || Y.length() == 0)
    return false;

  // x1, x2, ..., xm
  int m = X.length();
  // y1, y2, ..., yn
  int n = Y.length();
  // By default the length of each sub-problem of LCS is 0.
  vector<int> c_row(n + 1, -1);
  // Stores the length of LCS for sub-problem: Xi & Yj
  // 0 <= i <= m, 0 <= j <= n
  lengths.clear();
  lengths.resize(m + 1, c_row);
  // Stores the desicion of sub-problem while caculate the sub-problem:
  // Xi & Yj
  vector<DecisionType> d_row(n + 1, kNONE);
  decisions.clear();
  decisions.resize(m + 1, d_row);

  return true;
}


// DP: O(m*n)
int LCS_LENGTH(const string& X, const string& Y,
               vector<vector<int> >& lengths,
               vector<vector<DecisionType> >& decisions) {
  // Xi & Yj
  int i, j;
  // x1, x2, ..., xm
  int m = X.length();
  // y1, y2, ..., yn
  int n = Y.length();

  // Xi & Y0
  for (i = 0; i <= m; ++i) {
    lengths[i][0] = 0;
  }

  // X0 & Yj
  for (j = 1; j <= n; ++j) {
    lengths[0][j] = 0;
  }

  // 1 <= i <= m & 1 <= j <= n
  for (i = 1; i <= m; ++i) {
    for (j = 1; j <= n; ++j) {
      if (X[i - 1] == Y[j - 1]) {
        lengths[i][j] = lengths[i - 1][j - 1] + 1;
        // LEFT_UP
        decisions[i][j] = kLEFT_UP;
      } else {  // xi != yj
        if (lengths[i - 1][j] > lengths[i][j - 1]) {
          lengths[i][j] = lengths[i - 1][j];
          decisions[i][j] = kUP;
        } else {
          lengths[i][j] = lengths[i][j - 1];
          decisions[i][j] = kLEFT;
        }
      }
    }
  }

  return lengths[m][n];
}


// Memoized way(Recursive looking up memo) O(m*n)
int LCS_LENGTH_MEMOIZATION(const string& X, const string& Y,
                           vector<vector<int> >& lengths,
                           vector<vector<DecisionType> >& decisions,
                           int i, int j) {
  // Read from memo firstly before calculating it.
  if (lengths[i][j] >= 0)
    return lengths[i][j];

  // i == 0 OR j == 0
  if (i == 0 || j == 0) {
    lengths[i][j] = 0;
    decisions[i][j] = kNONE;
  }
  // Xi == Yj
  else if (X[i - 1] == Y[j - 1]) {
    LCS_LENGTH_MEMOIZATION(X, Y, lengths, decisions, i - 1, j - 1);

    lengths[i][j] = lengths[i - 1][j - 1] + 1;
    decisions[i][j] = kLEFT_UP;
  } else {  // Xi != Yj
    LCS_LENGTH_MEMOIZATION(X, Y, lengths, decisions, i - 1, j);
    LCS_LENGTH_MEMOIZATION(X, Y, lengths, decisions, i, j - 1);

    // UP
    if (lengths[i - 1][j] > lengths[i][j - 1]) {
      lengths[i][j] = lengths[i - 1][j];
      decisions[i][j] = kUP;
    } else {  // Left
      lengths[i][j] = lengths[i][j - 1];
      decisions[i][j] = kLEFT;
    }
    
  }

  return lengths[i][j];
}



// Boolean return value used to indicate whether there's capable printing in
// this function. O(m + n)
void print_LCS(const string& X, const string& Y,
               const vector<vector<DecisionType> >& decisions,
               int i, int j) {
  // Empty Xm, Yn
  if (X.length() == 0 || Y.length() == 0) return;

  // empty sub-sequence
  if (i == 0 || j == 0) return;

  // Print longest common sequences recursively for sub-problem Xi, Yj
  switch (decisions[i][j]) {
    case kLEFT:
      print_LCS(X, Y, decisions, i, j - 1);
      break;

    case kUP:
      print_LCS(X, Y, decisions, i - 1, j);
      break;

    case kLEFT_UP:
      print_LCS(X, Y, decisions, i - 1, j - 1);
      cout << X[i - 1];
      break;

    default:
      break;
  }
}


// Reconstruct the LCS from completed lengths table and the original X & Y,
// without the help of decision tracking table like above code.
// In this way, we can save O(m*n) extra space.
// See Excercises 15.4 - 2 for detailed information.
void print_LCS_without_tracking(const string& X, const string& Y,
                                const vector<vector<int> >& lengths,
                                int i, int j) {
  // Empty Xm, Yn
  if (X.length() == 0 || Y.length() == 0) return;

  // empty sub-sequence
  if (i == 0 || j == 0) return;

  // Print longest common sequences recursively for sub-problem Xi, Yj
  // Left case:
  if (lengths[i][j] == lengths[i][j - 1]) {
    print_LCS_without_tracking(X, Y, lengths, i, j - 1);
  } else if (lengths[i][j] == lengths[i - 1][j]) {  // UP case
    print_LCS_without_tracking(X, Y, lengths, i - 1, j);
  } else {  // Left-Up case
    print_LCS_without_tracking(X, Y, lengths, i - 1, j - 1);
    cout << X[i - 1];
  }
}


int main()
{
  string X, Y;
  vector<vector<int> > lengths;
  vector<vector<DecisionType> > decisions;

  while (cin >> X >> Y) {
    // Data initialization
    if (!init_data(X, Y, lengths, decisions)) break;
    cout << "Length = "
         << LCS_LENGTH(X, Y, lengths, decisions)
         << endl;
    cout << "The longest common sequence is:\n";
    cout << "1. Tracking way: <";
    print_LCS(X, Y, decisions, X.length(), Y.length());
    cout << ">" << endl;
    cout << "2. Non-tracking way: <";
    print_LCS_without_tracking(X, Y, lengths, X.length(), Y.length());
    cout << ">" << endl;
  }

  return 0;
}