
#include <iostream>
#include <cassert>
#include <string>
#include <set>
#include <map>
using namespace std;

// Node element in the disjoint set's tree representation.
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

template<>
struct less<Node> {
  bool operator()(const Node& left, const Node& right) const{
    return left.key < right.key;
  }
};

// Set used to store elements from disjoint sets.
set<Node> NodeSet;

// Describe the satellite data for each digit in the sequence.
class DigitSatellite {
public:
  DigitSatellite()
    : same(-1), opposite(-1) { }
  DigitSatellite(int same_, int opposite_)
    : same(same_), opposite(opposite_) { }
  // Stores the representive of disjoint set for ith node, which has same parity
  // as it.
  int same;
  // Stores the index to the representive of disjoint set for ith node,
  // which has opposite parity as it.
  int opposite;
};


// Make a disjoint set which only contain one element.
void MakeSet(int key) {
  Node node(key);
  NodeSet.insert(node);
}

// Recursion-based find representive of the set which contains [key] node.
int FindSet(int key) {
  if (key == -1) return key;

  set<Node>::iterator it = NodeSet.find(key);
  Node& node = *it;

  // End of recursion.
  if (node.parent == key) return key;

  // Find representive element key from its parent.
  return (node.parent = FindSet(node.parent));
}

// Unoin two disjoint sets.
int UnionSet(int keyX, int keyY) {
  if (keyX == -1) return FindSet(keyY);
  
  if (keyY == -1) return FindSet(keyX);

  int repX = FindSet(keyX);
  int repY = FindSet(keyY);

  // Avoid union two same sets.
  if (repX == repY) return repX;

  Node& nodeX = *NodeSet.find(repX);
  Node& nodeY = *NodeSet.find(repY);

  int rep = -1;
  if (nodeX.rank > nodeY.rank) {
    nodeY.parent = nodeX.key;
    rep = repX;
  } else {
    nodeX.parent = nodeY.key;
    if (nodeX.rank == nodeY.rank) ++nodeY.rank;
    rep = repY;
  }

  return rep;
}

// <DigitPosition, Representive of Opposite Parity Set>.
map<int, int> OppositeCache;

// <DigitPosition, Satellite Data>
map<int, DigitSatellite> SequenceData;

int main() {
  int n, p;
  int a, b;
  string answer;

  cin >> n >> p;

  int repI = -1, repJ = -1, j;
  for (j = 0; j < p; ++j) {
    cin >> a >> b >> answer;
    // Find whether (a-1)th and bth digit are in the SequenceData.
    if (SequenceData.find(a - 1) == SequenceData.end()) {
      MakeSet(a - 1);
      OppositeCache[a - 1] = -1;
      SequenceData[a - 1] = DigitSatellite(a - 1, a - 1);
    }
    if (SequenceData.find(b) == SequenceData.end()) {
      MakeSet(b);
      OppositeCache[b] = -1;
      SequenceData[b] = DigitSatellite(b, b);
    }

    // Index of the opposite set cache for (a-1)th digit.
    int oppIndexI = SequenceData[a - 1].opposite;
    // Index of the opposite set cache for bth digit.
    int oppIndexJ = SequenceData[b].opposite;

    // sequence[1...a - 1] has the same parity as sequence[1...b], union their
    // same and opposite.
    if (answer == "even") {
      // Merge (a-1)th digit's same parity set with bth's.
      repI = UnionSet(SequenceData[a - 1].same, SequenceData[b].same);
      SequenceData[a - 1].same = SequenceData[b].same = repI;

      // Merge two empty opposite sets.
      if (OppositeCache[oppIndexI] == -1 && OppositeCache[oppIndexJ] == -1) {
        SequenceData[a - 1].opposite = oppIndexI = oppIndexJ;
      }

      // Merge (a-1)th digit's opposite parity set with bth's.
      repJ = UnionSet(OppositeCache[oppIndexI], OppositeCache[oppIndexJ]);
      OppositeCache[oppIndexI] = OppositeCache[oppIndexJ] = repJ;

      // Check conflict after merging.
      if (repI == repJ) break;
    } else {  // Odd
      // Merge (a-1)th digit's same parity set with bth's opposite set.
      repI = UnionSet(SequenceData[a - 1].same, OppositeCache[oppIndexJ]);
      SequenceData[a - 1].same = OppositeCache[oppIndexJ] = repI;

      // Merge bth digit's same parity set with (a-1)th's opposite set.
      repJ = UnionSet(SequenceData[b].same, OppositeCache[oppIndexI]);
      SequenceData[b].same = OppositeCache[oppIndexI] = repJ;

      if (repI == repJ) break;
    }
  }

  cout << j << endl;

  return 0;
}
