/*
ID: amble_s1
LANG: C++
TASK: pprime
*/

#include <cstdio>
#include <fstream>
#include <cassert>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

// The maximum length of number is 9 digits.
const int MAX_NUMBER_LEN = 9;

typedef struct _Range {
  size_t a;
  size_t b;
} Range;

size_t POW(size_t a, size_t b) {
  size_t value = 1;
  for (size_t i = 0; i < b; ++i)
    value *= a;

  return value;
}


vector<int> generate_palindromes(size_t n, size_t low_pos,
                                 size_t digit_length,
                                 const Range& range) {
  size_t middle = (digit_length - 1) / 2;
  vector<int> palindromes;

  // End of recursive
  if (low_pos > middle) {
    if (range.a <= n && n <= range.b)
      palindromes.push_back(n);
    return palindromes;
  }

  size_t high_pos = (digit_length - 1) - low_pos;
  size_t start = (low_pos == 0);
  size_t end = 10;
  size_t step = start + 1;

  // Using DFS to generate all palindromes for different digits.
  // Since we generate the palindromes from highest digit to the middle digit,
  // and use smallest digit to largest digit, so the final palindromes is sorted
  // ascending.
  for (size_t d = start; d < end; d += step) {
    int new_n = n + d * POW(10, low_pos);
    if (low_pos < high_pos)
      new_n += d * POW(10, high_pos);
    vector<int> new_palindromes = generate_palindromes(new_n, low_pos + 1,
                                                       digit_length, range);
    palindromes.insert(palindromes.end(), new_palindromes.begin(),
                       new_palindromes.end());
  }

  return palindromes;
}

vector<int> find_palindromes(const Range& range) {
  char digitsA[MAX_NUMBER_LEN + 1] = { 0 };
  char digitsB[MAX_NUMBER_LEN + 1] = { 0 };
  sprintf(digitsA, "%d", range.a);
  sprintf(digitsB, "%d", range.b);

  vector<int> palindromes;
  size_t lenA = strlen(digitsA);
  size_t lenB = strlen(digitsB);
  size_t minLen = min(lenA, lenB);
  size_t maxLen = max(lenA, lenB);

  for (size_t l = minLen; l <= maxLen; ++l) {
    vector<int> new_palindromes = generate_palindromes(0, 0, l, range);
    palindromes.insert(palindromes.end(), new_palindromes.begin(),
                       new_palindromes.end());
  }

  return palindromes;
}

bool isPrime(size_t a) {
  // 0, 1 is not prime.
  if (a <= 1) return false;

  // 2 is the only prime in even numbers.
  if (a == 2) return true;

  bool prime = true;
  for (size_t i = 3; i * i <= a; i += 2) {
    if (a % i == 0) {
      prime = false;
      break;
    }
  }

  return prime;
}

vector<int> find_pprimes(size_t a, size_t b) {
  Range range;
  range.a = a;
  range.b = b;
  vector<int> palindromes = find_palindromes(range);

  // Remove non-primes.
  for (size_t i = palindromes.size() - 1; (i + 1) >= 1; --i) {
    if (!isPrime(palindromes[i]))
      palindromes.erase(palindromes.begin() + i);
  }

  sort(palindromes.begin(), palindromes.end());
  return palindromes;
}

int main() {
  ifstream infile("pprime.in");
  ofstream outfile("pprime.out");
  if (!infile || !outfile) return -1;

  size_t a, b;
  while (infile >> a >> b) {
    vector<int> pprimes = find_pprimes(a, b);
    for (size_t i = 0; i < pprimes.size(); ++i) {
      outfile << pprimes[i] << endl;
    }
  }

  return 0;
}