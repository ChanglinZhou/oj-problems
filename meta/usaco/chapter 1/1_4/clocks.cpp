/*
ID: amble_s1
LANG: C++
TASK: clocks
*/

#include <fstream>
#include <cassert>
#include <vector>
#include <string>
#include <iterator>

using namespace std;

string moves[9] = {"ABDE", "ABC", "BCEF", "ADG", 
                   "BDEFH", "CFI","DEGH", "GHI", "EFHI"};
int move_length[9] = {4, 3, 4, 3, 5, 3, 4, 3, 4};
int best_number;
int best_count;
vector<int> best_record;

int get_count(const vector<int>& record)
{
  int total_move_count = 0;
  for (int i = 0; i < record.size(); ++i) {
    total_move_count += record[i];
  }

  return total_move_count;
}

void update_record(vector<int> inter_clocks, const vector<int>& record) {
  int total_number = 0;
  for (size_t i = 0; i < record.size(); ++i) {
    int move_count = record[i];
    while (move_count > 0) {
      for (size_t j = 0; j < moves[i].size(); ++j) {
        inter_clocks[moves[i][j] - 'A'] += 3;
      }
      --move_count;
      total_number += move_length[i];
    }
  }

  bool all_done = true;
  for(size_t k = 0; k < inter_clocks.size(); ++k) {
    if (inter_clocks[k] % 12 != 0) {
      all_done = false;
      break;
    }
  }

  if (all_done) {
    if (best_count == 0 || 
        best_count > get_count(record) ||
        best_number > total_number) {
      best_record.assign(record.begin(), record.end());
      best_number = total_number;
      best_count = get_count(best_record);
    }
  }
}

void search(const vector<int>& clocks, int index) {
  static vector<int> record;
  
  if (index < 0 || index >= 9)
    return;

  if (index == 0) {
    record.assign(9, 0);
    best_record.assign(9, 0);
    best_number = 0;
    best_count = 0;
  }

  if (best_count > 0 && get_count(record) > best_count)
    return;

  int j;
  for (j = 0; j < 4; ++j) {
    record[index] = j;
    update_record(clocks, record);
    search(clocks, index + 1);
    if (best_count > 0 && get_count(record) > best_count)
      break;
  }
}

vector<int> get_moves(const vector<int>& record) {
  vector<int> moves;
  for (size_t i = 0; i < best_record.size(); ++i) {
    for (int j = 0; j < best_record[i]; ++j) {
      moves.push_back(i + 1);
    }
  }

  return moves;
}

int main()
{
    vector<int> clocks(9);
    ifstream infile("clocks.in");
    ofstream outfile("clocks.out");

    assert(infile && outfile);
    if (!infile || !outfile)
        return -1;

    copy(istream_iterator<int>(infile), istream_iterator<int>(),
         clocks.begin());

    search(clocks, 0);
    vector<int> best_moves = get_moves(best_record);

    copy(best_moves.begin(), best_moves.end() - 1, 
         ostream_iterator<int>(outfile, " "));
    outfile << static_cast<int>(best_moves.back()) << endl;

    return 0;
}