// Copyright (c) 2010, Su Shi <carmack.shi [at] gmail.com>
//
// All rights reserved.

#ifndef THOR_BINOMIAL_TREE_H_
#define THOR_BINOMIAL_TREE_H_

// C++ library headers.
#include <cassert>

#include "thor_basic_types.h"

namespace thor {

template <typename T> class BinomialHeap;

template <typename T>
struct BinomialTreeNode {
  BinomialTreeNode()
    : parent(NULL), sibling(NULL), child(NULL), degree(0), value(T()) {
  }
  BinomialTreeNode(const T& val)
    : parent(NULL), sibling(NULL), child(NULL), degree(0), value(val) {
  }

  // Pointer to parent. If it's root, parent = NULL.
  BinomialTreeNode* parent;
  // Pointer to its sibling immediately to its right.
  BinomialTreeNode* sibling;
  // Pointer to leftmost child.
  BinomialTreeNode* child;
  // Number of children.
  int degree;

  // T Data Field.
  T value;
};

template <typename T>
class BinomialTree {
 public:
  BinomialTree()
    : root_(NULL), prev_(NULL), next_(NULL) { }
  BinomialTree(BinomialTreeNode<T>* root)
    : root_(root), prev_(NULL), next_(NULL) {
  }
  ~BinomialTree() {
    DestroyTree(root_);
  }

  // Get/Set next binomial tree in the root list.
  const BinomialTree<T>* GetNext() const {
    return next_;
  }
  BinomialTree<T>* GetNext() {
    return next_;
  }
  void SetNext(BinomialTree<T>* next) {
    next_ = next;
  }

  // Get/Set previous binomial tree in the root list.
  const BinomialTree<T>* GetPrev() const {
    return prev_;
  }
  BinomialTree<T>* GetPrev() {
    return prev_;
  }
  void SetPrev(BinomialTree<T>* prev) {
    prev_ = prev;
  }

  // Get root node of current binomial tree.
  const BinomialTreeNode<T>* GetRootNode() const {
    return root_;
  }
  BinomialTreeNode<T>* GetRootNode() {
    return root_;
  }
  void SetRootNode(BinomialTreeNode<T>* root) {
    root_ = root;
  }

  bool IsEmpty() const {
    return (root_ == NULL);
  }

  // Get the degree of the root node of this binomial tree.
  // Degree of a node means the number of children it has.
  int GetDegree() const {
    assert(root_);
    return root_->degree;
  }

  const T& GetRootValue() const {
    assert(root_);
    return root_->value;
  }

  friend class BinomialHeap<T>;

 protected:
  // Post-order walking through the binomial sub-tree rooted at [root] to
  // destroy all of its nodes.
  void DestroyTree(BinomialTreeNode<T>* root) {
    if (root == NULL) return;

    // Destroy sub-tree rooted at [root]'s children.
    BinomialTreeNode<T>* child = root->child;
    BinomialTreeNode<T>* sib = NULL;
    while (child) {
      sib = child->sibling;
      DestroyTree(child);
      child = sib;
    }

    delete root;
  }

  // Root node of the binomial tree.
  BinomialTreeNode<T>* root_;

  // Previous/Next binomial tree in the root list.
  BinomialTree<T>* prev_;
  BinomialTree<T>* next_;

private:
  DISALLOW_COPY_AND_ASSIGN(BinomialTree);
};

}  // namespace thor

#endif  // THOR_BINOMIAL_TREE_H_