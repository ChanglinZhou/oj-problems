//  Topcoder Algorithm Competition.
//
//  SRM 471, DIV II.
//  Problem B:
//  Algorithm: Dynamic Programming.
//
//  Copyright: Su Shi (carmack.shi@gmail.com).
//
//  All rights reserved.
//

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<map<string, int> > Results;

void Init(int play_list_length) {
  Results.resize(play_list_length);
}

int Find(const vector<string>& songs, int play_list_length,
         const string& prefix) {

  if (play_list_length == 0)
    return 1;

  map<string, int>& sub_result = Results[play_list_length - 1];

  if (sub_result.find(prefix) == sub_result.end()) {
    int count = 0;
    for (size_t i = 0; i < songs.size(); ++i) {
      if (songs[i].substr(0, 3) == prefix || prefix == "0")
        count += Find(songs, play_list_length - 1,
                      songs[i].substr(songs[i].length() - 3, 3));
    }

    sub_result[prefix] = count;
  }

  return sub_result[prefix];
}

int main() {

  int t, n, k;

  cin >> t;

  for (int i = 1; i <= t; ++i) {
    cin >> n >> k;

    vector<string> songs;
    songs.reserve(n);
    string song_name;

    for (int j = 1; j <= n; ++j) {
      cin >> song_name;
      songs.push_back(song_name);
    }

    Init(k);

    cout << "Case #" << i << ": "
         << Find(songs, k, "0") << endl;
  }

  return 0;
}