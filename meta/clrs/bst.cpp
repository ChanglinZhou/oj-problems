/*
 * Chapter 12 Binary Search Tree
 * Author: meta
 */

// STD
#include <stack>
#include <iostream>
using namespace std;

#include "bst.h"

typedef Node<int> IntNode;

// Recursive edition for traversing the whole tree with in-order manner, which
// makes the visited node ordered.
void in_order_tree_walk(IntNode* x) {
  if (x == NULL) return;

  in_order_tree_walk(x->left);
  cout << x->value << endl;
  in_order_tree_walk(x->right);
}

// non-recursive with auxiliary stack
void in_order_tree_walk2(IntNode* x) {
  stack<IntNode*> nodes;

  while (x || !nodes.empty()) {
    if (x) {
      nodes.push(x);
      x = x->left;
    } else {
      x = nodes.top();
      cout << x->value << endl;
      nodes.pop();
      x = x->right;
    }
  }
}

// non-recursive without stack support, with successor similar mechanism.
void in_order_tree_walk3(IntNode* x) {
  if (x == NULL) return;

  // Find the first element to be printed in the tree rooted at x.
  while (x->left) {
    x = x->left;
  }

  // Print current element, and find next successor.
  while (x) {
    cout << x->value << endl;
    // If x have right sub-tree, then we find the smallest node in it like the
    // above way.
    if (x->right) {
      x = x->right;
      while (x->left) {
        x = x->left;
      }
    } else {
      // If no right sub-tree, find the lowest ancestor y of x that x is in y's
      // left sub-tree.
      IntNode* y = x->parent;
      while (y && y->left != x) {
        x = y;
        y = x->parent;
      }
      x = y;
    }
  }
}

// Search in the BST rooted at x(Recursive).
IntNode* tree_search(IntNode* x, int k) {
  if (x == NULL || x->value == k) return x;

  if (k < x->value)
    return tree_search(x->left, k);
  else
    return tree_search(x->right, k);
}

// Search in the BST rooted at x(Non-recursive).
IntNode* iterative_tree_search(IntNode* x, int k) {
  while (x != NULL && x->value != k) {
    if (k < x->value)
      x = x->left;
    else
      x = x->right;
  }

  return x;
}

IntNode* tree_minimum(IntNode* x) {
  while (x && x->left) {
    x = x->left;
  }
  return x;
}

IntNode* tree_maximum(IntNode* x) {
  while (x && x->right) {
    x = x->right;
  }
  return x;
}

IntNode* tree_successor(IntNode* x) {
  if (x == NULL) return x;

  if (x->right) return tree_minimum(x->right);

  IntNode* y = x->parent;
  while (y && y->left != x) {
    x = y;
    y = x->parent;
  }

  return y;
}

IntNode* tree_predecessor(IntNode* x) {
  if (x == NULL) return x;

  if (x->left) return tree_maximum(x->left);

  IntNode* y = x->parent;
  while (y && y->right != x) {
    x = y;
    y = x->parent;
  }

  return y;
}

// Newly inserted node is the leaf node(non-recursive).
void tree_insert(IntNode*& root, IntNode* z) {
  if (z == NULL) return;

  IntNode* x = root;
  IntNode* y = x;

  while (x) {
    y = x;
    if (z->value < x->value)
      x = x->left;
    else
      x = x->right;
  }

  z->parent = y;
  z->left = NULL;
  z->right = NULL;

  // BST rooted at node z.
  if (y == NULL) {
    root = z;
    return;
  }

  // Attach node z to node y's sub-tree.
  if (z->value < y->value)
    y->left = z;
  else
    y->right = z;
}


// Delete a node z from BST
void tree_delete(IntNode*& root, IntNode* z) {
  if (root == NULL || z == NULL)
    return;

  // Node to be deleted.
  IntNode* y = NULL;
  if (z->left == NULL || z->right == NULL)
    y = z;
  else
    y = tree_successor(z);

  // Root node of sub-tree of node y.
  IntNode* x = NULL;
  if (y->left)
    x = y->left;
  else
    x = y->right;

  // Update x node's parent pointer if x is not null.
  if (x) x->parent = y->parent;

  // Update y node's parent:
  // 1. y is the root node, if it's true that y must be equal to z, which means
  // z can't have two sub-trees.
  if (y->parent == NULL)
    root = x;
  else if (y->parent->left == y)
    y->parent->left = x;
  else
    y->parent->right = x;

  // In this case, we transfer deletion from node z to its successor y.
  if (y != z)
    z->value = y->value;

  delete y;
}


// Newly inserted node is the leaf node(recursive).
void tree_insert2(IntNode*& root, IntNode* z) {
  if (z == NULL) return;

  if (root == NULL) {
    z->left = z->right = NULL;
    root = z;
    return;
  }

  if (z->value < root->value) {
    if (root->left == NULL) z->parent = root;
    tree_insert2(root->left, z);
  } else {
    if (root->right == NULL) z->parent = root;
    tree_insert2(root->right, z);
  }

}

// Delete a node z from BST(improved), which moves z's successor to z's logical
// location in the tree, instead of copying data from y to z, and delete y.
void tree_delete_improved(IntNode*& root, IntNode* z) {
  if (root == NULL || z == NULL)
    return;

  // Node to be deleted.
  IntNode* y = NULL;
  if (z->left == NULL || z->right == NULL)
    y = z;
  else
    y = tree_successor(z);

  // Root node of sub-tree of node y.
  IntNode* x = NULL;
  if (y->left)
    x = y->left;
  else
    x = y->right;

  // Update x node's parent pointer if x is not null.
  if (x) x->parent = y->parent;

  // Update y node's parent:
  // 1. y is the root node, if it's true that y must be equal to z, which means
  // z can't have two sub-trees.
  if (y->parent == NULL)
    root = x;
  else if (y->parent->left == y)
    y->parent->left = x;
  else
    y->parent->right = x;

  // In this case, after splice out the node y, we should replace z with y in
  // z's logical location. This can avoid invalid pointer y used in other code.
  if (y != z) {
    y->left = z->left;
    y->right = z->right;
    y->parent = z->parent;
    y = z;
  }

  delete y;
}

int main() {

  int data[7] = {5, 4, 1, 10, 21, 17, 16};

  // Built from empty tree.
  IntNode* root = NULL;
  for (int i = 0; i < sizeof(data) / sizeof(int); ++i) {
    IntNode* z = new IntNode;
    z->value = data[i];
    z->parent = NULL;
    z->left = NULL;
    z->right = NULL;
    tree_insert2(root, z);
  }

  in_order_tree_walk2(root);

  cout << "Minimum node in tree is " << tree_minimum(root)->value << endl;
  cout << "Maximum node in tree is " << tree_maximum(root)->value << endl;

  return 0;
}