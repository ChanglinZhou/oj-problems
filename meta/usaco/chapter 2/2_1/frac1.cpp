/*
ID: amble_s1
LANG: C++
TASK: frac1
*/

#include <fstream>
#include <cassert>
#include <cstring>
#include <algorithm>
#include <functional>
#include <set>

using namespace std;

// A fraction which consists of numerator and denominator(non-zero).
typedef struct _Fraction {
  _Fraction(int n, int d)
    : numerator(n), denominator(d) {}
  int numerator;
  int denominator;
} Fraction;

// Two boudary fraction between[0, 1]
const Fraction Zero(0, 1);
const Fraction One(1, 1);

// Functor used to add fraction into set container.
namespace std {

template<>
struct less<Fraction> {
  bool operator()(const Fraction& left, const Fraction& right) const {
    assert(left.denominator && right.denominator);

    double valueL = static_cast<double>(left.numerator);
    valueL /= left.denominator;

    double valueR = static_cast<double>(right.numerator);
    valueR /= right.denominator;

    return valueL < valueR;
  }
};

}  // namespace std

// Great common divisor.
int gcd(int a, int b) {
  assert(a >= 0 && b > 0);

  int r = a % b;
  while (r) {
    a = b;
    b = r;
    r = a % b;
  }

  return b;
}

// Generate reduced fraction.
Fraction reduced_fraction(int ntor, int dtor) {
  assert(dtor);

  int divisor = gcd(ntor, dtor);
  Fraction fraction(ntor / divisor, dtor / divisor);
  return fraction;
}

// Generate all reduced fractions which values are within [0, 1], 0/1, ..., 1/1.
// The denominator part of fraction should be never large than given number n,
// and the numerator should be less than denominator.
set<Fraction> generate_fractions(int n) {
  assert(n >= 1);

  set<Fraction> fractions;
  fractions.insert(Zero);
  fractions.insert(One);

  for (int j = 2; j <= n; ++j) {
    for (int i = 1; i < j; ++i) {
      fractions.insert(reduced_fraction(i, j));
    }
  }

  return fractions;
}

// Ostream operator << redirection for set<Fraction>.
ostream& operator << (ostream& out, const set<Fraction>& fractions) {
  for (set<Fraction>::const_iterator it = fractions.begin();
       it != fractions.end();
       ++it) {
    out << it->numerator << "/" << it->denominator << endl;
  }

  return out;
}

int main() {
  ifstream infile("frac1.in");
  ofstream outfile("frac1.out");
  if (!infile || !outfile) return -1;

  int n;
  while (infile >> n) {
    set<Fraction> fractions = generate_fractions(n);
    outfile << fractions;
  }

  return 0;
}