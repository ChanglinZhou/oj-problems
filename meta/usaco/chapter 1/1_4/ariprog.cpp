/*
ID: amble_s1
LANG: C++
TASK: ariprog
*/

#include <fstream>
#include <cassert>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

// The basic composite structure of the arithmetic progression sequence.
// <a, a + b, ..., a + nb>
typedef struct _arith_info{
  // First element in the sequence.
  int a;
  // Difference between consecutive elements.
  int b;
} arith_info;

// Compare functor
namespace std {

// Must be strict weak ordering.
template<>
struct less<arith_info> {
  bool operator()(const arith_info& left, const arith_info& right) {
    if (left.b == right.b) {
      return (left.a <= right.a);
    }

    return (left.b < right.b);
  }
};

}  // namespace std


typedef set<arith_info, less<arith_info> > ArithInfoSet;


// Generate all distinct bisquares which consist of p^2 + q^2, 0 <= p, q <= m.
vector<int> generate_bisquare_set(int m) {
  assert(m > 0);
  set<int> bisquareSet;

  // Assume that p <= q always to avoid generate duplicated elements.
  for (int p = 0; p <= m; ++p) {
    for (int q = p; q <= m; ++q) {
      bisquareSet.insert(p*p + q*q);
    }
  }

  // To speed up random-access, copy the elements from set to vector.
  vector<int> bisquareVector(bisquareSet.begin(), bisquareSet.end());
  return bisquareVector;
}

// Find all arithmetic progression sequence with given n in a bisquares set.
ArithInfoSet find_all_sequences(const vector<int>& bisquares, int n) {
  int maxElemnt = *max_element(bisquares.begin(), bisquares.end());
  ArithInfoSet arith_infos;

  // To speed up the searching element in a sequence, we use table look-up.
  vector<bool> bisquare_table(maxElemnt + 1, false);
  vector<int>::const_iterator it = bisquares.begin();
  while (it != bisquares.end()) {
    bisquare_table[*it] = true;
    ++it;
  }

  for (size_t i = 0; i < bisquares.size(); ++i) {
    for (size_t j = i + 1; j < bisquares.size(); ++j) {
      arith_info info;
      info.a = bisquares[i];
      info.b = bisquares[j] - bisquares[i];
      // Test whether the last element of arithmetic progression sequence
      // is exceed the maximum one in the set.
      if (info.a + info.b * (n - 1) > maxElemnt) break;

      int k;
      for (k = 1; k < n; ++k) {
        if (bisquare_table[info.a + k*info.b] == false)
          break;
      }
      if (k == n) {
        arith_infos.insert(info);
      }
    }
  }

  return arith_infos;
}

void print_infos(const ArithInfoSet& infos,
                 ofstream& outfile) {
  if (infos.empty()) {
    outfile << "NONE" << endl;
    return;
  }

  ArithInfoSet::const_iterator it = infos.begin();
  while (it != infos.end()) {
    outfile << it->a << " " << it->b << endl;
    ++it;
  }
}

int main() {
  // Open the input & output file object.
  ifstream infile("ariprog.in");
  ofstream outfile("ariprog.out");
  if (!infile || !outfile) return -1;

  int n, m;
  while (infile >> n >> m) {
    vector<int> bisquares = generate_bisquare_set(m);
    ArithInfoSet arith_infos = find_all_sequences(bisquares, n);
    print_infos(arith_infos, outfile);
  }
}