/*
ID: amble_s1
LANG: C++
TASK: castle
*/

#include <fstream>
#include <cassert>
#include <cstring>
#include <algorithm>

using namespace std;

// Describe which module(row, column) the wall belongs to, and its direction.
typedef struct _Wall {
  int row;
  int column;
  char direction;
} Wall;

// Directions
const int WEST = 0x01;
const int NORTH = 0x02;
const int EAST = 0x04;
const int SOUTH = 0x08;

// Direction alias.
char Direction_Alias[SOUTH + 2] = ".WN.E...S";

// Moves
const int Moves[SOUTH + 1][2] = { {0, 0},
                                  {0, -1}, {-1, 0}, {0, 0}, {0, 1},
                                  {0, 0}, {0, 0}, {0, 0}, {1, 0} };

// Maximum size of n, m.
const int MAX_SIZE = 50;

// Floor plan
int map[MAX_SIZE][MAX_SIZE];

// Modules belong to which room component.
int rooms[MAX_SIZE][MAX_SIZE];

// Area of each kind of room.
int room_areas[MAX_SIZE * MAX_SIZE + 1];

// N stands for width, M stands for length.
int n = 0, m = 0;

// Maximum room area in the floor plan.
int max_area = 0;

// Initialize room number of each module on the floor plan to be 0, and each
// room's area to be 0.
void init() {
  for (int i = 0; i < MAX_SIZE; ++i)
    for (int j = 0; j < MAX_SIZE; ++j) {
      rooms[i][j] = 0;
    }
  memset(room_areas, 0, sizeof(room_areas));
}

// Use flood-fill strategy to find connected modules(DFS).
void flood_fill(int i, int j, int new_room) {
  if (i < 0 || i >= n || j < 0 || j >= m ||
      rooms[i][j] > 0 || new_room <= 0) return;

  rooms[i][j] = new_room;

  if ((map[i][j] & NORTH) == 0)
    flood_fill(i - 1, j, new_room);

  if ((map[i][j] & WEST) == 0)
    flood_fill(i, j - 1, new_room);

  if ((map[i][j] & SOUTH) == 0)
    flood_fill(i + 1, j, new_room);

  if ((map[i][j] & EAST) == 0)
    flood_fill(i, j + 1, new_room);
}

// Find all independent rooms by using flood-fill algorithm started on a 
// non-assigned moudle.
int find_rooms() {
  int num_rooms = 0;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) {
      if (rooms[i][j] == 0) {
        ++num_rooms;
        flood_fill(i, j, num_rooms);
      }
    }

  return num_rooms;
}

// Calculate each area for each room, and get the maximum area.
void calc_areas() {
  max_area = 0;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) {
      // Each time updating the area of a room, try to check whether it's larger
      // than current maximum.
      max_area = max(max_area, ++room_areas[rooms[i][j]]);
    }
}

// Find the perfect wall to remove from farthest to west firstly, then from
// farthest to south.
int find_optimal_wall(Wall& optima_wall) {
  int max_merged_area = max_area;
  int directions[2] = { NORTH, EAST };

  for (int j = 0; j < m; ++j)
    for (int i = n - 1; i >= 0; --i)
      for (int k = 0; k < 2; ++k) {
        int d = directions[k];
        if ((map[i][j] & d) == 0) continue;

        int neighbor_i = i + Moves[d][0];
        int neighbor_j = j + Moves[d][1];

        if (neighbor_i < 0 || neighbor_i >= n ||
            neighbor_j < 0 || neighbor_j >= m) continue;

        int current_room = rooms[i][j];
        int neighbor_room = rooms[neighbor_i][neighbor_j];
        // The neighbor module from north above or east right does not belong to
        // the same room.
        if (current_room != neighbor_room) {
          int merged_area = room_areas[current_room] +
                            room_areas[neighbor_room];
          if (merged_area > max_merged_area) {
            max_merged_area = merged_area;
            optima_wall.row = i + 1;
            optima_wall.column = j + 1;
            optima_wall.direction = Direction_Alias[d];
          }
        }
      }  // For different directions(North, East).

  return max_merged_area;
}

int main() {
  ifstream infile("castle.in");
  ofstream outfile("castle.out");
  if (!infile || !outfile) return -1;

  while (infile >> m >> n) {
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        infile >> map[i][j];

    init();

    outfile << find_rooms() << endl;

    calc_areas();
    outfile << max_area << endl;

    int max_merged_area = max_area;
    Wall optimal_wall;
    max_merged_area = find_optimal_wall(optimal_wall);
    outfile << max_merged_area << endl;
    outfile << optimal_wall.row << " "
            << optimal_wall.column << " "
            << optimal_wall.direction << endl;
  }

  return 0;
}
