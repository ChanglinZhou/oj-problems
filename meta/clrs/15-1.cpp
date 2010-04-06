/*
 * Problem: CLRS Problem 15-1: Bitonic euclidean traveling-salesman problem.
 * Algorithm: DP ( O(n^2) )
 * Author: meta
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

struct Point {
  double x;
  double y;
};

double dist(const Point& ptA, const Point& ptB) {
  return sqrt((ptA.x - ptB.x)*(ptA.x - ptB.x) +
              (ptA.y - ptB.y)*(ptA.y - ptB.y));
}

bool compare(const Point& ptA, const Point& ptB) {
  return ptA.x < ptB.x;
}

void print_path(const vector<vector<int> >& tour, int i, int j) {
  // right-to-left sub-path
  if (i < j) {
    int k = tour[i][j];
    cout << "P" << (k + 1) << endl;
    if (k > 0)
      print_path(tour, i, k);
  } else { // i > j: left-to-right sub-path, excluding P1 & Pn
    int k = tour[j][i];
    if (k > 0) {
      print_path(tour, k, j);
      cout << "P" << (k + 1)<< endl;
    }
  }
}

void print_tour(const vector<vector<int> >& tour) {
  int n = tour.size();
  if (n <= 2) return;

  cout << "P" << n << endl;
  cout << "P" << n - 1 << endl;
  int k = tour[n - 2][n - 1];
  print_path(tour, k, n - 2);
  cout << "P" << (k + 1) << endl;
}

double euclidean_tsp(vector<Point> pts, vector<vector<int> >& tour) {
  // Checking number of points, must be >= 2.
  int n = pts.size();
  if (n <= 2) return 0.0;

  // Initialize the bitonics[0...n-1, 0...n-1] which are used to record the
  // length of shortest bitonic path Pi,j, where i <= j.
  vector<double> bitonic_row(n, 0.0);
  vector<vector<double> > bitonics(n, bitonic_row);

  // Sort the points so that <P0, P1, ..., Pn-1> are in order of increasing
  // x-coordinate.
  sort(pts.begin(), pts.end(), compare);

  // Calculate the length of shortest bitonic paths.
  bitonics[0][1] = dist(pts[0], pts[1]);
  // Actually, it's impossible to hit this sub-path, tour[0][j], while printing
  // the whole tour, since we check the value of i( > 0) to make sure there's
  // deeper recursive sub-path left to be printed.
  tour[0][1] = 0;
  for (int j = 2; j < n; ++j) {
    // i < j - 1
    for (int i = 0; i < j - 1; ++i) {
      bitonics[i][j] = bitonics[i][j - 1] + dist(pts[j - 1], pts[j]);
      tour[i][j] = j - 1;
    }
    // i = j - 1
    for (int k = 0; k < j - 1; ++k) {
      // k < i
      double q = bitonics[k][j - 1] + dist(pts[k], pts[j]);
      if (k == 0 || q < bitonics[j - 1][j]) {
        bitonics[j - 1][j] = q;
        tour[j - 1][j] = k;
      }
    }
  }
  // bitonics[n - 1, n - 1] is the optimal bitonic tour.
  bitonics[n - 1][n - 1] = bitonics[n - 2][n - 1] +
                           dist(pts[n - 2], pts[n - 1]);
  return bitonics[n - 1][n - 1];
}

int main() {
  int n;
  cin >> n;
  if (n <= 0) return -1;

  vector<Point> pts;
  pts.reserve(n);
  for(int i = 0; i < n; ++i) {
    Point pt;
    cin >> pt.x >> pt.y;
    pts.push_back(pt);
  }

  // tour[i][j] records the immediate predecessor of Pj on the shortest
  // bitonic path Pi,j
  vector<int> tour_row(n, -1);
  vector<vector<int> > tour(n, tour_row);

  cout << setiosflags(ios::fixed) << setprecision(2)
       << euclidean_tsp(pts, tour) << endl;

  print_tour(tour);

  return 0;
}