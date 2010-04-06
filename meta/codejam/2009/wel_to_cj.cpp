/* Problem: Welcome to Code Jam(Qualification Round, Google Code Jam 2009)
 * Algorithm: 
 * Author: meta(carmack.shi@gmail.com)
 */

// STL header files
#include <vector>
#include <deque>
#include <string>
#include <fstream>
using ::std::vector;
using ::std::deque;
using ::std::string;
using ::std::ifstream;
using ::std::ofstream;
using ::std::endl;

// STL extension header files
#include <hash_map>
#include <regex>
using ::stdext::hash_map;

// Input & output file names
const char* input_name = "C-small.in";
const char* output_name = "C-small.out";


deque<string> split_string(const string& pattern) {
  deque<string> sub_strings;

  string new_string = "";
  string::size_type left, right, start_index;
  start_index = 0;
  while (start_index < pattern.size()) {
    left = pattern.find('(', start_index);
    right = pattern.find(')', start_index);
    if (left == string::npos && right == string::npos) break;
    if (start_index < left)
      sub_strings.push_back(pattern.substr(start_index, left - 1));
    sub_strings.push_back(pattern.substr(left, right + 1 - left));
    start_index = right + 1;
  }
  if (start_index < pattern.size())
    sub_strings.push_back(pattern.substr(start_index));

  return sub_strings;
}


bool is_prefix_valid(const hash_map<string, string>& alien_dict,
                     const string& prefix) {
  if (prefix.empty()) return true;
  bool ret = false;
  for (hash_map<string, string>::const_iterator it = alien_dict.begin();
       it != alien_dict.end(); ++it) {
    if (it->first.substr(0, prefix.size()) == prefix) {
      ret = true;
      break;
    }
  }

  return ret;
}


// Simulate recursive enumeration.
int valid_word_count(const hash_map<string, string>& alien_dict,
                     const deque<string>& sub_strings, int index = 0,
                     string previous = "") {
  // Complete search?
  if (index == sub_strings.size()) {
    if (alien_dict.find(previous) != alien_dict.end())
      return 1;
    else
      return 0;
  }
  // Branch predication
  if (!is_prefix_valid(alien_dict, previous)) return 0;

  const string& sub_string = sub_strings[index];
  int count = 0;
  if (sub_string[0] == '(') {
    for (string::size_type i = 1; i <= sub_string.size() - 2; ++i) {
      count += valid_word_count(alien_dict, sub_strings,
                                index + 1, previous + sub_string[i]);
    }
  } else {
    count = valid_word_count(alien_dict, sub_strings,
                             index + 1, previous + sub_string);
  }

  return count;
}


// Total legal alien words for specified pattern.
int word_count_for_pattern(const hash_map<string, string>& alien_dict,
                           const string& pattern) {
  deque<string> sub_strings = split_string(pattern);

  return valid_word_count(alien_dict, sub_strings);
}


int main() {
  // Open input & output files
  ifstream infile(input_name);
  ofstream outfile(output_name);
  if (!infile || !outfile) return -1;
  
  // l stands for length of each alien word.
  // d stands for number of total words in alien world.
  // n stands for number of test cases for this input file.
  int l, d, n;
  infile >> l >> d >> n;
  // Intialize the alien dictionary
  // <word, word> ?
  hash_map<string, string> alien_dict;
  string word = "";
  while (d--) {
    infile >> word;
    alien_dict[word] = word;
  }
  // Processing case by case
  string pattern = "";
  int k = 0;
  for (int i = 1; i <= n; ++i) {
    infile >> pattern;
    k = word_count_for_pattern(alien_dict, pattern);
    outfile << "Case #" << i << ": " << k << endl;
  }

  return 0;
}