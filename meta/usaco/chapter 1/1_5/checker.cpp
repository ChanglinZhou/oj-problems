/*
ID: amble_s1
LANG: C++
TASK: checker
*/

#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

// The maximum print times for solutions.
const int MAX_PRINT_TIMES = 3;
// The maximum size of checker board.
const int MAX_BOARD_SIZE = 13;

// Record the statuses of all diagonals(two kinds), and all columns, which stand
// for whether it's valid or not.
class CheckerBoard {
 public:
   CheckerBoard()
    : board_size(0) {
   };

  void Reset(int size) {
    board_size = size;
    // True means there's no attacking threat on this direction.
    fill(column, column + board_size, true);
    fill(nw2se, nw2se + 2 * board_size - 1, true);
    fill(sw2ne, sw2ne + 2 * board_size - 1, true);
  };

  // Stands for the status of columns[0...board_size - 1]
  bool column[MAX_BOARD_SIZE];
  // Stands for the status of diagonal run from north west to south east.
  // The position(i, j) on such kind of diagonal has the following relationship:
  // j - i = K, 1 - BOARD_SIZE <= K <= BOARD_SIZE - 1.
  // We store status of each kind of diagonal(K) on nw2se[K + BOARD_SIZE - 1].
  bool nw2se[2 * MAX_BOARD_SIZE - 1];
  // Stands for the status of diagonal run from south west to north east.
  // The position(i, j) on such kind of diagonal has the following relationship:
  // j + i = L, 0 <= L <= 2 * BOARD_SIZE - 2.
  // We store status of each kind of diagonal(L) on sw2ne[L].
  bool sw2ne[2 * MAX_BOARD_SIZE - 1];
  int board_size;
 private:
  CheckerBoard& operator=(const CheckerBoard& rhs);
  CheckerBoard(const CheckerBoard& rhs);
};

// Double-linked list node, used to keep the remain candidate column positions
// on the checker board.
typedef struct _Node {
  int column;
  _Node* prev;
  _Node* next;
} Node;

// The output file.
ofstream outfile("checker.out");

// Check to see whether this position(i, j) is attacked by other checkers.
bool IsValidPosition(int i, int j, const CheckerBoard& checker_board) {
  int board_size = checker_board.board_size;
  assert(board_size > 0 &&
         0 <= i && i < board_size && 0 <= j && j < board_size);

  return (checker_board.column[j] &&
          checker_board.nw2se[j - i + board_size - 1] &&
          checker_board.sw2ne[j + i]);
}

// Update the status of column, diagonals related to this position(i, j) with
// specified value.
void UpdateCheckerBoard(int i, int j, bool value, CheckerBoard& checker_board) {
  int board_size = checker_board.board_size;
  assert(board_size > 0 &&
         0 <= i && i < board_size && 0 <= j && j < board_size);

  checker_board.column[j] = value;
  checker_board.nw2se[j - i + board_size - 1] = value;
  checker_board.sw2ne[j + i] = value;
}

// Returns the total number of all possible solutions.
int CheckerChallenge(int row, int board_size) {
  assert(row >= 0 && board_size > 0);

  // The status of checker board.
  static CheckerBoard checker_board;
  // The pointer points to the head element of the candidates.
  static Node* candidate_head = NULL;
  // The solution records the selected column for each row.
  static int solution[MAX_BOARD_SIZE];

  // Initialization at the begin of each search.
  if (row == 0) {
    // Reset the status of the checker board.
    checker_board.Reset(board_size);
    // Memory pool.
    static Node NodeList[MAX_BOARD_SIZE];
    // Creates the double-linked candidate list.
    for (int i = board_size - 1; i >= 0; --i) {
      Node* new_node = &NodeList[i];
      new_node->column = i;
      new_node->prev = NULL;
      new_node->next = candidate_head;
      if (candidate_head) {
        candidate_head->prev = new_node;
      }
      candidate_head = new_node;
    }
    // Initialize the solution to be 0 filled.
    fill(solution, solution + MAX_BOARD_SIZE, 0);
  }

  // Reach one of the possible solution, just print it out.
  if (row >= board_size) {
    static int print_times = 0;
    // We only print at most the first three solutions for each board size.
    // Notice the solution will be printed in ascending order, since we
    // generate solutions from low column to high one.
    if (print_times < MAX_PRINT_TIMES) {
      for (int i = 0; i < board_size; ++i) {
        if (i > 0) outfile << " ";
        outfile << solution[i];
      }
      outfile << endl;
      ++print_times;
    }
    // We got one solution!
    return 1;
  }

  // Total solutions based on the statuses of previous rows, to all of its and
  // its possible subsequent rows' statuses.
  int solution_number = 0;
  // Try to put the checker on one of column from candidate list for current
  // row, and continue to put the checkers for next row by recursive way.
  for (Node* p = candidate_head; p != NULL; p = p->next) {
    int column = p->column;
    // If the position could be attacked by other checkers, stop put it here.
    if (!IsValidPosition(row, column, checker_board)) continue;
    // Record the column number for current row.
    solution[row] = column + 1;
    // Update the status of the checker board according to the checker position
    // (row, column).
    UpdateCheckerBoard(row, column, false, checker_board);
    // Remove current candidate column from the list(Dancing Link).
    if (p->prev) p->prev->next = p->next;
    if (p->next) p->next->prev = p->prev;
    if (p == candidate_head) candidate_head = p->next;
    // Recurisve to put checkers for the subsequent rows.
    solution_number += CheckerChallenge(row + 1, board_size);
    // Back-tracking to cancel current chosen column in the solution record.
    solution[row] = 0;
    // Restore the checker board to be the one which don't have checker put
    // on position(row, column).
    UpdateCheckerBoard(row, column, true, checker_board);
    // Restore the candiate column into the list(Dancing Link).
    if (p->prev) p->prev->next = p;
    if (p->next) p->next->prev = p;
    if (p->prev == NULL) candidate_head = p;
  }

  return solution_number;
}

int main() {
  ifstream infile("checker.in");
  if (!infile || !outfile) return -1;

  int n;
  while (infile >> n) {
    outfile << CheckerChallenge(0, n) << endl;
  }

  return 0;
}
