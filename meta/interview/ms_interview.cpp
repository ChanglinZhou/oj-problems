// Microsoft Interview Question
// Author: Su Shi(amble_shisu@hotmail.com)
// Date: July 15, 2010
//

// C++ header files
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

// This algorithm is just for positive big integer multiplication, since
// the integer array can only store positive 32-bits integers[0-9].
vector<int> BigIntegerMultiplication(const vector<int>& a,
                                     const vector<int>& b) {
  assert(!a.empty() && !b.empty());

  vector<int> result(a.size() + b.size(), 0);

  int result_size = result.size();

  for (int i = b.size() - 1; i >= 0; --i) {
    int carry = 0;
    int sum = 0;
    int k = 0;
    for (int j = a.size() - 1; j >= 0; --j) {
      k = j + i + 1;
      sum = result[k] + a[j] * b[i] + carry;
      result[k] = sum % 10;
      carry = sum / 10;
    }

    if (carry != 0)
      result[k - 1] = carry;
  }

  vector<int>::iterator it;
  for (it = result.begin();
       it < result.end() - 1; ++it) {
    if (*it != 0)
      break;
  }
  result.erase(result.begin(), it);

  return result;
}

void Print(const vector<int>& result) {
  for (size_t i = 0; i < result.size(); ++i)
    cout << result[i];
  cout << endl;
}

void Test_Positives() {
  vector<int> a;
  a.push_back(9);
  a.push_back(9);
  a.push_back(9);

  vector<int> b;
  b.push_back(9);
  b.push_back(9);
  b.push_back(9);
  b.push_back(9);

  Print(BigIntegerMultiplication(a, b));
}

void Test_PositiveAndZero() {
  vector<int> a;
  a.push_back(0);

  vector<int> b;
  b.push_back(3);
  b.push_back(6);
  b.push_back(4);
  b.push_back(2);

  Print(BigIntegerMultiplication(a, b));
}

int main() {

  Test_Positives();

  Test_PositiveAndZero();

  return 0;
}