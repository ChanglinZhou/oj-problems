/*
ID: amble_s1
LANG: C++
TASK: packrec
*/

#include <fstream>
#include <cassert>
using namespace std;

const int MAXLENGTH = 50;

struct Rect {
    int wid;
    int ht;
};

char map[MAXLENGTH * 2 + 1];

int update(int width, int height) {
    
    static int minArea = 0;
    int s = width * height;

    if (minArea == 0 || s < minArea) {
        minArea = s;
        memset(map, 0, sizeof(map));
    }

    if (s == minArea) {
        map[min(width, height)] = 1;
    }

    return minArea;
}

int area(Rect* r) {
    int min, height, width, i;
    min = 0;

    /* scheme 1
     * 0 1 2 3
     */
    height = width = 0;
    for (i = 0; i < 4; ++i) {
        width += r[i].wid;
        height = max(r[i].ht, height);
    }
    min = update(width, height);
    
    /* scheme 2
     * 0 1 2
     * _____
     *
     *   3
     */
    height = width = 0;
    for (i = 0; i < 3; ++i) {
        width += r[i].wid;
        height = max(r[i].ht, height);
    }
    height += r[3].ht;
    width = max(r[3].wid, width);
    min = update(width, height);

    /*scheme 3
     * 0 1 2
     * ___
     *  3
     */
    height = max(r[0].ht, r[1].ht) + r[3].ht;
    height = max(r[2].ht, height);
    width = max(r[0].wid + r[1].wid, r[3].wid) + r[2].wid;
    min = update(width, height);

    /* scheme 4, 5
     * 0 1 2
     *   _
     *   3
     */
    height = max(r[0].ht, r[2].ht);
    height = max(height, r[1].ht + r[3].ht);
    width = r[0].wid + r[2].wid;
    width += max(r[1].wid, r[3].wid);
    min = update(width, height);

    /*scheme 6
     * 0 1
     * 3 2
    */
    height = max(r[0].ht + r[3].ht, r[1].ht + r[2].ht);
    width = r[3].wid + r[2].wid;

    if (r[3].ht < r[2].ht)
        width = max(width, r[0].wid + r[2].wid);

    if (r[3].ht > r[2].ht)
        width = max(width, r[3].wid + r[1].wid);

    if (r[0].ht + r[3].ht > r[2].ht && 
        r[3].ht < r[1].ht + r[2].ht)
        width = max(width, r[0].wid + r[1].wid);

    if (r[0].ht + r[3].ht <= r[2].ht)
        width = max(width, r[1].wid);

    if (r[3].ht >= r[1].ht + r[2].ht)
        width = max(width, r[0].wid);

    min = update(width, height);

    return min;
}

int rotate(Rect* r, int n) {
    if (n == 4)
        return area(r);

    int t1, t2;
    t1 = rotate(r, n + 1);
    swap<int>(r[n].ht, r[n].wid);
    t2 = rotate(r, n + 1);

    return (t1 > t2) ? t1 : t2;
}

int permute(Rect* r, int n) {
    if (n == 4)
        return rotate(r, 0);

    int min, t;
    min = 0;
    for(int i = n; i < 4; ++i) {
        swap(r[n], r[i]);
        t = permute(r, n + 1);
        swap(r[n], r[i]);
        if (min == 0 || t < min)
            min = t;
    }

    return min;
}

int main(int argc, char** argv)
{
    Rect r[4];
    ifstream infile("packrec.in");
    ofstream outfile("packrec.out");

    if (!infile || !outfile)
        return -1;

    for (int i = 0; i < 4; ++i) {
        infile >> r[i].ht >> r[i].wid;
    }

    int min = permute(r, 0);
    outfile << min << endl;
    for(int i = 1; i <= 2*MAXLENGTH; ++i) {
        if(map[i])
            outfile << i << " " << min / i << endl;
    }

    return 0;
}