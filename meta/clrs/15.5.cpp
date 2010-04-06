#include <iostream>
#include <stack>
using namespace std;

struct Range {
  Range(int _i, int _j)
    : i(_i), j(_j) {};
  int i;
  int j;
};

int root[6][6] = { {-1, -1, -1, -1, -1, -1},
                   {-1, 1, 1, 2, 2, 2},
                   {-1, -1, 2, 2, 2, 4},
                   {-1, -1, -1, 3, 4, 5},
                   {-1, -1, -1, -1, 4, 5},
                   {-1, -1, -1, -1, -1, 5} };

// Exercises 15.5-1

// Recursive edition
void construct_optimal_bst(int* root, int n, int i, int j) {
  if (j == i - 1 || root == NULL) return;

  // j >= i
  int r = *(root + i * n + j);
  if (i == 1 && j == n - 1) {
    cout << "K" << r << " is the root" << endl;
  }

  if (r == i) {
    cout << "D" << (i - 1) << " is left child of "
         << "K" << r << endl;
  } else {
    int ls = *(root + i * n + r - 1);
    cout << "K" << ls << " is left child of "
         << "K" << r << endl;
    construct_optimal_bst(root, n, i, r - 1);
  }

  if (r == j) {
    cout << "D" << j << " is right child of "
         << "K" << r << endl;
  } else {
    int rs = *(root + (r + 1)* n + j);
    cout << "K" << rs << " is right child of "
         << "K" << r << endl;
    construct_optimal_bst(root, n, r + 1, j);
  }
}

// Non-recursive edition
void nr_construct_optimal_bst(int* root, int n) {
  if (n < 1 || root == NULL) return;

  // Push the root node
  stack<Range> st;
  st.push(Range(1, n - 1));

  while (!st.empty()) {
    Range cur = st.top();
    int i, j, r;
    i = cur.i;
    j = cur.j;

    // empty sub-tree
    if (j == i - 1) {
      st.pop();
      // if there's no parent node, just break the loop.
      if (st.empty()) break;
      // pop nearest ancestor, push it's right sub-tree.
      Range parent = st.top();
      st.pop();
      i = parent.i;
      j = parent.j;
      r = *(root + i * n + j);
      if (r == j) {
        cout << "D" << j << " is right child of "
          << "K" << r << endl;
      } else {
        int rs = *(root + (r + 1)* n + j);
        cout << "K" << rs << " is right child of "
          << "K" << r << endl;
      }
      st.push(Range(r + 1, j));
    } else { // j >= i
      r = *(root + i * n + j);
      // root node
      if (i == 1 && j == n - 1) {
        cout << "K" << r << " is the root" << endl;
      }

      // left sub-tree
      if (r == i) {
        cout << "D" << (i - 1) << " is left child of "
          << "K" << r << endl;
      } else {
        int ls = *(root + i * n + r - 1);
        cout << "K" << ls << " is left child of "
          << "K" << r << endl;
      }
      st.push(Range(i, r - 1));
    }

  };
}

int main() {
  //construct_optimal_bst(&root[0][0], 6, 1, 5);
  nr_construct_optimal_bst(&root[0][0], 6);
  return 0;
}