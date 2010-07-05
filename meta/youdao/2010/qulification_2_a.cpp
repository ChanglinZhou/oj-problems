#include <iostream>
#include <vector>
#include <string>

using namespace std;

char code_base[4] = { 'a', 'o', 'd', ' '};

string Encode(const string& raw_string) {
  string encoded_string(raw_string.size() * 4 + 1, '\0');

  for (int i = 0; i < raw_string.size(); ++i) {
    encoded_string += code_base[(raw_string[i] >> 6) & 0x03];
    encoded_string += code_base[(raw_string[i] >> 4) & 0x03];
    encoded_string += code_base[(raw_string[i] >> 2) & 0x03];
    encoded_string += code_base[raw_string[i] & 0x03];
  }

  return encoded_string;
}

int FindDao(const string& encoded_string) {
  int count = 0;

  for (int i = 0; i < encoded_string.size() - 2; ++i) {
    if (encoded_string[i] == 'd' &&
        encoded_string[i + 1] == 'a' &&
        encoded_string[i + 2] == 'o') {
      ++count;
      i += 2;
    }
  }

  return count;
}

int main() {

  int n;

  cin >> n;

  string raw_string;

  for (int i = 0; i < n; ++i) {
    cin >> raw_string;
    cout << FindDao(Encode(raw_string)) << endl;
  }

  return 0;
}
