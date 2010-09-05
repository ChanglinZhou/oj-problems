#include <iostream>

using namespace std;

int NumberOfFillings(int h, int w) {
  if (h == 0 || w == 0)
    return 1;

  if ((h * w) % 2 == 1)
    return 0;

  if (h == 1 || w == 1)
    return 1;

  return NumberOfFillings(h - 1, w - 2) * NumberOfFillings(h - 1, 2) +
         NumberOfFillings(h - 2, w - 1) * NumberOfFillings(2, w - 1);
};

int main() {

  int h, w;
  while (cin >> h >> w) {
    if (h == 0 && w == 0)
      break;

    cout << NumberOfFillings(h, w) << endl;
  }

  return 0;

}