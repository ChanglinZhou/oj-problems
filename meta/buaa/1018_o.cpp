#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 100
#define T 10

#define TRUE 1
#define FALSE 0

typedef unsigned char BOOL;

BOOL b[T * (T-1)];
int x[M + 1];
int a[M + 1][T];


int compare (const void * a, const void * b)
{
	return ( *(int*)a - *(int*)b );
}


void init( int m, int s, int t )
{
	if ( s <= 0 || t <= 0 || s > t )
		return;

	int i, j;

	memset( b, 0, sizeof(b) );
	b[0] = TRUE;
	for ( i = 1; i < T * (T-1); ++i )
		for ( j = s; j <= t; ++j )
			if( (i - j) >= 0 )
				b[i] = b[i] || b[i-j];

	for ( i = 0; i <= m; ++i )
		for ( j = 0; j < t; ++j )
			a[i][j] = m + 1;

	x[0] = 0;
	a[0][0] = 0;
}


BOOL can( int v, int s, int t )
{
	if ( v < 0 || s <= 0 || t <= 0 || s > t )
		return FALSE;

	if ( v >= s*(s-1) )
		return TRUE;

	return b[v];
}

int getMinRocks( int m, int s, int t )
{
	if ( s <= 0 || t <= 0 || s > t )
		return 0;

	int best, i, j, k;

	if ( s == t )
	{
		best = 0;
		for ( i = 1; i <= m; ++i )
			if ( x[i] % s == 0 )
				++best;

		return best;
	}

	init(m, s, t);
	for ( i = 1; i <= m; ++i ) {
		for ( j = 0; j < t; ++j ) {
			if ( (x[i] - j) <= x[i-1] ) {
				a[i][j] = a[i-1][j-x[i]+x[i-1]];
			}
			else {
				for ( k = 0; k < t; ++k ) {
					if ( can( x[i]-j-x[i-1]+k, s, t ) && (a[i-1][k] < a[i][j]) )
						a[i][j] = a[i-1][k];
				}

				if ( j == 0 )
					a[i][j] += 1;
			}
		}
	}

	best = m + 1;

	for ( i = 0; i < t; ++i ) {
		if ( a[m][i] < best )
			best = a[m][i];
	}

	return best;
}


int main()
{
	int i, pos;
	int l, s, t, m;

	while ( scanf( "%d", &l ) != EOF ) {
		if ( l == 0 )
			break;

		scanf( "%d %d %d", &s, &t, &m );

		for ( i = 1; i <= m; ++i ) {
			scanf( "%d", &pos );
			x[i] = pos;
		}

		qsort( x, m + 1, sizeof(int), compare );

		printf( "%d\n",  getMinRocks(m, s, t) );
	}

	return 0;
}

