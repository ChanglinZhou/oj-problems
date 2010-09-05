#include <iostream>
#include <string>

using namespace std;

// Problem #2103 from www.careercup.com

void PrintBrackets(const string& brackets) {
  for (string::const_iterator it = brackets.begin();
       it != brackets.end(); ++it) {
    cout << *it;
  }

  cout << endl;
};

void GenerateCombination(int left, int right, string& brackets) {
  if (left > right || left < 0 || right < 0)
    return;

  if (left == 0 && right == 0)
    return PrintBrackets(brackets);

  brackets.push_back('(');
  GenerateCombination(left - 1, right, brackets);
  brackets.erase(brackets.size() - 1, string::npos);

  brackets.push_back(')');
  GenerateCombination(left, right - 1, brackets);
  brackets.erase(brackets.size() - 1, string::npos);
}

int main() {
  string brackets;
  GenerateCombination(3, 3, brackets);
  return 0;
}