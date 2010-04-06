// Copyright (c) 2010, Su Shi <carmack.shi [at] gmail.com>
//
// All rights reserved.

#ifndef THOR_STRING_UTILS_H_
#define THOR_STRING_UTILS_H_

#include <cstddef>
#include <algorithm>
#include <string>

namespace thor {

typedef std::string String;

int char_map[256] = { 0 };

String FindShortestDigest(const String& content) {

  std::size_t expected_kinds_of_char = 0;
  std::fill(char_map, char_map + sizeof(char_map), 0);

  size_t content_length = content.size();
  for (size_t i = 0; i < content_length; ++i) {
    ++char_map[content[i]];
    if (char_map[content[i]] == 1) ++expected_kinds_of_char;
  }

  std::fill(char_map, char_map + sizeof(char_map), 0);

  size_t start, end;
  size_t current_kinds_of_char = 1;
  char_map[content[0]] = 1;
  size_t shortest_length = content_length + 1;
  size_t final_start, final_end;
  for (start = 0, end = 1; start < content_length; ++start) {
    if (start > 0) {
      --char_map[content[start - 1]];
      if (char_map[content[start - 1]] == 0) --current_kinds_of_char;
    }
    // If current kinds of character are less than expectation, we should extend
    // it.
    while (end < content_length &&
      current_kinds_of_char < expected_kinds_of_char) {
        ++char_map[content[end]];
        if (char_map[content[end]] == 1) ++current_kinds_of_char;
        ++end;
    }

    if (current_kinds_of_char == expected_kinds_of_char) {
      size_t length = end - start;
      if (length < shortest_length) {
        shortest_length = length;
        final_start = start;
        final_end = end;
      }
    }
  }

  return content.substr(final_start, final_end - final_start);

}

}  // thor


#endif  // THOR_STRING_UTILS_H_