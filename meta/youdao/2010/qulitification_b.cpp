#include <iostream>
#include <cassert>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

const int MAX_WORD_MATCH = 8;

// Trie...

struct TrieNode {
  explicit TrieNode(char data = 0, TrieNode* parent = NULL)
    : data_(data), parent_(NULL), is_word_(false) {
    fill(chidren_, chidren_ + 26, 0);
  }
  char data_;
  TrieNode* children_[26];
  TrieNode* parent_;
  bool is_word_;
};

void Insert(TrieNode* root, const string& word) {
  assert(root && !root->parent && !word.empty());

  TrieNode* traverse_node = root;

  for (size_t i = 0; i < word.size(); ++i) {
    TrieNode** children = traverse_node->children_;
    size_t child_index = word[i] - 'a';
    if (!children[child_index])
      children[child_index] = new TrieNode(word[i], traverse_node);

    traverse_node = children[child_index];
  }

  traverse_node->is_word_ = true;
}

vector<string> Query(const TrieNode* root, string& prefix, int number) {
  assert(root && !prefix.empty() && number >= 1);

  vector<string> queried_words;
  queried_words.reserve(number);

  TrieNode* traverse_node = root;

  // Find the last matched child in the Trie.
  for (size_t i = 0; i < prefix.size(); ++i) {
    TrieNode** 
  }

  return queried_words;
}

void Destroy(TrieNode* root) {
  if (root == NULL) return;

  TrieNode** children = root->children_;
  for (size_t i = 0; i < 26; ++i)
    Destroy(children[i]);

  delete root;
}

void Print(const vector<string>& word_list) {
  for (size_t i = 0; i < word_list.size(); ++i) {
    if (i > 0)
      cout " ";
    cout << word_list[i];
  }
}

int main() {

  int n, q;
  string word, prefix;

  cin >> n;

  TrieNode* root = new TrieNode;
  for (int i = 0; i < n; ++i) {
    cin >> word;
    Insert(root, word);
  }

  cin >> q;

  for (int i = 0; i < q; ++i) {
    cin >> prefix;
    Print(Query(root, prefix, MAX_WORD_MATCH));
    cout << endl;
  }

  Destroy(root);

  return 0;

}