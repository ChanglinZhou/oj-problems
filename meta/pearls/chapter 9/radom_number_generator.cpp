/* Copyright (C) 1999 Lucent Technologies
 * Author: Jon Bentley
 * Purpose: Generate random numbers with different policies.
 * Modified by: Su Shi(carmack.shi@gmail.com)
*/

#include <cstdlib>
#include <cstdio>
#include <cstddef>
#include <cassert>
using namespace std;

// If NODESIZE is 8, this program uses the special-case malloc.
// Change NODESIZE to 0 to use the system malloc.
const int kBlockSize = 0;
const int kBlockGroup = 1000;

union Block {
  Block* next;
  char data_trunk[kBlockSize];
};

Block* free_block_head = NULL;

void* PoolMalloc(size_t size) {
  void* p = NULL;

  if (size != kBlockSize)
    return malloc(size);

  if (free_block_head == NULL) {
    free_block_head = static_cast<Block*>(malloc(kBlockGroup*kBlockSize));

    if (free_block_head) {
      for (size_t i = 0; i < kBlockGroup - 1; ++i) {
        free_block_head[i].next = free_block_head + i + 1;
      }
      free_block_head[kBlockGroup - 1].next = NULL;
    }
  }

  if (free_block_head) {
    p = free_block_head;
    free_block_head = free_block_head->next;
  }

  return p;
}

void PoolFree(void* memory, size_t size = kBlockSize) {
  if (size != kBlockSize)
    return free(memory);

  Block* block = static_cast<Block*>(memory);
  block->next = free_block_head;
  free_block_head = block;
}


int BigRand() {
  return RAND_MAX*rand() + rand();
}


class IntSetBins {
 public:
  IntSetBins(size_t max_elements_number, size_t max_value)
    : elements_number_(0), 
      bins_number_(max_elements_number),
      max_value_(max_value) {
    bins_ = static_cast<Node**>(PoolMalloc(bins_number_*sizeof(Node*)));
    sentinel_ = static_cast<Node*>(PoolMalloc(sizeof(Node)));
    sentinel_->value_ = max_value_;
    sentinel_->next_ = NULL;
    for (size_t i = 0; i < bins_number_; ++i)
      bins_[i] = sentinel_;
  }
  ~IntSetBins() {
    for (size_t i = 0; i < bins_number_; ++i)
      for (Node* node = bins_[i]; node != sentinel_; node = node->next_)
        PoolFree(node);

    PoolFree(bins_);
    PoolFree(sentinel_);
  }

  void Insert(size_t value) {
    int hash_index = value / (1 + max_value_ / bins_number_);
    //bins_[hash_index] = RecursiveSubInsert(bins_[hash_index], value);
    bins_[hash_index] = NonRecursiveSubInsert(bins_[hash_index], value);
  }

  void Report() {
    for (size_t i = 0; i < bins_number_; ++i)
      for (Node* node = bins_[i]; node != sentinel_; node = node->next_)
        /*printf("%d\n", node->value_)*/;
  }

  size_t size() const {
    return elements_number_;
  }

 private:
  struct Node {
    size_t value_;
    Node *next_;
  };

  Node* RecursiveSubInsert(Node* root, size_t value) {
    assert(root);

    if (root->value_ < value) {
      root->next_ = RecursiveSubInsert(root->next_, value);
    } else if (root->value_ > value) {
      Node* new_node = static_cast<Node*>(PoolMalloc(sizeof(Node)));
      new_node->value_ = value;
      new_node->next_ = root;
      root = new_node;
      ++elements_number_;
    }

    return root;
  }

  Node* NonRecursiveSubInsert(Node* root, size_t value) {
    assert(root);

    Node *prev = NULL, *current = root;
    while (current->value_ < value) {
      prev = current;
      current = current->next_;
    }

    if (current->value_ > value) {
      Node* new_node = static_cast<Node*>(PoolMalloc(sizeof(Node)));
      new_node->value_ = value;
      new_node->next_ = current;
      if (prev)
        prev->next_ = new_node;
      else
        root = new_node;
      ++elements_number_;
    }

    return root;
  }

  size_t elements_number_;
  size_t bins_number_;
  size_t max_value_;
  Node** bins_;
  Node* sentinel_;
};


int main(int argc, char *argv[]) {
  size_t max_elements = 10000;
  size_t max_value = 1000000;

  if (argc >= 3) {
    max_elements = atoi(argv[1]);
    max_value = atoi(argv[2]);
  }

  // Integer set with bins.
  IntSetBins int_set_bins(max_elements, max_value);
  while (int_set_bins.size() < max_elements) {
    int_set_bins.Insert(BigRand() % max_value);
  }
  int_set_bins.Report();

  return 0;
}