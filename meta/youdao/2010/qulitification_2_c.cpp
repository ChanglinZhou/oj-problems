#include <iostream>
#include <vector>

using namespace std;

const int Modular = 9907;

struct SkillRequirement {
  int skill_level_;
  int count_;
};

struct Leader {

  int require_number_;
  vector<SkillRequirement> requires_;
  int id_;
};

struct Fresh {
  int skill_count_;
  vector<int> skills_;
  int id_;
};


int main() {

  int n;

  return 0;

}