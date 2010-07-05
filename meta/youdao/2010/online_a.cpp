#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

typedef vector<int> Row;
typedef vector<Row> Matrix;

vector<int> sequence;
vector<bool> visited;

void Print(const vector<int>& sequence) {
  for (size_t i = 0; i < sequence.size(); ++i) {
    if (i > 0)
      cout << " ";
    cout << sequence[i];
  }

  if (!sequence.empty())
    cout << endl;
}

bool FindSequence(const Matrix& matrix, int n, int e, int h) {
  visited[e] = true;
  sequence.push_back(e);

  bool found = false;
  if (sequence.size() == n && sequence.back() == h) {
    cout << "YES" << endl;
    Print(sequence);
    found = true;
  }

  const Row& row = matrix[e];

  for (size_t j = 0; j < row.size() && !found; ++j) {
    if (row[j] == 0 || visited[j])
      continue;

    if (j == h && sequence.size() < n - 1))
      continue;

    found = FindSequence(matrix, n, j, h);
  }

  visited[e] =false;
  sequence.pop_back();

  return found;
}


int main() {

  int n, e, h, d, i, j;

  cin >> n >> e >> h;

  Row row(n, 0);
  Matrix matrix(n, row);
  sequence.reserve(n);
  visited.resize(n);

  for (i = 0; i < n; ++i) {
    cin >> d;
    for (int k = 0; k < d; ++k) {
      cin >> j;
      matrix[i][j] = matrix[j][i] = 1;
    }
  }

  if (!FindSequence(matrix, n, e, h))
    cout << "NO" << endl;

  return 0;
}