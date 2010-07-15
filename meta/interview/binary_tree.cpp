// Binary Tree Interview Questions
// Author: Su Shi(amble_shisu@hotmail.com)
// Date: July 15, 2010
//

// C++ header files
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

// For simplify the problem, the satellite data stored inside the tree node is
// integer type.

struct Node {
  Node(int data)
    : data_(data), left_child_(NULL), right_child_(NULL) { }
  int data_;
  Node* left_child_;
  Node* right_child_;
};

Node* BuildTree(const vector<int>& pre_order_sequence,
                const vector<int>& in_order_sequence,
                size_t pre_order_index,
                size_t in_order_start,
                size_t in_order_end) {

  assert(!pre_order_sequence.empty() && !in_order_sequence.empty());
  assert(pre_order_sequence.size() == in_order_sequence.size());

  if (pre_order_index >= pre_order_sequence.size())
    return NULL;

  Node* root = new Node(pre_order_sequence[pre_order_index]);

  size_t root_index;
  for (root_index = in_order_start; root_index < in_order_end; ++root_index) {
    if (in_order_sequence[root_index] == root->data_)
      break;
  }

  root->left_child_ = BuildTree(pre_order_sequence, in_order_sequence,
                                ++pre_order_index,
                                in_order_start, root_index);

  root->right_child_ = BuildTree(pre_order_sequence, in_order_sequence,
                                pre_order_index + (root_index - in_order_start),
                                root_index + 1, in_order_end);

  return root;
}

void Test() {
  vector<int> pre_order_sequence;
  pre_order_sequence.reserve(4);
  pre_order_sequence.push_back(3);
  pre_order_sequence.push_back(1);
  pre_order_sequence.push_back(2);
  pre_order_sequence.push_back(4);

  vector<int> in_order_sequence;
  in_order_sequence.reserve(4);
  in_order_sequence.push_back(1);
  in_order_sequence.push_back(2);
  in_order_sequence.push_back(3);
  in_order_sequence.push_back(4);

  Node* root = BuildTree(pre_order_sequence, in_order_sequence,
                         0, 0, in_order_sequence.size());
}

int main() {

  Test();

  return 0;
}
