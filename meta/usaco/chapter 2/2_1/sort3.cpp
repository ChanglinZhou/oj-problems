/*
ID: amble_s1
LANG: C++
TASK: sort3
*/

#include <fstream>
#include <cassert>
#include <algorithm>

using namespace std;

const int MAX_NUMBER = 1000;

int minimum_exchanges(int sequence[], int n) {

  int sum_exchanges = 0;

  // length of each segment, which stands for 1, 2, 3.
  int segment_length[3] = { 0, 0, 0 };
  for (int i = 0; i < n; ++i)
    ++segment_length[sequence[i] - 1];

  // Number of each elements stored in each segment.
  int segment_status[3][3] = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };
  for (int j = 0; j < n; ++j) {
    if (j < segment_length[0])
      ++segment_status[0][sequence[j] - 1];
    else if (j < segment_length[0] + segment_length[1])
      ++segment_status[1][sequence[j] - 1];
    else
      ++segment_status[2][sequence[j] - 1];
  }

  int num_exchanges = 0;

  // One exchange to reset every two positions.
  // Remember to update the stored elements' status in each segment, since we'll
  // use them in later exchanges.
  for (int i = 0; i < 3; ++i) {
    for (int j = i + 1; j < 3; ++j) {
      num_exchanges = min(segment_status[i][j], segment_status[j][i]);
      if (num_exchanges <= 0) continue;

      sum_exchanges += num_exchanges;
      segment_status[i][j] -= num_exchanges;
      segment_status[j][j] += num_exchanges;
      segment_status[j][i] -= num_exchanges;
      segment_status[i][i] += num_exchanges;
    }
  }

  // Twice exchange to reset every three positions.
  // segment_status[0][1] and segment_status[0][2] can't be both > 0.
  num_exchanges = segment_status[0][1] + segment_status[0][2];
  if (num_exchanges > 0) {
    sum_exchanges += 2 * num_exchanges;

    // Update the status of each segment.
    if (segment_status[0][1] > 0) {
      segment_status[1][2] -= num_exchanges;
      segment_status[2][2] += num_exchanges;
      segment_status[2][0] -= num_exchanges;
      segment_status[1][0] += num_exchanges;

      segment_status[0][1] -= num_exchanges;
      segment_status[1][1] += num_exchanges;
      segment_status[1][0] -= num_exchanges;
      segment_status[0][0] += num_exchanges;
    } else {  // segment_status[0][2] > 0
      segment_status[2][1] -= num_exchanges;
      segment_status[1][1] += num_exchanges;
      segment_status[1][0] -= num_exchanges;
      segment_status[2][0] += num_exchanges;

      segment_status[0][2] -= num_exchanges;
      segment_status[2][2] += num_exchanges;
      segment_status[2][0] -= num_exchanges;
      segment_status[0][0] += num_exchanges;
    }
  }

  return sum_exchanges;
}

int main() {
  ifstream infile("sort3.in");
  ofstream outfile("sort3.out");
  if (!infile || !outfile) return -1;

  int sequence[MAX_NUMBER];
  int n;

  while (infile >> n) {
    for (int i = 0; i < n; ++i)
      infile >> sequence[i];

    outfile << minimum_exchanges(sequence, n) << endl;
  }
  return 0;
}
