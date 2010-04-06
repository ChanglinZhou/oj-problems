// Copyright (c) 2010, Su Shi <carmack.shi [at] gmail.com>
//
// All rights reserved.

#ifndef THOR_BINOMIAL_HEAP_H_
#define THOR_BINOMIAL_HEAP_H_

#include <cassert>
#include <algorithm>

#include "thor_basic_types.h"
#include "thor_binomial_tree.h"


namespace thor {

template <typename T>
class BinomialHeap {
 public:
  BinomialHeap()
    : head_(NULL) { }
  BinomialHeap(BinomialTree<T>* head)
    : head_(head) { }
  ~BinomialHeap() {
    DestroyHeap();
  }

  void IsEmpty() const {
    // If there's tree in the heap, it must be not empty.
    return (head_ == NULL);
  }

  void Insert(const T& value) {
    BinomialTreeNode<T>* new_node = new BinomialTreeNode<T>(value);
    BinomialTree<T>* new_tree = new BinomialTree<T>(new_node);

    new_tree->next_ = head_;
    head_ = new_tree;
    Solidate();
  }

  const T& Minimum() const {
    BinomialTree<T>* min_tree = GetMinimumTree();
    return min_tree->GetRootValue();
  }

  void ExtractMinimum() {
    BinomialTree<T>* min_tree = GetMinimumTree();

    delete ExtractRootNode(min_tree);
  }

  static BinomialHeap<T>* Union(BinomialHeap<T>* heap_x,
                                BinomialHeap<T>* heap_y) {
    assert(heap_x && heap_y);

    BinomialHeap<T>* unioned_heap = Merge(heap_x, heap_y);

    if (unioned_heap == NULL || unioned_heap->head_ == NULL)
      return unioned_heap;

    unioned_heap->Solidate();

    return unioned_heap;
  }

  void DecreaseKey(BinomialTreeNode<T>* node, const T& key) {
    assert(node && key <= node->value);
    node->value = key;
    BubbleUp(node, true);
  }

  void Delete(BinomialTreeNode<T>* node) {
    BubbleUp(node);

    //ExtractRootNode();
  }

 protected:
  // Destroys each binomial tree in the root list from least degree to greatest
  // one.
  void DestroyHeap() {
    BinomialTree<T>* next = NULL;
    while (head_) {
      next = head_->next_;
      delete head_;
      head_ = next;
    }
  }

  // Solidate the structure of the heap according to definition of binomial
  // heap.
  // The only violation is that there're at most two binomial trees has same
  // degree.
  void Solidate() {
    BinomialTree<T>* prev = NULL;
    BinomialTree<T>* current = head_;
    BinomialTree<T>* next = current ? current->next_ : NULL;

    // See BINOMIAL_HEAP_UNION(H1, H2) in 19.2<Operations on binomial heaps>,
    // CLRS 2nd Edition.
    while (next) {
      // Case 1:
      //   Current binomial tree has different degree with its imediate right
      //   sibling.
      // Case 2:
      //   There three continuous binomial trees whose degree are all the same.
      if ((current->GetDegree() != next->GetDegree()) ||
          (next->next_ && next->GetDegree() == next->next_->GetDegree())) {
        prev = current;
        current = next;
      } else {
        // Case 3:
        //   Root value of current tree is less or equal than its imediate
        //   right sibling. Links [next] to [current] as its left-most child.
        if (current->GetRootValue() <= next->GetRootValue()) {
          // Cut [next] off from root list.
          current->next_ = next->next_;
          Link(next, current);
          // Tree pointed by next is empty, we should delete it since empty
          // tree is not allowed in binomial heap.
          delete next;
        } else {
          // Cut [current] off from root list.
          if (prev == NULL) {
            head_ = next;
          }
          else {
            prev->next_ = next;
          }
          Link(current, next);
          // Same as above reason.
          delete current;
          current = next;
        }
      }

      next = current->next_;
    }
  }

  // Gets the binomial tree whose root value is the minimum in the whole heap.
  BinomialTree<T>* GetMinimumTree() const {
    assert(head_);

    BinomialTree<T>* min_tree = NULL;
    BinomialTree<T>* current_tree = head_;
    while (current_tree) {
      if (min_tree == NULL ||
          current_tree->GetRootValue() < min_tree->GetRootValue()) {
        min_tree = current_tree;
      }
      current_tree = current_tree->next_;
    }

    return min_tree;
  }

  // Gets the root list.
  BinomialTree<T>* GetForest() const {
    return head_;
  }
  void SetForest(BinomialTree<T>* head) {
    head_ = head;
  }

  void BubbleUp(BinomialTreeNode<T>* node, bool compare = false) {
    assert(node);

    BinomialTreeNode<T>* current = node;
    BinomialTreeNode<T>* parent = node->parent;

    // Bubbling up the given node in the heap.
    // If [compare] = true, we should stop bubbling up if current node is not
    // less than its parent node.
    while (parent &&
           (current->value < parent->value || !compare)) {
      // swap with its parent's key
      std::swap(current->value, parent->value);
      current = parent;
      parent = current->parent;
    }
  }

  BinomialTreeNode<T>* ExtractRootNode(BinomialTree<T>* tree) {

    assert(tree && tree->root_);

    // Remove the given tree from the root list in the heap.
    if (tree->prev_)
      tree->prev_->next_ = tree->next_;
    else
      head_ = tree->next_;
    if (tree->next_)
      tree->next_->prev_ = tree->prev_;

    // Take the ownership of the internal nodes, and delete this empty tree.
    BinomialTreeNode<T>* root = tree->root_;
    tree->root_ = NULL;
    delete tree;

    // Get the head of root node's children list, and destroy
    BinomialTreeNode<T>* child = root->child;

    // Reverse min_root's children list in order to satisfy the binomial heap's
    // property, that is degrees of trees are sorted in ascending order.
    BinomialTree<T>* children_head = NULL;
    BinomialTreeNode<T>* next = NULL;
    while (child) {
      // Cut the child from its destroyed parent, and its right sibling.
      child->parent = NULL;
      next = child->sibling;
      child->sibling = NULL;

      BinomialTree<T>* tree = new BinomialTree<T>(child);

      // Add a new binomial tree into the heap.
      tree->next_ = children_head;
      if (children_head)
        children_head->prev_ = tree;
      children_head = tree;

      child = next;
    }

    // Construt a new heap which contains the children list, and union it with
    // current heap.
    if (children_head) {
      BinomialHeap<T>* children_heap = new BinomialHeap<T>(children_head);
      BinomialHeap<T>* unioned_heap = Union(this, children_heap);
      delete children_heap;

      head_ = unioned_heap->head_;
      unioned_heap->head_ = NULL;
      delete unioned_heap;
    }

    return root;
  }

  // Links other binomial tree whose to this one to construct a new binomial
  // tree
  // Pre-condition
  //  a. Non-empty tree.
  //  b. Same degree.
  //  c. value[root[tree_x]] >= value[root[tree_y]]
  static void Link(BinomialTree<T>* tree_x, BinomialTree<T>* tree_y) {
    assert(tree_x && tree_y &&
           !tree_x->IsEmpty() && !tree_y->IsEmpty());

    assert(tree_x->GetDegree() == tree_y->GetDegree());

    assert(tree_x->GetRootNode()->value >= tree_y->GetRootNode()->value);

    // Transfer out the ownership of nodes inside tree_x.
    BinomialTreeNode<T>* root_x = tree_x->GetRootNode();
    tree_x->SetRootNode(NULL);

    BinomialTreeNode<T>* root_y = tree_y->GetRootNode();
    root_x->parent = root_y;
    root_x->sibling = root_y->child;
    root_y->child = root_x;
    ++(root_y->degree);
  }

  // Merges the internal root lists of two given binomial heaps into a new one,
  // which is sorted by root node's degree of binomial tree monotonically.
  // We put the merged root list in a returned BinomialHeap<T> object.
  // Take acount of NRV optimization, the list won't be destroyed in dtor.
  static BinomialHeap<T>* Merge(BinomialHeap<T>* heap_x,
                                BinomialHeap<T>* heap_y) {
    assert(heap_x && heap_y);

    BinomialTree<T>* tree_x = heap_x->head_;
    heap_x->head_ = NULL;

    BinomialTree<T>* tree_y = heap_y->head_;
    heap_y->head_ = NULL;

    BinomialTree<T>* merged_trees_head = NULL;
    BinomialTree<T>* merged_trees_tail = NULL;

    while (tree_x && tree_y) {
      BinomialTree<T>* merged_tree = NULL;
      if (tree_x->root_->degree < tree_y->root_->degree) {
        merged_tree = tree_x;
        tree_x = tree_x->next_;
      } else {
        merged_tree = tree_y;
        tree_y = tree_y->next_;
      }

      // Links the chosen tree to the tail of the root list.
      merged_tree->prev_ = merged_trees_tail;
      merged_tree->next_ = NULL;
      merged_trees_tail = merged_tree;

      // If it's the first time to enter the loop to merge tree into a new
      // root list, we should record the head.
      if (merged_trees_head == NULL) {
        merged_trees_head = merged_trees_tail;
      }
    }

    BinomialTree<T>* left_tree_list = NULL;
    if (tree_x)
      left_tree_list = tree_x;
    else  // Must be tree_y or NULL
      left_tree_list = tree_y;

    if (left_tree_list) {
      if (merged_trees_head == NULL) {
        merged_trees_head = merged_trees_tail = left_tree_list;
      }
      else {
        merged_trees_tail->next_ = left_tree_list;
        left_tree_list->prev_ = merged_trees_tail;
      }
    }

    return new BinomialHeap<T>(merged_trees_head);
  }

 private:
  // Head of the binomial tree list inside heap.
  BinomialTree<T>* head_;

  DISALLOW_COPY_AND_ASSIGN(BinomialHeap);
};

}  // namespace thor

#endif  // THOR_BINOMIAL_HEAP_H_
