/*
ID: amble_s1
LANG: C++
TASK: sprime
*/

#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <exception>

using namespace std;

vector<bool> GeneratePrimeTable(size_t size) {
  if (size == 0)
    throw new exception;

  vector<bool> prime_table(size, true);

  // 0, 1 are not prime by default.
  prime_table[0] = false;
  if (size > 1)
    prime_table[1] = false;

  // Even numbers are not prime by default
  for (size_t k = 4; k < size - 1; k += 2)
    prime_table[k] = false;

  for (size_t i = 3; i <= size - 1; i += 2) {
    if (!prime_table[i]) continue;

    for (size_t j = i; j * i < size ; j += 2)
      prime_table[j * i] = false;
  }

  return prime_table;
}

// Since the possible super primes are consisting of:
// [2, 3, 5, 7][1, 3, 7, 9]*
// So the number of them are 4^n, each of which take at most 10^[(n + 1)/2]/2
// times modular calculation.
// For this problem, the maximum value of n is 8, which means we need at most
// 5,000 times modular to judge whether is a prime for 8-digits number.
// The total modular for all 4^8 numbers is about 320 M, which is acceptable
// for modern computer. So we here use traditional method instead of table
// look-up way.
bool IsPrime(size_t number) {
  // 0, 1 are not primes.
  if (number <= 1) return false;

  // 2 is only number which is both prime and even.
  if (number == 2) return true;

  // Other even numbers aren't primes.
  if (number % 2 == 0) return false;

  bool prime = true;
  for (size_t i = 3; i * i <= number; i += 2)
    if (number % i == 0) {
      prime = false;
      break;
    }

  return prime;
}

vector<size_t> GenerateSuperPrime(size_t n) {
  if (n == 0)
    throw new exception;

  vector<size_t> sprimes;

  if (n == 1) {
    sprimes.reserve(4);
    sprimes.push_back(2);
    sprimes.push_back(3);
    sprimes.push_back(5);
    sprimes.push_back(7);

    return sprimes;
  }

  // Find the sub super prime with n - 1 digits length.
  sprimes = GenerateSuperPrime(n - 1);

  // Combine with the nth digit on the righ most position.
  size_t digits[] = { 1, 3, 7, 9 };
  size_t base_size = sprimes.size();
  sprimes.reserve(sizeof(digits) / sizeof(size_t) * base_size);
  for (size_t d = 0; d < sizeof(digits) / sizeof(size_t); ++d) {
    for (size_t i = 0; i < base_size; ++i) {
      if (d == 0) {
        sprimes[i] = sprimes[i] * 10 + digits[d];
      } else {
        sprimes.push_back(sprimes[i] + digits[d] - digits[0]);
      }
    }
  }

  // Remove non-primes
  for (size_t j = sprimes.size() - 1; (j + 1) >= 1; --j) {
    if (!IsPrime(sprimes[j]))
      sprimes.erase(sprimes.begin() + j);
  }

  return sprimes;
}

int main() {
  ifstream infile("sprime.in");
  ofstream outfile("sprime.out");
  if (!infile || !outfile) return -1;

  size_t n;
  while (infile >> n) {
    vector<size_t> sprimes = GenerateSuperPrime(n);
    sort(sprimes.begin(), sprimes.end());
    for (size_t i = 0; i < sprimes.size(); ++i)
      outfile << sprimes[i] << endl;
  }

  return 0;
}
