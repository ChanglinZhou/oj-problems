// Copyright (c) 2010, Su Shi <carmack.shi [at] gmail.com>
//
// Problem:
// Consider a function which, for a given whole number n, returns the number of
// ones required when writing out all numbers between 0 and n.
// For example, f(13)=6. Notice that f(1)=1.
// What is the next largest n such that f(n)=n?
//
// Algorithm:
// Memoized computation + Divide-and-Conqure.
//
// All rights reserved.

#ifndef THOR_MISC_H_
#define THOR_MISC_H_

#include <algorithm>
#include <iostream>
#include <cassert>
#include <ctime>
#include <limits>

// Maximum size of digits of 32-bits integer number.
const int MAX_NUMBER_SIZE = 10;

// Base value for each digit of 32 bits integer number from low to high.
// [0, 9]
const int BaseTable[MAX_NUMBER_SIZE] = { 1, 10, 100, 1000, 10000, 100000,
                                         1000000, 10000000, 100000000,
                                         1000000000 };

// Cache size which stands for the maximum number of memoized values.
// [0, 100,000)
const int SECTION_SIZE = 100000;

// Cachese the total population count of '1' digits occur in each decimal number
// from [0, SECTION_SIZE).
char PopulationTable[SECTION_SIZE];

// Cleanup the cache.
void Cleanup() {
  std::fill(PopulationTable, PopulationTable + SECTION_SIZE, -1);
}

// Use divide-and-conqure method to find the range which satisfy the condition:
// BaseTable[high] <= number < BaseTable[low]
int GetNumberLength(int number) {
  if (number <= 0) return 0;

  // Use binary search to find the range.
  int low = 0, high = MAX_NUMBER_SIZE - 1;
  while (low <= high) {
    int mid = (low + high) / 2;
    if (number < BaseTable[mid])
      high = mid - 1;
    else
      low = mid + 1;
  }

  return low;
}

// Get the population count of '1' digits in the given decimal number.
int GetPopulationCount(int number) {
  if (number <= 0) return 0;

  // Reads from cache firstly.
  if (number < SECTION_SIZE && PopulationTable[number] >= 0)
    return PopulationTable[number];

  int number_length = GetNumberLength(number);

  // For number belongs to [1, 9], calculate population directly and store
  // it in the cache.
  if (number_length == 1)
    return (PopulationTable[number] = (number == 1));

  // Divde-and-Conqure strategy:
  // Split the given number into two parts: high & low.
  // Since the splited two parts are smaller number, which might use cache
  // directly to fetch result instead of re-calculating.
  int low_length = number_length / 2;
  int divisor = (BaseTable[low_length]);
  int low_part = number % divisor;
  int high_part = number / divisor;
  int population_count = GetPopulationCount(low_part) +
                         GetPopulationCount(high_part);

  // Cache reult if necessary.
  if (number < SECTION_SIZE)
    PopulationTable[number] = population_count;

  return population_count;
}

// Prints all the numbers belongs to range [0, max_number] which satisfy the
// condition:
// F(n) = n
void PrintFixedNumber(int max_number) {
  // Memoized computation which can avoid duplicated calculations.
  // Induction:
  // F(n) = F(n - 1) + GetPopulationCount(n)
  for (int number = 2, population_count = 1;
       0 <= number && number <= max_number; ++number) {
    population_count += GetPopulationCount(number);
    if (population_count == number)
      std::cout << "f(" << number << ") = " << number << std::endl;
  }
}

// Gets the sum of population count for each decimal number in the given range.
// [first, last)
int GetPopulationCountInRange(int first, int last) {
  if (first >= last) return 0;

  int total_population_count = 0;
  for (int number = first; number < last; ++number) {
    total_population_count += GetPopulationCount(number);
  }

  return total_population_count;
}


////////////////////////////////////////////////////////////////////////////////
// Microsoft's fucking algorithm
typedef long long LONGLONG;
typedef unsigned long long ULONGLONG;
LONGLONG Sum1s(ULONGLONG n) {
  ULONGLONG iCount = 0;
  ULONGLONG iFactor = 1;

  ULONGLONG iLowerNum = 0;
  ULONGLONG iCurrNum = 0;
  ULONGLONG iHigherNum = 0;

  while (n / iFactor != 0) {
    iLowerNum = n - (n / iFactor) * iFactor;
    iCurrNum = (n / iFactor) % 10;
    iHigherNum = n / (iFactor * 10);

    switch(iCurrNum) {
      case 0:
        iCount += iHigherNum * iFactor;
        break;

      case 1:
        iCount += iHigherNum * iFactor + iLowerNum + 1;
        break;

      default:
        iCount += (iHigherNum + 1)* iFactor;
        break;
    }

    iFactor *= 10;
  }

  return iCount;
}
////////////////////////////////////////////////////////////////////////////////


#endif  // THOR_MISC_H_