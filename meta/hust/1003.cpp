#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

const int MOD = 1000000007;

const int MAX = 100 * 1000 + 1;

vector<int> Results(MAX, -1);

long hash(double x) {
  assert(x >= 0);

  return long(100 * x + 1e-8);
}

void Init() {
  fill(Results.begin(), Results.begin() + 313, 1);

  for (int i = 314; i < MAX; ++i) {
    Results[i] = (Results[i - 100] + Results[i - 314]) % MOD;
  }
}

int SFib(double number) {

  if (number < 0) return 0;

  return Results[hash(number)];
}

int main() {

  int t;
  double number;

  cin >> t;

  Init();

  for (int i = 0; i < t; ++i) {
    cin >> number;
    cout << SFib(number) << endl;
  }

  return 0;
}
