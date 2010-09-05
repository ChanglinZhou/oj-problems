// This file includes some interesting interview questions related to
// numerical computation.

#include <cassert>
#include <iostream>

using namespace std;

const size_t kInt32Size = sizeof(int) * 8;

bool IsZero(double value) {
  return (!(value < 0.0) && !(value > 0.0));
}

// Exponent computation
double Power(double base, int exponent) {
  assert(!IsZero(base) || exponent >= 0);

  if (exponent == 0)
    return 1;

  if (exponent < 0) {
    base = 1 / base;  // precision lost?
    exponent = -exponent;
  }

  double exp_table[kInt32Size];
  exp_table[0] = base;
  for (size_t i = 1; i < kInt32Size; ++i) {
    exp_table[i] = exp_table[i - 1] * exp_table[i - 1];
  }

  double value = 1.0;

  for (size_t j = 0; j < kInt32Size; ++j) {
    if (exponent & (1 << j))
      value *= exp_table[j];
  }

  return value;
}

void PowerTest() {
  double base, value;
  int exponent;

  // Case 1:
  base = 2;
  exponent = 4;
  value = Power(base, exponent);
  if (value == 16.0)
    cout << "Pass" << endl;
  else
    cerr << "Fail" << endl;

  // Case 2:
  base = 0;
  exponent = 0;
  value = Power(base, exponent);
  if (value == 1.0)
    cout << "Pass" << endl;
  else
    cerr << "Fail" << endl;

  // Case 3:
  base = -2;
  exponent = 4;
  value = Power(base, exponent);
  if (value == 16.0)
    cout << "Pass" << endl;
  else
    cerr << "Fail" << endl;
}

int main() {
  PowerTest();

  return 0;
};