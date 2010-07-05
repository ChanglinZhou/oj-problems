#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include <algorithm>

using namespace std;

typedef unsigned int UINT8;

vector<UINT8> ConvertFromDec(int n, int base) {
  assert(n >= 0 && base >= 2);

  vector<UINT8> data;

  while (n) {
    data.insert(data.begin(), n % base);
    n /= base;
  }

  return data;
}

int ConvertToDec(const vector<UINT8>& data, int base) {
  assert(base >= 2);

  int value = 0;

  for (size_t i = 0; i < data.size(); ++i) {
    value = value * base + data[i];
  }

  return value;
}

int XOR(int a, int b, int base) {
  assert(base >= 2 && a >= 0 && b >= 0);

  vector<UINT8> converted_a = ConvertFromDec(a, base);
  vector<UINT8> converted_b = ConvertFromDec(b, base);

  vector<UINT8> converted_c;

  size_t i, j;
  for (i = converted_a.size() - 1, j = converted_b.size() - 1;
       (i + 1) >= 1 && (j + 1) >= 1; --i, --j) {
    converted_c.insert(converted_c.begin(),
                       (converted_a[i] + converted_b[j]) % base);
  }

  if (i + 1 >= 1)
    converted_c.insert(converted_c.begin(),
                       converted_a.begin(), converted_a.begin() + i + 1);

  if (j + 1 >= 1)
    converted_c.insert(converted_c.begin(),
                       converted_b.begin(), converted_b.begin() + j + 1);

  return ConvertToDec(converted_c, base);
}

int main() {

  int t, a, b;
  string op;

  cin >> t;

  for (int i = 0; i < t; ++i) {
    cin >> a >> op >> b;

    cout << XOR(a, b, op.length() + 1) << endl;
  }


  return 0;

}