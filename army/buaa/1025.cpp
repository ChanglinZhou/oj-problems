#include <iostream>
#include <vector>
#include <iterator>
#include <functional>
using namespace std;

int factors[] = 
{
0,
1,
2,
2,
3,
2,
4,
2,
4,
3,
4,
2,
6,
2,
4,
4,
5,
2,
6,
2,
6,
4,
4,
2,
8,
3,
4,
4,
6,
2,
8,
2,
6,
4,
4,
4,
9,
2,
4,
4,
8,
2,
8,
2,
6,
6,
4,
2,
10,
3,
6,
4,
6,
2,
8,
4,
8,
4,
4,
2,
12,
2,
4,
6,
7,
4,
8,
2,
6,
4,
8,
2,
12,
2,
4,
6,
6,
4,
8,
2,
10,
5,
4,
2,
12,
4,
4,
4,
8,
2,
12,
4,
6,
4,
4,
4,
12,
2,
6,
6,
9,
2,
8,
2,
8,
8,
4,
2,
12,
2,
8,
4,
10,
2,
8,
4,
6,
6,
4,
4,
16,
3,
4,
4,
6,
4,
12,
2,
8,
4,
8,
2,
12,
4,
4,
8,
8,
2,
8,
2,
12,
4,
4,
4,
15,
4,
4,
6,
6,
2,
12,
2,
8,
6,
8,
4,
12,
2,
4,
4,
12,
4,
10,
2,
6,
8,
4,
2,
16,
3,
8,
6,
6,
2,
8,
6,
10,
4,
4,
2,
18,
2,
8,
4,
8,
4,
8,
4,
6,
8,
8,
2,
14,
2,
4,
8,
9,
2,
12,
2,
12,
4,
4,
4,
12,
4,
4,
6,
10,
4,
16,
2,
6,
4,
4,
4,
16,
4,
4,
4,
12,
4,
8,
2,
12,
9,
4,
2,
12,
2,
8,
8,
8,
2,
12,
4,
6,
4,
8,
2,
20,
2,
6,
6,
6,
6,
8,
4,
8,
4,
8,
2,
18,
4,
4,
8,
9,
2,
8,
4,
12,
6,
4,
2,
16,
4,
8,
4,
6,
2,
16,
2,
10,
8,
4,
6,
12,
2,
4,
6,
16,
2,
8,
2,
6,
8,
8,
4,
18,
3,
8,
4,
6,
2,
12,
4,
8,
8,
4,
4,
18,
4,
4,
4,
10,
4,
12,
2,
12,
4,
8,
2,
16,
2,
4,
12,
6,
2,
8,
4,
14,
4,
8,
4,
15,
6,
4,
4,
8,
4,
16,
2,
6,
6,
4,
4,
20,
2,
6,
4,
12,
4,
12,
4,
8,
8,
4,
2,
12,
2,
12,
8,
12,
2,
8,
4,
6,
8,
4,
2,
24,
3,
4,
6,
12,
4,
8,
2,
10,
6,
8,
4,
12,
2,
8,
8,
8,
4,
16,
2,
12,
4,
4,
2,
16,
8,
4,
6,
6,
2,
16,
4,
12,
4,
4,
4,
18,
2,
4,
8,
15,
2,
8,
4,
6,
10,
8,
4,
16,
2,
8,
4,
6,
4,
12,
4,
12,
4,
8,
2,
24,
2,
4,
6,
8,
6,
8,
4,
6,
8,
8,
2,
20,
2,
8,
8,
6,
4,
8,
2,
16,
9,
8,
2,
12,
4,
4,
4,
14,
2,
18,
4,
6,
4,
4,
8,
16,
2,
4,
8,
12,
2,
16,
2,
10,
8,
4,
2,
18,
4,
8,
4,
8,
4,
8,
6,
12,
6,
4,
2,
24,
4,
4,
8,
9,
4,
12,
2,
8,
4,
12,
2,
12,
4,
8,
12,
10,
4,
8,
2,
12,
4,
4,
2,
24,
4,
8,
6,
6,
2,
16,
4,
10,
8,
4,
4,
12,
4,
8,
4,
16,
2,
12,
2,
6,
12,
4,
4,
20,
3,
8,
6,
12,
4,
8,
4,
8,
4,
4,
6,
24,
2,
4,
4,
12,
4,
16,
2,
6,
6,
12,
4,
16,
4,
4,
8,
6,
2,
12,
4,
20,
8,
4,
2,
12,
4,
4,
10,
8,
2,
16,
2,
12,
4,
8,
6,
21,
2,
6,
4,
12,
4,
8,
4,
8,
12,
4,
2,
18,
4,
8,
4,
10,
2,
16,
8,
6,
4,
8,
2,
24,
2,
8,
6,
6,
6,
8,
2,
12,
8,
8,
4,
18,
2,
4,
8,
16,
2,
8,
2,
12,
8,
4,
4,
20,
5,
4,
8,
6,
4,
24,
2,
8,
4,
4,
4,
12,
6,
8,
6,
16,
2,
8,
2,
12,
8,
8,
2,
20,
4,
12,
8,
6,
2,
8,
4,
10,
6,
8,
2,
24,
2,
4,
8,
8,
8,
12,
4,
6,
4,
8,
4,
24,
2,
4,
12,
9,
2,
8,
4,
16,
4,
8,
2,
18,
4,
8,
4,
10,
4,
16,
2,
6,
12,
4,
4,
16,
4,
4,
4,
18,
2,
16,
4,
14,
8,
4,
4,
12,
2,
8,
6,
8,
4,
16,
8,
6,
4,
4,
2,
30,
4,
6,
4,
6,
6,
12,
2,
16,
7,
8,
4,
12,
2,
4,
12,
12,
4,
12,
2,
12,
8,
8,
2,
16,
4,
4,
6,
12,
4,
16,
2,
10,
4,
8,
4,
24,
2,
4,
8,
16,
2,
8,
4,
6,
12,
4,
4,
18,
2,
16,
4,
6,
2,
12,
6,
8,
8,
4,
4,
24,
4,
8,
8,
15,
4,
8,
2,
6,
4,
8,
4,
24,
4,
4,
8,
6,
2,
16,
4,
18,
6,
4,
4,
12,
8,
8,
4,
8,
2,
20,
2,
12,
4,
8,
4,
20,
4,
4,
12,
12,
2,
8,
2,
8,
12,
8,
2,
18,
2,
8,
4,
14,
6,
8,
4,
12,
8,
4,
2,
32,
3,
4,
4,
6,
6,
12,
6,
10,
4,
12,
4,
12,
2,
8,
12,
8,
2,
16,
2,
12,
8,
4,
2,
24,
4,
4,
6,
12,
4,
16,
4,
8,
6,
8,
8,
12,
2,
4,
4,
20,
2,
18,
2,
12,
8,
4,
2,
16,
4,
8,
10,
6,
4,
8,
4,
16,
8,
4,
4,
27,
4,
8,
8,
8,
4,
8,
2,
6,
6,
16,
2,
20,
4,
4,
8,
6,
4,
16,
2,
16,
4,
4,
4,
24,
6,
4,
6,
12,
2,
16,
6,
6,
4,
4,
8,
24,
2,
8,
4,
12,
2,
8,
4,
10,
16,
8,
2,
12,
4,
12,
4,
16,
2,
12,
4,
6,
8,
4,
4,
28,
3,
8,
6,
6,
4,
16,
2,
12,
8,
8,
2,
18,
4,
4,
12,
10,
2,
8,
4,
18,
6,
4,
2,
16,
4,
8,
8,
12,
4,
24,
2,
12,
4,
8,
4,
12,
2,
4,
8,
16,
8,
8,
4,
6,
8,
4,
4,
30,
2,
8,
4,
12,
2,
12,
8,
8,
6,
4,
2,
24,
2,
8,
8,
11,
6,
16,
4,
6,
8,
8,
2,
16,
2,
8,
12,
12,
4,
8,
2,
20,
4,
4,
4,
18,
8,
4,
4,
8,
2,
24,
2,
6,
10,
8,
4,
24,
4,
6,
4,
12,
2,
12,
2,
16,
8,
8,
4,
12,
2,
8,
12,
10,
4,
8,
6,
6,
4,
12,
4,
32,
4,
4,
6,
6,
8,
8,
2,
14,
9,
8,
2,
24,
2,
4,
8,
8,
2,
12,
4,
18,
4,
8,
2,
20,
8,
8,
8,
6,
2,
16,
4,
8,
8,
4,
4,
18,
2,
8,
4,
24,
4,
16,
2,
6,
12,
4,
6,
16,
2,
8,
8,
6,
4,
20,
4,
10,
4,
4,
4,
24,
4,
4,
6,
16,
4,
8,
4,
12,
4,
12,
2,
24,
2,
4,
16,
9,
4,
8,
4,
16,
8,
8,
2,
12,
4,
8,
4,
10,
4,
24,
2,
6,
8,
4,
6,
24,
4,
8,
6,
12,
2,
8,
6,
12,
8,
4,
2,
24,
4,
16,
4,
8,
2,
8,
4,
12,
12,
4,
4,
30,
2,
4,
4,
12,
4,
12,
4,
8,
8,
12,
4,
12,
2,
4,
12,
14,
2,
16,
4,
12,
8,
8,
2,
24,
9,
4,
4,
6,
2,
16,
2,
20,
6,
4,
8,
12,
2,
4,
8,
16,
4,
16,
4,
6,
8,
8,
4,
24,
2,
10,
6,
6,
4,
16,
4,
8,
4,
8,
2,
36,
4,
4,
4,
10,
8,
8,
4,
6,
8,
8,
4,
16,
4,
12,
12,
12,
2,
12,
2,
18,
8,
4,
2,
12,
4,
4,
12,
16,
2,
16,
2,
12,
4,
4,
8,
25,
2,
8,
4,
18,
2,
16,
2,
8,
12,
4,
2,
12,
8,
8,
8,
12,
4,
12,
4,
12,
4,
4,
2,
32,
2,
4,
12,
6,
6,
16,
2,
10,
4,
16,
4,
18,
4,
8,
8,
8,
4,
8,
4,
12,
6,
8,
4,
28,
4,
4,
4,
6,
4,
24,
4,
12,
8,
4,
4,
12,
4,
8,
6,
20,
2,
8,
4,
12,
16,
4,
2,
24,
3,
8,
4,
12,
2,
8,
8,
12,
10,
8,
4,
24,
2,
4,
4,
8,
4,
24,
4,
6,
4,
8,
4,
20,
4,
8,
12,
6,
4,
8,
2,
24,
4,
4,
4,
24,
4,
8,
8,
16,
2,
16,
4,
6,
6,
8,
4,
16,
4,
4,
8,
12,
6,
12,
2,
10,
12,
8,
2,
24,
2,
16,
8,
8,
2,
8,
8,
6,
4,
4,
2,
36,
4,
8,
8,
9,
6,
8,
2,
8,
12,
12,
2,
18,
2,
4,
8,
20,
4,
14,
2,
12,
4,
8,
8,
16,
4,
4,
6,
6,
4,
24,
2,
14,
4,
8,
6,
18,
4,
4,
8,
16,
2,
16,
2,
12,
16,
4,
2,
20,
2,
8,
8,
6,
2,
12,
8,
16,
4,
8,
2,
24,
4,
4,
6,
12,
8,
8,
4,
12,
4,
8,
2,
32,
4,
4,
8,
6,
4,
16,
6,
20,
9,
4,
2,
12,
6,
8,
4,
8,
4,
24,
2,
6,
8,
8,
4,
20,
4,
4,
10,
24,
4,
8,
2,
8,
8,
4,
8,
18,
2,
12,
8,
10,
2,
16,
4,
6,
6,
8,
2,
32,
4,
8,
4,
12,
4,
16,
2,
18,
4,
8,
2,
12,
6,
4,
18,
8,
4,
8,
2,
12,
8,
8,
2,
30,
4,
8,
6,
6,
4,
16,
4,
8,
8,
4,
8,
24,
2,
8,
8,
21,
2,
12,
4,
6,
8,
8,
2,
16,
2,
16,
6,
12,
2,
8,
8,
10,
12,
4,
2,
30,
2,
4,
4,
16,
8,
8,
2,
12,
6,
8,
4,
24,
4,
8,
8,
6,
2,
24,
4,
16,
4,
4,
4,
12,
8,
4,
8,
10,
4,
24,
4,
12,
8,
4,
4,
24,
2,
4,
8,
12,
4,
8,
2,
16,
12,
12,
2,
12,
2,
8,
4,
16,
4,
16,
6,
6,
8,
4,
4,
40,
3,
6,
12,
6,
4,
8,
4,
8,
4,
12,
4,
18,
2,
12,
8,
12,
2,
8,
2,
18,
12,
8,
4,
16,
8,
4,
4,
12,
2,
24,
4,
10,
4,
4,
8,
24,
4,
4,
6,
16,
2,
16,
2,
6,
12,
4,
4,
28,
8,
8,
4,
6,
2,
12,
4,
16,
6,
8,
4,
24,
2,
8,
8,
10,
4,
12,
2,
12,
8,
16,
4,
16,
2,
4,
16,
6,
4,
8,
2,
24,
4,
4,
4,
27,
4,
4,
8,
16,
4,
16,
8,
6,
6,
4,
6,
20,
2,
8,
4,
12,
4,
20,
2,
8,
16,
8,
2,
12,
2,
8,
6,
18,
4,
16,
4,
6,
4,
8,
4,
36,
2,
8,
4,
12,
6,
16,
4,
10,
8,
8,
2,
12,
6,
4,
12,
8,
4,
12,
4,
24,
4,
4,
2,
24,
6,
8,
12,
6,
4,
16,
2,
8,
8,
8,
4,
24,
4,
4,
4,
20,
4,
8,
4,
6,
12,
8,
2,
32,
3,
12,
4,
6,
4,
12,
8,
14,
4,
4,
6,
24,
2,
12,
10,
8,
4,
8,
2,
6,
8,
16,
2,
30,
2,
4,
10,
12,
2,
8,
2,
16,
12,
4,
4,
12,
8,
8,
8,
12,
2,
32,
4,
12,
4,
4,
4,
16,
4,
8,
6,
18,
2,
8,
4,
20,
8,
4,
2,
18,
4,
8,
12,
8,
2,
16,
4,
6,
8,
8,
4,
32,
4,
6,
4,
12,
12,
12,
4,
8,
4,
8,
2,
24,
2,
4,
12,
15,
4,
16,
4,
12,
4,
4,
4,
24,
4,
8,
8,
6,
2,
24,
2,
12,
12,
4,
8,
12,
4,
8,
4,
24,
4,
12,
4,
6,
8,
4,
4,
20,
4,
8,
8,
12,
2,
16,
6,
16,
4,
8,
2,
36,
4,
4,
4,
14,
4,
8,
2,
12,
12,
8,
4,
16,
2,
4,
16,
6,
2,
16,
2,
20,
8,
16,
2,
12,
4,
8,
6,
8,
6,
16,
2,
6,
8,
8,
8,
36,
2,
4,
4,
12,
4,
8,
6,
16,
15,
4,
2,
18,
2,
16,
4,
10,
4,
12,
8,
6,
8,
4,
2,
32,
4,
4,
6,
12,
4,
16,
4,
12,
4,
12,
4,
24,
2,
8,
8,
8,
6,
16,
4,
12,
6,
4,
2,
20,
8,
4,
8,
12,
2,
24,
4,
16,
4,
8,
6,
12,
4,
4,
16,
24,
2,
8,
2,
6,
8,
8,
2,
24,
2,
16,
8,
6,
8,
8,
4,
10,
6,
4,
2,
36,
4,
4,
4,
8,
4,
20,
6,
12,
8,
8,
2,
28,
2,
8,
12,
9,
4,
8,
4,
16,
8,
4,
4,
18,
8,
4,
4,
20,
2,
16,
2,
12,
8,
8,
8,
16,
2,
4,
8,
12,
2,
24,
2,
12,
16,
8,
4,
12,
4,
12,
6,
8,
2,
8,
4,
18,
4,
8,
4,
40,
2,
8,
8,
6,
4,
12,
4,
8,
6,
16,
4,
12,
4,
4,
12,
16,
4,
18,
2,
12,
4,
4,
4,
32,
8,
4,
8,
6,
4,
16,
4,
10,
8,
4,
4,
18,
4,
8,
4,
24,
4,
8,
2,
12,
18,
4,
2,
24,
3,
16,
8,
12,
2,
16,
4,
8,
4,
4,
4,
24,
2,
8,
12,
10,
6,
16,
4,
6,
4,
8,
4,
24,
8,
4,
8,
12,
2,
8,
2,
28,
8,
8,
2,
24,
4,
4,
8,
8,
4,
24,
2,
6,
4,
12,
8,
20,
4,
4,
6,
12,
8,
16,
4,
8,
8,
8,
2,
30,
2,
8,
4,
12,
2,
8,
12,
6,
12,
8,
4,
32,
2,
8,
4,
6,
4,
12,
2,
20,
8,
8,
4,
12,
2,
8,
16,
16,
2,
8,
6,
18,
8,
4,
6,
27,
4,
4,
4,
6,
2,
32,
2,
12,
6,
8,
4,
12,
4,
8,
4,
20,
4,
16,
4,
12,
12,
4,
4,
16,
4,
8,
12,
12,
2,
8,
4,
12,
8,
8,
2,
36,
2,
4,
8,
8,
8,
16,
2,
6,
10,
12,
2,
30,
4,
8,
8,
12,
2,
12,
4,
16,
4,
4,
4,
12,
8,
12,
6,
14,
4,
16,
2,
6,
8,
4,
8,
32,
2,
8,
8,
24,
2,
8,
2,
10,
12,
4,
8,
12,
2,
8,
4,
16,
2,
24,
4,
6,
8,
8,
2,
36,
5,
4,
8,
6,
8,
8,
4,
16,
8,
8,
2,
18,
4,
8,
16,
10,
2,
16,
4,
18,
6,
8,
2,
16,
6,
4,
4,
6,
4,
24,
8,
16,
4,
4,
4,
24,
2,
8,
6,
16,
2,
16,
4,
12,
8,
4,
2,
30,
4,
18,
8,
6,
4,
8,
4,
8,
16,
4,
2,
24,
4,
4,
4,
24,
8,
12,
2,
6,
4,
16,
4,
16,
2,
4,
18,
6,
2,
16,
4,
20,
4,
8,
4,
24,
8,
8,
4,
8,
4,
16,
4,
12,
6,
8,
4,
28,
4,
4,
12,
15,
4,
12,
2,
8,
8,
8,
4,
24,
4,
8,
10,
10,
4,
8,
4,
12,
4,
4,
4,
48,
2,
8,
6,
6,
6,
8,
6,
12,
6,
16,
2,
12,
4,
8,
12,
8,
4,
16,
2,
12,
12,
8,
2,
20,
4,
8,
6,
18,
2,
24,
2,
16,
8,
4,
8,
18,
2,
4,
4,
20,
4,
16,
4,
6,
16,
4,
4,
16,
4,
8,
4,
6,
4,
24,
6,
20,
4,
4,
2,
24,
4,
4,
12,
16,
8,
8,
4,
6,
4,
16,
2,
30,
2,
4,
8,
12,
6,
8,
4,
24,
9,
4,
4,
24,
4,
4,
8,
10,
2,
24,
4,
6,
8,
4,
4,
16,
2,
16,
8,
12,
2,
16,
4,
14,
16,
8,
4,
18,
4,
8,
4,
16,
2,
8,
8,
6,
6,
4,
8,
40,
4,
4,
4,
6,
6,
24,
2,
8,
4,
12,
4,
24,
4,
4,
12,
12,
2,
8,
2,
24,
4,
8,
2,
24,
8,
8,
8,
12,
4,
16,
2,
10,
12,
8,
6,
12,
2,
8,
8,
16,
4,
12,
2,
12,
8,
8,
2,
32,
2,
8,
12,
6,
2,
8,
12,
8,
8,
8,
2,
36,
4,
8,
8,
15,
4,
16,
2,
6,
12,
8,
2,
16,
2,
8,
8,
12,
8,
12,
2,
24,
4,
4,
4,
12,
6,
8,
8,
16,
2,
32,
2,
6,
4,
4,
4,
30,
8,
6,
8,
12,
2,
8,
4,
16,
12,
4,
4,
12,
2,
16,
8,
14,
2,
20,
8,
12,
4,
8,
4,
32,
4,
4,
6,
6,
8,
8,
2,
10,
8,
8,
4,
36,
4,
8,
12,
8,
2,
8,
4,
12,
8,
8,
6,
24,
4,
8,
4,
12,
2,
24,
2,
8,
12,
8,
8,
12,
2,
4,
6,
30,
2,
8,
2,
6,
16,
8,
4,
32,
3,
8,
4,
12,
4,
16,
4,
18,
6,
4,
2,
24,
8,
8,
4,
8,
6,
12,
4,
12,
8,
8,
4,
20,
2,
8,
20,
6,
2,
16,
4,
16,
4,
12,
2,
18,
4,
4,
8,
12,
8,
24,
2,
12,
6,
4,
4,
32,
2,
4,
4,
24,
2,
16,
4,
10,
8,
4,
4,
12,
4,
16,
12,
8,
6,
8,
8,
6,
8,
4,
2,
42,
4,
8,
6,
12,
4,
16,
2,
12,
8,
12,
6,
12,
4,
4,
8,
10,
2,
24,
4,
18,
4,
4,
2,
24,
8,
4,
12,
6,
2,
16,
4,
24,
4,
8,
8,
21,
2,
4,
8,
16,
4,
8,
4,
12,
18,
16,
2,
20,
4,
8,
4,
6,
4,
12,
4,
8,
8,
8,
2,
36,
4,
4,
8,
16,
8,
8,
4,
12,
4,
12,
4,
24,
2,
8,
8,
6,
2,
16,
4,
20,
12,
4,
2,
24,
4,
4,
8,
16,
2,
32,
2,
6,
4,
4,
12,
24,
4,
4,
6,
12,
4,
16,
4,
8,
8,
4,
4,
18,
6,
16,
4,
20,
4,
8,
4,
12,
10,
4,
2,
32,
2,
8,
16,
6,
4,
12,
4,
14,
8,
16,
2,
12,
4,
8,
12,
16,
4,
8,
2,
12,
8,
4,
2,
40,
9,
8,
4,
6,
4,
16,
4,
8,
6,
8,
4,
24,
2,
12,
4,
24,
2,
18,
4,
6,
16,
4,
4,
16,
2,
12,
8,
12,
4,
8,
8,
10,
4,
8,
8,
36,
2,
4,
4,
8,
4,
16,
2,
12,
12,
8,
4,
22,
4,
8,
12,
6,
4,
20,
2,
32,
8,
8,
2,
12,
4,
4,
12,
10,
2,
16,
4,
6,
4,
16,
4,
24,
4,
4,
4,
18,
4,
16,
4,
12,
16,
4,
4,
24,
2,
8,
8,
8,
4,
12,
8,
12,
4,
4,
2,
40,
2,
8,
6,
12,
6,
8,
4,
16,
8,
8,
4,
24,
4,
4,
16,
21,
2,
8,
4,
12,
6,
4,
4,
16,
8,
12,
4,
6,
4,
36,
4,
10,
4,
8,
4,
12,
8,
4,
12,
16,
4,
16,
2,
12,
8,
4,
2,
36,
2,
8,
8,
12,
4,
12,
6,
8,
6,
8,
6,
24,
2,
8,
4,
10,
12,
16,
2,
6,
4,
16,
2,
32,
4,
4,
12,
12,
4,
16,
4,
24,
8,
4,
2,
18,
4,
8,
4,
8,
2,
16,
6,
12,
16,
4,
4,
20,
2,
4,
8,
24,
2,
12,
4,
16,
12,
4,
4,
12,
2,
16,
6,
12,
4,
24,
4,
6,
8,
4,
4,
40,
4,
4,
8,
6,
8,
8,
4,
20,
9,
16,
2,
12,
2,
4,
16,
16,
2,
12,
2,
12,
4,
8,
4,
28,
4,
8,
12,
12,
4,
16,
2,
8,
4,
4,
6,
36,
4,
8,
4,
20,
4,
8,
6,
6,
12,
8,
4,
16,
8,
16,
4,
6,
4,
16,
4,
12,
8,
8,
2,
36,
2,
8,
6,
16,
4,
16,
2,
6,
4,
8,
8,
30,
2,
4,
16,
6,
4,
16,
2,
16,
10,
8,
2,
12,
12,
4,
4,
18,
2,
24,
2,
18,
8,
4,
8,
16,
4,
4,
12,
12,
4,
8,
2,
20,
8,
8,
2,
24,
4,
12,
4,
8,
4,
16,
8,
6,
6,
8,
2,
48,
2,
6,
8,
9,
4,
24,
8,
8,
4,
8,
2,
12,
2,
8,
16,
10,
4,
8,
4,
18,
12,
8,
4,
24,
4,
4,
4,
18,
2,
16,
2,
14,
12,
4,
8,
12,
4,
4,
8,
24,
4,
24,
4,
12,
8,
8,
2,
20,
4,
16,
6,
6,
2,
8,
4,
16,
8,
4,
4,
36,
4,
8,
8,
12,
6,
8,
4,
6,
8,
16,
4,
32,
2,
8,
8,
6,
4,
12,
4,
20,
8,
4,
4,
24,
8,
4,
6,
8,
2,
24,
8,
6,
4,
8,
4,
32,
2,
16,
4,
12,
2,
8,
2,
8,
24,
4,
2,
18,
2,
8,
8,
20,
4,
12,
6,
12,
8,
8,
6,
32,
3,
4,
10,
12,
8,
16,
4,
12,
4,
8,
2,
18,
4,
4,
8,
16,
4,
16,
2,
24,
6,
8,
4,
20,
4,
4,
8,
6,
6,
32,
2,
8,
4,
8,
8,
12,
2,
4,
12,
28,
4,
8,
4,
6,
12,
8,
2,
36,
2,
8,
8,
6,
2,
16,
8,
20,
8,
8,
2,
24,
2,
16,
4,
8,
4,
12,
2,
6,
12,
12,
4,
24,
8,
4,
12,
12,
2,
8,
2,
16,
4,
8,
4,
30,
8,
4,
8,
10,
4,
32,
2,
12,
6,
4,
12,
16,
6,
4,
4,
12,
2,
12,
2,
20,
8,
8,
4,
24,
4,
8,
16,
8,
2,
8,
4,
12,
8,
8,
4,
45,
4,
4,
4,
12,
8,
8,
2,
16,
6,
12,
4,
24,
2,
8,
8,
12,
2,
16,
8,
12,
8,
4,
2,
16,
8,
12,
12,
6,
4,
24,
2,
10,
8,
8,
4,
18,
2,
8,
4,
32,
4,
8,
2,
6,
14,
4,
4,
28,
4,
12,
4,
12,
4,
24,
8,
8,
8,
8,
2,
24,
4,
4,
12,
10,
4,
16,
4,
12,
4,
8,
2,
32,
2,
8,
18,
6,
2,
8,
4,
24,
6,
8,
4,
12,
8,
8,
4,
8,
8,
24,
2,
12,
4,
4,
4,
40,
2,
6,
8,
18,
2,
8,
6,
8,
16,
8,
4,
18,
2,
16,
4,
16,
4,
8,
4,
6,
12,
12,
2,
32,
3,
4,
8,
18,
6,
20,
2,
10,
8,
8,
8,
12,
2,
4,
12,
8,
4,
16,
2,
24,
8,
4,
4,
36,
8,
4,
4,
6,
4,
20,
6,
16,
8,
4,
4,
12,
6,
4,
8,
20,
2,
24,
4,
6,
8,
8,
2,
16,
2,
16,
6,
12,
8,
16,
6,
14,
4,
4,
2,
48,
4,
8,
8,
16,
4,
8,
4,
6,
6,
8,
4,
20,
2,
8,
16,
12,
2,
12,
4,
24,
8,
4,
2,
12,
4,
8,
10,
24,
4,
16,
4,
6,
8,
4,
8,
24,
4,
8,
8,
12,
2,
24,
2,
10,
18,
4,
4,
24,
4,
8,
4,
8,
2,
16,
8,
12,
4,
8,
4,
36,
4,
8,
12,
9,
4,
8,
2,
16,
4,
24,
2,
18,
2,
8,
8,
10,
8,
8,
4,
12,
16,
4,
2,
32,
4,
4,
4,
6,
4,
24,
6,
18,
4,
8,
8,
24,
2,
8,
6,
16,
2,
8,
4,
6,
16,
8,
6,
30,
2,
8,
4,
12,
4,
16,
8,
8,
6,
4,
4,
36,
4,
4,
4,
14,
8,
24,
2,
6,
4,
16,
2,
16,
8,
8,
16,
12,
2,
8,
2,
30,
4,
8,
2,
18,
6,
8,
16,
8,
2,
16,
2,
6,
12,
8,
4,
24,
4,
8,
8,
12,
4,
16,
2,
16,
8,
4,
2,
24,
4,
12,
6,
20,
4,
8,
8,
12,
4,
4,
4,
48,
4,
8,
4,
6,
8,
8,
2,
16,
15,
8,
6,
12,
4,
4,
12,
16,
4,
24,
4,
12,
4,
8,
4,
20,
4,
4,
6,
6,
2,
32,
4,
8,
8,
4,
8,
24,
4,
4,
8,
24,
2,
16,
2,
24,
12,
4,
2,
16,
4,
8,
8,
12,
2,
12,
8,
10,
8,
12,
2,
24,
2,
4,
8,
8,
12,
16,
2,
12,
8,
16,
4,
42,
4,
4,
8,
6,
4,
8,
4,
16,
6,
8,
4,
12,
4,
12,
8,
20,
2,
30,
2,
6,
8,
4,
4,
24,
2,
4,
12,
24,
4,
8,
4,
12,
8,
8,
6,
18,
4,
16,
8,
8,
2,
16,
6,
6,
8,
4,
2,
40,
8,
8,
4,
6,
8,
12,
4,
16,
8,
8,
2,
24,
2,
8,
24,
13,
4,
8,
2,
18,
4,
8,
4,
32,
4,
4,
6,
12,
4,
16,
2,
10,
6,
12,
4,
24,
4,
8,
4,
16,
4,
12,
8,
6,
16,
4,
2,
24,
2,
16,
12,
6,
2,
16,
4,
16,
8,
4,
2,
36,
4,
8,
4,
20,
4,
8,
8,
12,
6,
12,
4,
16,
2,
8,
8,
6,
2,
32,
2,
28,
8,
4,
4,
12,
12,
4,
6,
8,
4,
16,
4,
12,
8,
4,
6,
30,
2,
4,
8,
24,
4,
16,
4,
8,
16,
16,
4,
12,
4,
8,
8,
12,
4,
12,
4,
6,
4,
4,
8,
48,
2,
8,
6,
6,
6,
8,
4,
10,
8,
8,
2,
30,
4,
12,
8,
16,
2,
16,
2,
12,
12,
4,
4,
32,
9,
4,
4,
12,
2,
24,
2,
12,
8,
8,
12,
12,
4,
8,
8,
20,
2,
16,
2,
6,
8,
8,
4,
24,
4,
16,
8,
6,
2,
8,
8,
24,
12,
4,
2,
24,
2,
4,
12,
16,
4,
16,
4,
12,
4,
16,
2,
20,
2,
4,
18,
6,
8,
16,
4,
16,
4,
4,
2,
36,
4,
4,
4,
14,
2,
32,
4,
12,
10,
8,
4,
16,
2,
8,
4,
18,
8,
12,
4,
10,
16,
4,
4,
12,
4,
8,
6,
24,
4,
8,
4,
12,
4,
8,
4,
48,
4,
4,
8,
12,
6,
16,
2,
8,
12,
8,
4,
18,
4,
8,
12,
10,
2,
12,
2,
24,
4,
8,
4,
16,
8,
8,
16,
6,
2,
24,
4,
18,
4,
8,
8,
27,
2,
4,
4,
16,
6,
8,
2,
6,
12,
8,
4,
40,
4,
16,
8,
6,
2,
16,
10,
8,
4,
8,
4,
24,
4,
8,
6,
12,
4,
16,
4,
6,
16,
8,
2,
24,
4,
8,
8,
12,
2,
8,
4,
30,
8,
8,
8,
12,
4,
4,
8,
16,
2,
36,
4,
6,
4,
4,
4,
28,
4,
6,
6,
24,
2,
16,
2,
16,
12,
4,
4,
24,
4,
8,
8,
10,
8,
8,
4,
6,
12,
8,
4,
32,
2,
4,
4,
12,
8,
24,
2,
12,
4,
12,
2,
24,
4,
8,
20,
8,
2,
8,
8,
12,
4,
8,
2,
30,
8,
16,
4,
6,
4,
16,
4,
16,
12,
4,
6,
12,
6,
4,
4,
32,
2,
16,
2,
12,
16,
4,
4,
32,
3,
8,
6,
6,
2,
16,
8,
10,
4,
8,
4,
36,
4,
4,
8,
8,
8,
8,
2,
18,
8,
16,
4,
24,
2,
8,
16,
6,
2,
12,
2,
16,
8,
16,
2,
24,
6,
8,
6,
10,
4,
16,
4,
12,
4,
4,
4,
40,
4,
4,
8,
12,
4,
8,
8,
14,
12,
4,
2,
12,
2,
24,
8,
8,
4,
24,
4,
12,
12,
8,
4,
40,
2,
4,
12,
12,
8,
8,
2,
8,
4,
8,
4,
18,
4,
4,
12,
24,
4,
16,
4,
12,
6,
8,
2,
16,
8,
4,
8,
12,
4,
32,
2,
20,
4,
4,
4,
12,
2,
12,
12,
24,
4,
16,
2,
6,
8,
12,
4,
30,
4,
8,
8,
6,
4,
8,
8,
8,
12,
4,
4,
48,
2,
4,
8,
15,
8,
12,
4,
12,
4,
8,
4,
16,
4,
8,
12,
12,
2,
8,
2,
24,
16,
8,
2,
24,
4,
8,
4,
16,
2,
24,
2,
6,
12,
8,
12,
20,
2,
8,
4,
12,
4,
24,
2,
16,
8,
4,
4,
12,
8,
8,
8,
14,
2,
16,
12,
12,
4,
4,
2,
48,
4,
4,
8,
6,
4,
16,
4,
10,
6,
16,
2,
24,
6,
4,
8,
8,
8,
20,
4,
18,
4,
4,
2,
36,
4,
8,
6,
12,
4,
16,
4,
16,
4,
4,
8,
18,
4,
8,
12,
20,
2,
8,
2,
6,
24,
8,
4,
16,
2,
16,
8,
18,
2,
12,
4,
16,
4,
8,
4,
24,
4,
4,
12,
8,
8,
16,
4,
6,
4,
16,
2,
40,
6,
4,
8,
12,
4,
16,
2,
32,
9,
4,
4,
12,
4,
4,
8,
12,
4,
24,
4,
6,
8,
16,
6,
16,
4,
4,
10,
12,
4,
8,
2,
20,
16,
4,
2,
36,
2,
8,
4,
8,
2,
16,
8,
12,
12,
4,
2,
42,
2,
10,
4,
6,
6,
16,
8,
8,
8,
16,
4,
12,
2,
8,
12,
20,
2,
16,
4,
12,
4,
4,
8,
24,
6,
8,
4,
12,
4,
32,
2,
12,
8,
4,
4,
24,
4,
8,
4,
24,
4,
12,
4,
12,
16,
4,
4,
20,
4,
12,
18,
6,
4,
8,
4,
8,
4,
8,
4,
36,
2,
16,
4,
18,
8,
8,
4,
6,
6,
8,
2,
32,
4,
4,
16,
12,
2,
12,
8,
20,
4,
4,
4,
24,
4,
8,
8,
16,
2,
16,
4,
6,
8,
4,
8,
36,
4,
8,
8,
27,
6,
16,
2,
8,
12,
8,
4,
12,
2,
8,
4,
10,
4,
32,
4,
6,
8,
4,
2,
32,
8,
8,
6,
6,
6,
8,
4,
28,
8,
16,
2,
18,
2,
4,
16,
8,
2,
8,
4,
24,
10,
8,
2,
20,
8,
4,
8,
6,
6,
36,
2,
8,
8,
4,
4,
24,
2,
8,
12,
24,
6,
8,
4,
12,
8,
8,
2,
32,
2,
16,
4,
12,
2,
8,
6,
10,
12,
8,
4,
24,
4,
8,
8,
16,
4,
12,
2,
12,
4,
8,
8,
32,
2,
8,
16,
6,
4,
24,
2,
20,
4,
8,
2,
18,
16,
4,
4,
10,
2,
16,
2,
12,
6,
8,
8,
32,
4,
8,
8,
12,
2,
20,
2,
12,
12,
8,
4,
12,
4,
8,
12,
16,
4,
8,
8,
6,
8,
8,
2,
60,
3,
4,
6,
12,
4,
12,
6,
8,
16,
12,
2,
12,
4,
12,
8,
14,
4,
12,
2,
24,
8,
4,
4,
16,
4,
8,
6,
12,
4,
24,
4,
10,
8,
8,
12,
24,
2,
4,
4,
16,
2,
24,
8,
12,
12,
4,
2,
24,
4,
8,
4,
12,
4,
12,
4,
24,
4,
4,
2,
36,
2,
4,
14,
20,
4,
16,
2,
6,
8,
16,
4,
24,
2,
4,
16,
6,
8,
8,
2,
22,
6,
8,
4,
24,
8,
8,
4,
8,
4,
32,
4,
6,
8,
8,
8,
20,
4,
8,
6,
12,
4,
8,
4,
8,
16,
8,
2,
36,
4,
12,
8,
24,
2,
8,
4,
6,
8,
4,
8,
32,
4,
8,
4,
6,
4,
24,
2,
20,
4,
16,
2,
12,
4,
8,
18,
8,
4,
8,
2,
24,
8,
4,
4,
35,
8,
4,
16,
6,
2,
16,
4,
16,
6,
12,
4,
12,
2,
8,
4,
30,
4,
18,
6,
6,
8,
8,
4,
32,
2,
8,
8,
6,
4,
16,
8,
12,
8,
4,
4,
36,
4,
8,
4,
8,
12,
16,
2,
6,
12,
8,
2,
20,
2,
4,
8,
24,
2,
16,
6,
16,
4,
4,
6,
24,
4,
8,
12,
16,
4,
32,
4,
12,
8,
8,
4,
24,
4,
8,
4,
12,
2,
8,
4,
20,
20,
4,
4,
12,
4,
16,
8,
8,
2,
12,
6,
6,
4,
16,
2,
48,
2,
8,
6,
6,
8,
8,
4,
8,
8,
12,
8,
36,
4,
4,
8,
10,
2,
8,
4,
18,
12,
8,
2,
32,
4,
8,
8,
6,
2,
24,
4,
14,
16,
4,
4,
12,
4,
4,
8,
32,
4,
8,
2,
12,
12,
4,
4,
30,
3,
16,
4,
12,
2,
16,
8,
16,
6,
8,
4,
24,
6,
4,
8,
12,
4,
24,
2,
12,
4,
12,
2,
16,
4,
4,
24,
12,
4,
16,
4,
20,
4,
8,
4,
18,
8,
4,
4,
16,
8,
16,
4,
12,
8,
4,
8,
36,
4,
4,
8,
12,
2,
24,
4,
8,
8,
4,
2,
12,
4,
24,
6,
10,
2,
16,
8,
12,
8,
4,
2,
48,
4,
8,
4,
12,
8,
16,
2,
18,
6,
8,
4,
24,
2,
4,
12,
8,
2,
24,
2,
12,
8,
4,
8,
20,
12,
4,
10,
12,
4,
16,
2,
16,
4,
16,
4,
18,
2,
4,
12,
28,
2,
8,
2,
6,
18,
8,
4,
16,
2,
12,
8,
12,
8,
16,
4,
20,
8,
4,
4,
48,
4,
4,
6,
8,
4,
8,
8,
6,
4,
8,
2,
36,
4,
16,
12,
9,
2,
16,
2,
16,
16,
4,
2,
12,
4,
8,
8,
20,
4,
24,
6,
6,
4,
8,
8,
16,
4,
4,
12,
24,
2,
16,
2,
16,
8,
4,
2,
30,
4,
16,
8,
16,
4,
8,
4,
12,
6,
8,
2,
40,
2,
8,
8,
6,
12,
12,
2,
8,
8,
16,
2,
12,
4,
4,
16,
12,
6,
16,
4,
12,
4,
8,
4,
48,
4,
8,
6,
12,
4,
24,
8,
10,
6,
4,
8,
12,
2,
8,
8,
16,
4,
16,
2,
12,
16,
12,
4,
28,
2,
8,
6,
12,
2,
8,
6,
16,
12,
4,
4,
36,
2,
4,
4,
10,
4,
24,
4,
12,
12,
16,
2,
16,
8,
4,
8,
6,
4,
12,
4,
36,
4,
4,
4,
12,
8,
4,
12,
8,
4,
32,
4,
12,
4,
8,
4,
40,
4,
6,
4,
12,
8,
8,
2,
16,
15,
8,
4,
24,
4,
8,
4,
20,
4,
12,
12,
6,
4,
4,
2,
32,
2,
16,
16,
12,
4,
8,
2,
10,
8,
12,
2,
18,
2,
8,
16,
16,
2,
16,
2,
12,
12,
8,
4,
24,
8,
4,
4,
12,
2,
40,
4,
8,
8,
4,
6,
24,
4,
8,
6,
20,
8,
8,
2,
18,
8,
4,
6,
24,
2,
8,
8,
6,
2,
16,
8,
14,
8,
16,
4,
36,
2,
4,
4,
16,
8,
12,
4,
6,
8,
8,
2,
40,
4,
4,
12,
6,
2,
8,
8,
32,
4,
4,
4,
24,
6,
8,
8,
12,
4,
16,
4,
6,
18,
8,
8,
16,
2,
8,
4,
24,
2,
24,
2,
10,
8,
12,
4,
12,
2,
16,
10,
8,
4,
16,
4,
6,
8,
4,
4,
48,
4,
8,
8,
12,
4,
12,
4,
16,
6,
8,
4,
24,
4,
4,
24,
15,
4,
16,
2,
18,
8,
12,
2,
16,
8,
8,
6,
6,
4,
16,
2,
12,
4,
4,
8,
36,
8,
8,
4,
24,
2,
8,
4,
6,
16,
4,
2,
30,
4,
16,
8,
6,
2,
24,
4,
8,
8,
4,
6,
24,
2,
8,
6,
28,
6,
8,
2,
12,
8,
16,
8,
28,
4,
4,
8,
6,
4,
16,
2,
20,
12,
8,
2,
12,
8,
8,
4,
16,
2,
36,
2,
24,
4,
4,
4,
24,
2,
8,
16,
12,
2,
8,
8,
8,
16,
8,
2,
18,
2,
8,
8,
10,
4,
16,
8,
12,
6,
4,
2,
48,
2,
8,
8,
6,
8,
16,
6,
18,
8,
16,
4,
12,
4,
8,
12,
16,
2,
8,
4,
18,
8,
8,
2,
30,
4,
4,
8,
12,
4,
16,
4,
8,
10,
4,
12,
24,
4,
8,
4,
24,
4,
24,
2,
6,
12,
4,
2,
32,
9,
8,
6,
6,
4,
16,
4,
20,
4,
4,
2,
48,
4,
4,
8,
8,
8,
8,
4,
6,
6,
24,
4,
28,
2,
8,
8,
6,
8,
12,
4,
16,
4,
8,
4,
24,
4,
8,
16,
10,
4,
16,
4,
6,
8,
8,
6,
24,
4,
12,
4,
24,
2,
8,
4,
24,
24,
8,
2,
12,
4,
8,
4,
16,
4,
20,
8,
6,
4,
4,
4,
40,
4,
4,
12,
12,
4,
32,
2,
8,
4,
8,
2,
18,
4,
8,
8,
16,
4,
16,
4,
24,
8,
4,
4,
16,
6,
8,
12,
12,
2,
24,
4,
20,
4,
8,
8,
12,
2,
4,
12,
16,
4,
16,
2,
6,
16,
4,
2,
48,
4,
18,
4,
12,
2,
8,
8,
8,
6,
8,
4,
24,
8,
8,
8,
10,
4,
12,
2,
12,
12,
8,
4,
32,
2,
4,
18,
18,
4,
8,
2,
28,
4,
4,
8,
27,
4,
8,
4,
8,
2,
32,
2,
6,
6,
8,
8,
20,
8,
4,
8,
18,
2,
16,
4,
16,
16,
8,
4,
12,
4,
16,
12,
12,
2,
8,
4,
12,
4,
16,
4,
48,
2,
4,
8,
6,
12,
8,
4,
10,
8,
8,
2,
24,
2,
4,
8,
16,
6,
24,
4,
12,
8,
8,
2,
24,
4,
8,
6,
12,
8,
24,
2,
8,
8,
8,
4,
30,
4,
4,
4,
40,
4,
16,
2,
12,
12,
4,
4,
16,
4,
8,
12,
6,
2,
24,
12,
12,
8,
4,
4,
24,
4,
8,
8,
8,
4,
8,
4,
24,
4,
8,
4,
30,
4,
8,
16,
6,
2,
8,
2,
24,
12,
8,
2,
24,
8,
8,
4,
14,
4,
32,
2,
6,
8,
8,
8,
32,
2,
4,
6,
12,
2,
16,
6,
10,
12,
8,
4,
18,
2,
16,
8,
16,
4,
8,
8,
6,
20,
4,
4,
48,
3,
4,
4,
12,
4,
12,
2,
16,
4,
12,
8,
12,
6,
8,
12,
20,
2,
16,
4,
12,
4,
8,
2,
32,
8,
8,
4,
6,
2,
32,
2,
24,
12,
4,
6,
12,
2,
8,
16,
16,
4,
12,
4,
6,
8,
8,
2,
20,
4,
16,
8,
18,
8,
8,
4,
8,
4,
8,
2,
54,
2,
8,
8,
12,
8,
8,
8,
12,
6,
8,
2,
16,
4,
16,
8,
6,
2,
24,
4,
20,
12,
8,
2,
24,
12,
4,
12,
16,
2,
16,
4,
6,
4,
4,
8,
42,
2,
4,
4,
12,
4,
16,
2,
16,
16,
8,
4,
18,
4,
12,
8,
10,
2,
12,
8,
12,
8,
12,
2,
32,
2,
4,
12,
12,
8,
8,
2,
12,
8,
24,
4,
24,
2,
4,
16,
8,
4,
8,
2,
24,
6,
4,
4,
40,
4,
8,
4,
6,
2,
24,
8,
16,
4,
8,
4,
24,
2,
8,
10,
27,
4,
16,
4,
6,
16,
4,
4,
24,
8,
8,
4,
12,
6,
8,
4,
10,
12,
4,
6,
24,
2,
12,
4,
16,
6,
32,
2,
6,
4,
8,
4,
24,
4,
4,
24,
6,
4,
16,
4,
32,
8,
4,
4,
18,
4,
8,
8,
20,
2,
24,
2,
6,
8,
8,
4,
16,
4,
4,
4,
24,
8,
12,
4,
14,
8,
8,
4,
36,
2,
8,
6,
8,
2,
16,
12,
6,
8,
8,
8,
50,
2,
8,
4,
6,
4,
16,
4,
8,
12,
16,
2,
12,
4,
8,
8,
24,
4,
18,
4,
24,
8,
4,
4,
16,
4,
4,
8,
6,
4,
32,
4,
20,
8,
4,
4,
18,
8,
4,
8,
16,
2,
8,
4,
12,
18,
8,
4,
32,
2,
8,
8,
12,
4,
24,
4,
16,
4,
8,
4,
24,
4,
4,
6,
10,
16,
8,
2,
6,
8,
12,
2,
48,
2,
8,
16,
12,
4,
8,
4,
24,
9,
8,
2,
12,
8,
12,
8,
8,
2,
24,
2,
12,
8,
8,
6,
20,
2,
16,
12,
24,
2,
8,
4,
8,
8,
8,
4,
24,
4,
8,
8,
14,
4,
16,
4,
12,
6,
4,
2,
48,
8,
4,
8,
12,
4,
12,
2,
20,
4,
8,
4,
24,
4,
4,
24,
8,
4,
8,
2,
12,
4,
16,
4,
36,
8,
4,
6,
6,
4,
32,
4,
8,
12,
8,
4,
24,
2,
4,
4,
20,
4,
20,
8,
12,
8,
4,
6,
16,
4,
24,
6,
6,
2,
8,
8,
20,
8,
4,
2,
36,
2,
4,
4,
24,
8,
16,
4,
6,
16,
16,
4,
20,
2,
8,
12,
6,
4,
24,
2,
16,
8,
8,
4,
12,
8,
4,
6,
24,
2,
16,
2,
12,
8,
4,
8,
32,
4,
8,
16,
18,
2,
8,
2,
10,
12,
8,
4,
24,
2,
16,
4,
8,
6,
12,
8,
12,
4,
4,
2,
56,
8,
4,
10,
9,
6,
16,
6,
12,
4,
8,
4,
36,
2,
16,
8,
10,
2,
8,
4,
12,
12,
4,
4,
16,
8,
4,
8,
12,
4,
32,
4,
12,
4,
8,
8,
12,
4,
8,
6,
24,
2,
24,
2,
12,
16,
8,
4,
30,
4,
8,
8,
6,
4,
8,
6,
24,
8,
4,
2,
24,
2,
4,
16,
16,
8,
24,
4,
6,
8,
16,
2,
16,
2,
8,
12,
6,
4,
16,
4,
30,
4,
8,
2,
36,
4,
8,
4,
16,
4,
16,
6,
12,
6,
4,
8,
24,
4,
8,
4,
24,
4,
12,
2,
8,
24,
4,
2,
12,
2,
8,
16,
20,
2,
16,
4,
6,
8,
8,
4,
48,
2,
8,
4,
12,
6,
16,
4,
14,
6,
12,
8,
12,
8,
8,
8,
8,
2,
16,
4,
24,
4,
8,
2,
40,
4,
4,
12,
12,
2,
16,
2,
8,
8,
8,
10,
18,
6,
8,
4,
24,
4,
16,
2,
6,
20,
8,
4,
32,
3,
16,
4,
6,
4,
12,
8,
10,
12,
4,
2,
36,
4,
16,
12,
8,
4,
8,
2,
12,
12,
8,
2,
36,
4,
4,
8,
24,
2,
8,
8,
16,
6,
4,
8,
12,
6,
4,
4,
10,
6,
48,
4,
6,
4,
4,
8,
24,
4,
4,
8,
12,
4,
16,
4,
24,
8,
8,
2,
18,
2,
12,
8,
16,
4,
16,
8,
12,
6,
12,
2,
40,
2,
6,
8,
6,
8,
20,
2,
16,
8,
16,
2,
24,
4,
8,
18,
14,
2,
8,
4,
12,
8,
4,
2,
24,
8,
8,
8,
6,
4,
16,
2,
20,
16,
8,
4,
24,
2,
4,
4,
32,
2,
12,
4,
12,
8,
8,
12,
24,
4,
8,
12,
6,
2,
16,
8,
8,
4,
12,
2,
48,
8,
4,
4,
10,
6,
8,
2,
12,
12,
16,
4,
16,
4,
4,
16,
6,
4,
24,
2,
32,
4,
8,
2,
12,
4,
8,
12,
8,
8,
24,
4,
12,
4,
4,
8,
45,
2,
4,
8,
12,
4,
16,
4,
8,
12,
4,
4,
24,
2,
16,
4,
24,
4,
16,
6,
12,
8,
4,
2,
32,
4,
4,
6,
24,
8,
8,
4,
10,
8,
8,
4,
18,
4,
4,
16,
8,
4,
24,
4,
18,
8,
8,
2,
28,
12,
16,
8,
6,
2,
24,
4,
16,
4,
4,
4,
12,
4,
4,
12,
20,
2,
8,
4,
12,
16,
8,
2,
40,
2,
16,
4,
6,
4,
16,
4,
12,
12,
8,
6,
48,
4,
4,
4,
16,
4,
12,
4,
6,
4,
24,
2,
20,
4,
12,
16,
6,
4,
8,
2,
16,
16,
4,
8,
18,
4,
4,
4,
22,
4,
16,
4,
12,
6,
8,
12,
32,
2,
8,
4,
12,
4,
32,
4,
10,
8,
4,
2,
12,
8,
8,
12,
16,
2,
16,
4,
12,
4,
8,
4,
54,
4,
8,
10,
6,
8,
8,
2,
16,
10,
16,
2,
12,
2,
4,
16,
20,
4,
12,
2,
18,
8,
8,
4,
32,
9,
4,
12,
12,
2,
16,
4,
14,
4,
4,
4,
24,
2,
16,
8,
16,
4,
16,
2,
6,
24,
4,
2,
20,
4,
16,
4,
18,
2,
24,
4,
8,
8,
8,
8,
36,
4,
4,
8,
12,
4,
16,
6,
12,
4,
8,
4,
24,
4,
4,
12,
12,
4,
8,
4,
40,
6,
8,
2,
12,
8,
4,
8,
8,
4,
28,
4,
6,
16,
8,
4,
32,
2,
8,
6,
18,
6,
8,
4,
16,
8,
8,
2,
36,
2,
16,
4,
10,
4,
16,
16,
12,
8,
4,
4,
32,
2,
8,
4,
6,
6,
24,
4,
12,
8,
8,
2,
24,
2,
8,
12,
16,
8,
8,
4,
12,
4,
4,
4,
40,
8,
4,
8,
12,
2,
36,
2,
8,
12,
4,
4,
12,
4,
8,
8,
28,
4,
12,
4,
12,
8,
8,
4,
16,
2,
16,
20,
12,
4,
8,
8,
10,
4,
16,
4,
36,
6,
4,
8,
16,
8,
8,
4,
6,
6,
8,
4,
48,
2,
4,
16,
9,
4,
16,
6,
24,
4,
4,
4,
12,
4,
12,
6,
10,
4,
32,
2,
12,
8,
8,
4,
24,
2,
4,
4,
24,
4,
8,
4,
18,
24,
8,
4,
12,
8,
8,
4,
8,
2,
24,
4,
18,
8,
4,
4,
40,
4,
6,
6,
6,
4,
16,
4,
24,
8,
12,
2,
30,
4,
4,
16,
12,
2,
16,
2,
12,
6,
16,
4,
16,
4,
4,
8,
6,
8,
24,
4,
10,
8,
8,
12,
24,
2,
4,
8,
32,
2,
16,
4,
6,
8,
8,
2,
42,
2,
16,
8,
6,
4,
8,
4,
8,
18,
8,
2,
30,
4,
12,
8,
20,
8,
16,
2,
6,
4,
8,
8,
16,
4,
12,
12,
6,
2,
16,
4,
24,
8,
4,
2,
36,
12,
8,
8,
8,
2,
16,
4,
12,
12,
4,
8,
20,
2,
4,
8,
24,
2,
12,
4,
16,
8,
16,
2,
24,
2,
12,
6,
16,
8,
8,
4,
6,
8,
4,
2,
64,
2,
8,
4,
12,
8,
16,
8,
20,
9,
8,
4,
12,
2,
8,
12,
8,
2,
12,
8,
12,
12,
8,
2,
24,
8,
4,
8,
12,
2,
32,
2,
16,
4,
4,
12,
18,
4,
8,
8,
30,
4,
16,
2,
6,
18,
4,
2,
16,
4,
8,
8,
12,
4,
20,
4,
28,
4,
8,
4,
24,
2,
8,
18,
8,
8,
16,
4,
6,
4,
16,
4,
30,
4,
8,
8,
12,
4,
16,
2,
16,
8,
4,
2,
36,
8,
4,
4,
12,
2,
36,
4,
6,
4,
8,
4,
32,
8,
8,
12,
12,
4,
8,
4,
10,
16,
4,
8,
24,
2,
16,
4,
16,
2,
8,
6,
12,
6,
8,
4,
40,
2,
8,
8,
12,
8,
24,
2,
12,
8,
8,
2,
12,
6,
4,
20,
20,
4,
8,
2,
36,
8,
4,
2,
24,
8,
4,
8,
12,
4,
16,
4,
12,
6,
16,
4,
12,
2,
8,
8,
16,
4,
32,
2,
6,
12,
4,
2,
40,
4,
8,
6,
6,
8,
8,
16,
8,
4,
8,
4,
36,
2,
12,
8,
21,
4,
8,
4,
12,
16,
16,
4,
32,
2,
4,
16,
12,
2,
12,
2,
20,
8,
4,
4,
12,
4,
8,
6,
8,
4,
32,
4,
12,
4,
12,
6,
36,
8,
4,
4,
12,
4,
8,
4,
16,
12,
8,
4,
24,
2,
16,
12,
10,
2,
12,
4,
6,
8,
8,
4,
48,
4,
8,
12,
6,
8,
8,
4,
16,
8,
16,
4,
36,
4,
4,
8,
8,
2,
8,
4,
24,
12,
4,
2,
20,
6,
16,
4,
12,
2,
32,
4,
16,
8,
4,
4,
12,
4,
4,
12,
36,
2,
8,
8,
12,
8,
4,
8,
24,
4,
12,
4,
12,
2,
32,
4,
10,
10,
4,
4,
24,
4,
4,
4,
8,
12,
24,
2,
12,
8,
8,
4,
28,
2,
8,
24,
12,
2,
16,
2,
16,
8,
8,
2,
24,
8,
4,
8,
20,
8,
16,
4,
6,
6,
4,
4,
32,
4,
8,
4,
18,
2,
12,
4,
24,
16,
8,
2,
12,
4,
16,
8,
16,
4,
8,
4,
6,
16,
8,
2,
60,
3,
8,
8,
12,
6,
8,
2,
8,
6,
16,
8,
12,
2,
4,
12,
18,
2,
30,
4,
12,
4,
12,
6,
16,
8,
8,
6,
6,
2,
24,
2,
20,
8,
8,
8,
36,
4,
8,
8,
16,
4,
8,
2,
12,
16,
8,
4,
24,
4,
8,
4,
6,
8,
12,
12,
8,
4,
4,
4,
48,
4,
8,
6,
10,
4,
16,
6,
6,
4,
16,
4,
32,
2,
8,
16,
6,
4,
16,
4,
28,
12,
4,
4,
24,
4,
4,
8,
32,
2,
24,
2,
6,
4,
4,
8,
20,
2,
8,
14,
12,
4,
16,
4,
16,
12,
4,
4,
18,
8,
16,
4,
12,
4,
16,
4,
18,
12,
4,
2,
32,
8,
4,
8,
6,
4,
16,
4,
10,
4,
24,
4,
24,
2,
4,
12,
16,
4,
16,
2,
24,
4,
8,
4,
48,
4,
8,
4,
6,
2,
16,
4,
8,
16,
8,
12,
12,
4,
8,
4,
20,
2,
12,
4,
12,
24,
8,
2,
16,
2,
8,
12,
18,
2,
16,
4,
24,
4,
4,
8,
45,
2,
4,
8,
8,
4,
16,
6,
6,
12,
8,
2,
30,
8,
4,
8,
6,
2,
24,
4,
32,
4,
8,
2,
12,
10,
8,
16,
14,
4,
16,
4,
12,
4,
12,
4,
24,
4,
8,
4,
24,
4,
16,
4,
10,
12,
4,
2,
24,
4,
12,
16,
8,
4,
16,
8,
6,
4,
4,
4,
48,
2,
16,
6,
12,
8,
8,
2,
8,
8,
16,
2,
18,
4,
8,
12,
20,
8,
16,
2,
12,
10,
4,
6,
32,
4,
4,
4,
12,
4,
48,
2,
14,
4,
8,
8,
12,
4,
4,
6,
24,
4,
8,
4,
12,
8,
8,
4,
40,
2,
8,
16,
6,
4,
12,
8,
16,
12,
8,
2,
24,
2,
4,
4,
12,
12,
12,
4,
18,
8,
8,
2,
32,
2,
8,
16,
12,
2,
8,
8,
20,
8,
8,
2,
18,
8,
16,
4,
8,
4,
32,
4,
6,
12,
4,
8,
28,
4,
4,
4,
24,
4,
24,
2,
8,
16,
4,
4,
24,
2,
8,
6,
20,
2,
16,
6,
6,
8,
4,
4,
48,
9,
8,
8,
12,
4,
8,
2,
24,
8,
8,
2,
12,
2,
16,
16,
16,
2,
12,
4,
18,
4,
8,
6,
20,
8,
4,
12,
12,
4,
16,
2,
8,
8,
4,
4,
48,
2,
4,
8,
32,
4,
16,
8,
6,
18,
8,
4,
16,
2,
24,
4,
6,
4,
12,
4,
10,
8,
8,
4,
24,
4,
8,
10,
16,
4,
16,
4,
6,
12,
12,
4,
36,
2,
4,
8,
6,
4,
16,
4,
32,
6,
8,
2,
24,
8,
8,
4,
10,
2,
32,
4,
24,
4,
8,
8,
16,
2,
8,
18,
12,
6,
16,
4,
14,
16,
8,
2,
18,
2,
8,
4,
8,
8,
8,
8,
6,
8,
16,
4,
60,
4,
4,
4,
12,
6,
12,
4,
8,
4,
12,
4,
12,
4,
8,
24,
12,
4,
16,
2,
12,
8,
4,
2,
40,
6,
8,
6,
18,
2,
16,
2,
20,
6,
4,
8,
24,
8,
4,
8,
16,
4,
24,
2,
6,
8,
8,
2,
36,
8,
18,
8,
6,
4,
8,
8,
16,
4,
4,
4,
36,
2,
4,
16,
15,
4,
16,
2,
12,
6,
24,
4,
16,
4,
8,
12,
12,
6,
16,
4,
24,
8,
4,
4,
24,
4,
4,
12,
8,
4,
16,
4,
12,
8,
8,
4,
30,
4,
8,
4,
24,
2,
16,
4,
8,
24,
4,
4,
12,
4,
16,
4,
28,
2,
24,
8,
6,
8,
4,
4,
32,
2,
4,
6,
6,
12,
24,
2,
20,
4,
8,
4,
24,
8,
8,
8,
16,
2,
8,
2,
24,
12,
4,
2,
24,
4,
4,
16,
6,
4,
36,
4,
8,
4,
16,
8,
24,
4,
8,
8,
20,
4,
8,
2,
6,
8,
4,
4,
48,
8,
8,
4,
6,
2,
8,
12,
16,
6,
4,
4,
48,
2,
8,
4,
16,
8,
20,
4,
12,
8,
8,
6,
20,
4,
4,
12,
12,
2,
8,
2,
24,
8,
16,
4,
18,
4,
8,
8,
12,
2,
32,
4,
6,
16,
8,
4,
16,
4,
8,
12,
12,
4,
12,
2,
30,
16,
8,
2,
12,
2,
8,
12,
16,
4,
8,
8,
12,
4,
8,
4,
56,
2,
8,
8,
6,
16,
16,
2,
16,
9,
12,
4,
24,
4,
4,
8,
10,
4,
24,
4,
12,
4,
8,
2,
24,
4,
8,
10,
12,
2,
24,
8,
12,
12,
4,
6,
18,
2,
4,
8,
32,
2,
8,
4,
12,
12,
8,
8,
20,
2,
16,
4,
12,
2,
32,
8,
8,
8,
4,
2,
36,
8,
8,
6,
20,
4,
8,
2,
12,
4,
16,
4,
36,
2,
4,
16,
6,
4,
8,
2,
20,
16,
12,
8,
12,
6,
4,
4,
8,
8,
24,
2,
12,
8,
8,
4,
48,
2,
8,
6,
24,
2,
16,
4,
8,
16,
4,
2,
24,
4,
20,
4,
10,
2,
8,
8,
12,
12,
8,
4,
32,
2,
8,
8,
12,
4,
12,
4,
14,
8,
8,
6,
24,
4,
8,
24,
8,
4,
32,
2,
12,
4,
4,
2,
30,
8,
8,
8,
12,
8,
16,
4,
16,
6,
4,
4,
12,
4,
8,
8,
36,
4,
16,
2,
12,
8,
16,
2,
16,
4,
8,
12,
6,
4,
16,
8,
20,
4,
4,
2,
54,
2,
8,
8,
8,
6,
8,
8,
6,
10,
8,
2,
32,
6,
8,
16,
9,
2,
12,
2,
32,
8,
4,
4,
24,
8,
4,
6,
20,
2,
24,
4,
6,
8,
8,
16,
32,
4,
8,
4,
12,
2,
16,
2,
12,
12,
16,
2,
12,
6,
8,
4,
8,
4,
24,
8,
12,
8,
8,
4,
40,
4,
4,
16,
6,
4,
8,
2,
16,
4,
16,
4,
36,
2,
4,
8,
14,
8,
8,
4,
18,
12,
4,
4,
32,
8,
8,
4,
12,
4,
40,
8,
10,
4,
4,
4,
12,
4,
16,
6,
16,
4,
8,
2,
12,
24,
4,
4,
36,
2,
16,
8,
24,
2,
8,
4,
8,
8,
8,
4,
24,
2,
8,
8,
20,
4,
24,
4,
6,
8,
12,
2,
16,
4,
12,
12,
6,
6,
8,
6,
36,
8,
4,
2,
24,
8,
4,
12,
16,
2,
32,
2,
6,
6,
8,
6,
40,
4,
6,
8,
12,
4,
12,
4,
8,
8,
4,
8,
24,
4,
16,
12,
12,
6,
8,
8,
12,
4,
8,
2,
48,
2,
8,
4,
6,
4,
16,
2,
10,
24,
16,
2,
12,
2,
4,
8,
24,
4,
16,
4,
24,
8,
8,
4,
28,
9,
4,
12,
12,
2,
32,
4,
8,
4,
4,
8,
18,
4,
4,
8,
20,
2,
16,
2,
24,
16,
4,
4,
32,
2,
12,
8,
12,
4,
12,
4,
12,
4,
8,
2,
24,
8,
8,
12,
16,
12,
8,
2,
6,
4,
8,
4,
50,
4,
8,
18,
6,
4,
16,
4,
16,
6,
8,
4,
12,
8,
16,
8,
16,
4,
24,
2,
6,
8,
4,
8,
16,
4,
4,
8,
36,
4,
16,
2,
10,
8,
8,
4,
36,
2,
8,
4,
16,
4,
24,
4,
12,
6,
8,
4,
48,
4,
4,
4,
6,
8,
24,
2,
16,
8,
16,
4,
12,
2,
4,
24,
10,
2,
8,
8,
12,
8,
8,
4,
24,
8,
8,
4,
6,
4,
24,
2,
28,
10,
8,
4,
24,
2,
8,
8,
16,
2,
12,
12,
12,
16,
4,
4,
20,
4,
16,
6,
6,
2,
16,
6,
16,
16,
8,
4,
48,
2,
4,
4,
24,
8,
8,
2,
6,
6,
8,
8,
16,
4,
4,
8,
18,
4,
24,
2,
30,
4,
8,
2,
24,
8,
4,
16,
8,
2,
16,
4,
18,
8,
8,
8,
33,
4,
8,
8,
12,
2,
16,
4,
8,
18,
8,
2,
12,
4,
16,
8,
10,
4,
24,
4,
6,
4,
8,
2,
64,
2,
4,
12,
6,
6,
16,
4,
18,
4,
16,
6,
18,
4,
8,
8,
16,
2,
8,
4,
12,
16,
8,
4,
20,
8,
8,
4,
12,
8,
24,
4,
16,
8,
4,
12,
12,
2,
4,
6,
28,
2,
32,
2,
12,
8,
4,
4,
32,
4,
8,
8,
12,
2,
8,
12,
20,
6,
4,
4,
36,
4,
4,
8,
8,
4,
24,
4,
12,
8,
24,
2,
24,
4,
4,
20,
12,
8,
8,
2,
16,
8,
8,
2,
36,
6,
4,
4,
20,
4,
16,
8,
6,
12,
8,
4,
16,
2,
16,
8,
12,
2,
16,
2,
16,
16,
4,
4,
24,
2,
24,
6,
16,
4,
8,
4,
6,
4,
4,
6,
60,
8,
8,
4,
6,
4,
16,
8,
8,
8,
8,
2,
24,
8,
8,
12,
12,
2,
12,
4,
24,
8,
4,
4,
32,
4,
12,
12,
6,
4,
16,
2,
10,
8,
16,
4,
30,
2,
8,
8,
24,
8,
8,
2,
6,
24,
4,
4,
42,
3,
8,
4,
12,
2,
12,
8,
16,
8,
8,
2,
24,
2,
8,
8,
20,
12,
8,
4,
6,
8,
16,
2,
24,
2,
8,
16,
12,
2,
24,
2,
24,
6,
4,
8,
12,
4,
4,
8,
8,
4,
48,
4,
12,
8,
8,
8,
20,
6,
4,
6,
24,
2,
16,
2,
24,
8,
4,
2,
18,
4,
8,
16,
18,
2,
8,
6,
12,
14,
8,
2,
32,
4,
8,
8,
6,
8,
24,
4,
10,
4,
16,
2,
24,
4,
8,
12,
8,
2,
8,
8,
24,
4,
4,
8,
48,
4,
12,
4,
6,
4,
16,
2,
16,
12,
8,
8,
24,
4,
4,
8,
40,
2,
18,
4,
6,
12,
8,
4,
16,
4,
8,
8,
6,
2,
16,
4,
14,
12,
8,
2,
36,
8,
8,
4,
8,
8,
16,
2,
24,
6,
12,
2,
20,
4,
8,
24,
6,
4,
20,
6,
16,
4,
8,
4,
12,
4,
4,
6,
24,
4,
32,
4,
6,
4,
4,
6,
48,
4,
4,
8,
12,
8,
8,
6,
10,
16,
4,
2,
24,
4,
16,
8,
16,
4,
24,
8,
6,
8,
4,
4,
48,
2,
4,
12,
15,
8,
8,
4,
8,
4,
12,
4,
24,
2,
16,
8,
10,
4,
16,
2,
24,
6,
8,
2,
16,
16,
4,
4,
12,
2,
24,
2,
24,
12,
4,
8,
24,
4,
8,
20,
16,
4,
8,
2,
6,
8,
16,
4,
30,
2,
12,
4,
12,
6,
8,
4,
16,
12,
8,
4,
48,
2,
4,
4,
14,
4,
16,
4,
6,
8,
8,
4,
32,
4,
8,
18,
12,
2,
8,
2,
30,
8,
8,
4,
18,
8,
8,
4,
16,
2,
32,
4,
6,
8,
8,
8,
24,
2,
8,
8,
18,
4,
36,
4,
8,
8,
8,
4,
12,
8,
8,
12,
10,
4,
8,
8,
12,
8,
8,
2,
48,
2,
4,
8,
24,
6,
8,
4,
20,
12,
16,
4,
12,
2,
8,
16,
8,
8,
12,
2,
12,
8,
4,
2,
40,
4,
8,
12,
6,
2,
32,
6,
16,
4,
4,
4,
18,
4,
16,
4,
24,
4,
8,
4,
6,
24,
8,
2,
32,
2,
8,
4,
12,
4,
16,
12,
20,
4,
4,
8,
24,
2,
8,
6,
8,
8,
16,
2,
6,
8,
16,
2,
42,
4,
8,
8,
12,
4,
16,
4,
36,
15,
12,
2,
24,
8,
4,
8,
10,
4,
24,
2,
12,
4,
8,
8,
16,
2,
4,
6,
12,
8,
8,
8,
12,
12,
8,
4,
48,
2,
8,
8,
8,
2,
16,
8,
6,
6,
4,
2,
40,
4,
16,
8,
12,
8,
12,
4,
8,
12,
12,
2,
12,
4,
8,
16,
32,
2,
16,
2,
24,
8,
4,
4,
24,
4,
4,
16,
6,
4,
32,
2,
10,
6,
4,
8,
12,
8,
8,
8,
32,
4,
20,
2,
12,
8,
4,
2,
24,
8,
16,
12,
6,
4,
16,
4,
8,
4,
12,
4,
54,
2,
4,
4,
10,
8,
16,
2,
6,
8,
8,
8,
32,
4,
4,
8,
12,
4,
24,
8,
28,
4,
12,
2,
12,
6,
8,
6,
16,
2,
16,
2,
12,
16,
4,
4,
40,
4,
4,
4,
24,
2,
8,
4,
16,
24,
4,
8,
12,
2,
12,
8,
12,
4,
24,
8,
12,
4,
8,
4,
32,
4,
8,
12,
12,
4,
16,
2,
20,
4,
8,
6,
18,
2,
4,
24,
16,
4,
8,
4,
12,
6,
16,
4,
36,
4,
4,
4,
12,
4,
32,
4,
8,
4,
8,
4,
36,
4,
4,
12,
25,
};

int getFactors(int v)
{
/*	if (factors[v] == 0)
	{
		int cnt = 2;
		int t = (int)sqrt((float)v) - 1;
		for (int i = 2; i <= t; ++i)
			if (v % i == 0)
				cnt += 2;
		if (v % (t + 1) == 0)
		{
			if ((t + 1) * (t + 1) == v)
				++cnt;
			else
				cnt += 2;
		}
		factors[v] = cnt;
	}*/
	return factors[v];
}

struct Node
{
	int val;
	int fa;
};

bool comp(const Node& a, const Node& b)
{
	return a.fa < b.fa;
}

void solve(int num, int a, int b, int k)
{
	vector<Node> vec;
	vec.reserve(b - a + 1);
	for (int i = a; i <= b; ++i)
	{
		Node n;
		n.val = i;
		n.fa = getFactors(i);
		vec.push_back(n);
	}
	sort(vec.begin(), vec.end(), comp);
	
	vector<int> ret;
	vector<Node>::reverse_iterator iter = vec.rbegin() + k;
	if (iter < vec.rend())
	{
		if (iter->fa != (iter - 1)->fa)
		{
			int ref = iter->fa;
			while (iter < vec.rend() && iter->fa == ref)
			{
				ret.push_back(iter->val);
				++iter;
			}
		} 
	}
	
	cout << "Case " << num << ": ";
	if (ret.empty())
		cout << "None" << endl;
	else
	{
		sort(ret.begin(), ret.end());
		copy(ret.begin(), ret.end(), ostream_iterator<int>(cout, " "));
		cout << endl;
	}
}

int main()
{
	int cnt;
	cin >> cnt;
	int c = 0;
	while (cnt--)
	{
		int a, b, k;
		cin >> a >> b >> k;
		solve(++c, a, b, k);
	}
}
