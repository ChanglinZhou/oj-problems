/*
ID: amble_s1
LANG: C++
TASK: milk3
*/

#include <fstream>
#include <cassert>
#include <set>

using namespace std;

// The maximum capacity for all three buckets.
const int MAX_CAPACITY = 20;

// Capacity of bucket A, B, C.
int AL, BL, CL;


// Intermediate state which describes i liters milk in bucket A, j liters milker
// in bucket B, (CL - i - j) liters in bucket C.
// If this state can be hit during DFS, which means it's a node in the searching
// tree.
bool State[MAX_CAPACITY + 1][MAX_CAPACITY + 1];

// The possible liter set in bucket C.
set<int> LiterSet;

// Operation type, which indicates that FJ pour milk from X to Y.
typedef enum _Operation { A2B, A2C, B2A, B2C, C2A, C2B } Operation;

// Initialize the all possible states to be non-hit.
void Init() {
  for (int i = 0; i <= MAX_CAPACITY; ++i)
    for (int j = 0; j < MAX_CAPACITY; ++j)
      State[i][j] = false;
}

// Search the all the possible states of three buckets from initial state(0, 0).
void Search_State(int i, int j) {
  // Check invalid liters in bucket A and B.
  if (i < 0 || i > AL ||
      j < 0 || j > BL)
      return;

  // Avoid circular search.
  if (State[i][j]) return;

  // If bucket A is empty, insert current liters in bucket C in the set.
  if (i == 0) LiterSet.insert(CL - j);

  // Assume we change to this state.
  State[i][j] = true;
  // We've six choices to do pouring milk.
  for (int op = A2B; op <= C2B; ++op) {
    switch(op) {
      case A2B:
        if (i > 0 && j < BL) {
          int transfer = min(i, BL - j);
          Search_State(i - transfer, j + transfer);
        }
        break;

      case A2C:
        if (i > 0) {
          Search_State(0, j);
        }
        break;

      case B2A:
        if (j > 0 && i < AL) {
          int transfer = min(AL - i, j);
          Search_State(i + transfer, j - transfer);
        }
        break;

      case B2C:
        if (j > 0) {
          Search_State(i, 0);
        }
        break;

      case C2A:
        if (i + j < CL && i < AL) {
          int transfer = min(AL - i, CL - i - j);
          Search_State(i + transfer, j);
        }
        break;

      case C2B:
        if (i + j < CL && j < BL) {
          int transfer = min(BL - j, CL - i - j);
          Search_State(i, j + transfer);
        }
        break;

      default:
        break;
    }
  }
  // Remove the change, back-tracking to previous state to do other choice.
  State[i][j] = false;
}

// Print the possible liters for bucket C.
void Print(ofstream& outfile) {
  int printed = false;
  set<int>::const_iterator it = LiterSet.begin();
  for (set<int>::const_iterator it = LiterSet.begin();
       it != LiterSet.end(); ++it) {
    if (it != LiterSet.begin())
      outfile << " ";
    outfile << *it;
  }

  if (!LiterSet.empty()) outfile << endl;
}

int main() {
  // Open the input & output files.
  ifstream infile("milk3.in");
  ofstream outfile("milk3.out");
  if (!infile || !outfile) return -1;

  while (infile >> AL >> BL >> CL) {
    Init();
    Search_State(0, 0);
    Print(outfile);
  }

  return 0;
}
