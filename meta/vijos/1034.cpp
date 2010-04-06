/*
 * System: VIJOS
 * Problem: Familly(1034)
 * Algorithm: Disjoint-Set
 *
 */

#include <iostream>
using namespace std;

const int MAX_NODE_NUMBER = 5000;

class Node {
public:
  Node()
    : key(0), parent(0), rank(0) { }
  Node(int key_)
    : key(key_), parent(key), rank(0) { }
  int key;
  int parent;
  int rank;
};

Node NodeBuffer[MAX_NODE_NUMBER + 1];

void MakeSet(int key) {
  Node& node = NodeBuffer[key];
  node.key = key;
  node.parent = key;
  node.rank = 0;
}

// Recursion-based.
int FindSet(int key) {
  Node& node = NodeBuffer[key];

  // End of recursion.
  if (node.parent == key) return key;

  // Find representive element key from its parent.
  return (node.parent = FindSet(node.parent));
}

//// Non-recursion optimized.
//int FindSet(int x) {
//  int px = x;
//
//  // Go up toward root to get representive.
//  while (NodeBuffer[px].parent != px) {
//    px = NodeBuffer[px].parent;
//  }
//
//  // Go down toward x to set its parent to the representive of the set.
//  int tmp;
//  while (px != x) {
//    tmp = NodeBuffer[x].parent;
//    NodeBuffer[x].parent = px;
//    x = tmp;
//  }
//
//  return px;
//}

void UnionSet(int keyX, int keyY) {
  int repX = FindSet(keyX);
  int repY = FindSet(keyY);

  // Avoid union two same sets.
  if (repX == repY) return;

  Node& nodeX = NodeBuffer[repX];
  Node& nodeY = NodeBuffer[repY];

  if (nodeX.rank > nodeY.rank) {
    nodeY.parent = nodeX.key;
  } else {
    nodeX.parent = nodeY.key;
    if (nodeX.rank == nodeY.rank) ++nodeY.rank;
  }
}

int main() {

  int n, m, p, a, b;

  cin >> n >> m >> p;

  // Make n independent disjoint set.
  for (int i = 1; i <= n; ++i) {
    MakeSet(i);
  }

  // Union two elements' sets if they're disjoint.
  for (int j = 0; j < m; ++j) {
    cin >> a >> b;
    UnionSet(a, b);
  }

  // Judge whether two elements are from the same set.
  for (int k = 0; k < p; ++k) {
    cin >> a >> b;
    int repA = FindSet(a);
    int repB = FindSet(b);
    if (repA == repB) cout << "Yes" << endl;
    else cout << "No" << endl;
  }

  return 0;
}