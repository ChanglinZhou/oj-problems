#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
  int t, x, s, n, m;
  string name;

  cin >> t;

  for (int i = 0; i < t; ++i) {
    cin >> x >> s;
    map<string, int> user_data;
    for (int j = 0; j < s; ++j) {
      cin >> n >> m;
      int repay = m > (n * x) ? (n * x) : m;
      for (int k = 0; k < n; ++k)
        cin >> name;

      cin >> name;

      if (user_data.find(name) == user_data.end())
        user_data[name] = 0;
      user_data[name] += repay;
    }

    for (map<string, int>::const_iterator it = user_data.begin();
         it != user_data.end(); ++it) {
      cout << it->first << " " << it->second << endl;
    }

    cout << endl;
  }
  return 0;
}
