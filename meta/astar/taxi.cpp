#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
using namespace std;

typedef enum _PointType {
    End, Intersection, Nearest
} PointType;

struct Point2d {
    double x;
    double y;
    PointType type;
};

struct Segment2d {
    Point2d startPt;
    Point2d endPt;
};

const int MAX = 1500;

int graph[MAX][MAX];
vector<int> nearests;


void read_data( vector<Segment2d>& segments, Point2d& start, Point2d& end )
{
    int k;
    scanf( "%d", &k );
    
    for ( int i = 0; i < k; ++i )
    {
        Segment2d segment;
        scanf( "%lf %lf %lf %lf", &segment.startPt.x, &segment.startPt.y, &segment.endPt.x, &segment.endPt.y );
        segments.push_back( segment );
    }

    scanf( "%lf %lf %lf %lf", &start.x, &start.y, &end.x, &end.y );
    start.type = end.type = End;
}



void generate_graph( const vector<Segment2d>& segments, const Point2d& start, const Point2d& end )
{
    memset(graph, -1, sizeof(graph));
}


double shortest_path( int source, int destination )
{
    double path = 0.0;

    return path;
}

double best_path( int source )
{
    vector<int>::iterator it = nearests.begin();

    if ( it == nearests.end() )
        throw exception("Error!");

    double minPath = shortest_path( source, *it++ );
    double tmp;

    while ( it != nearests.end() ) 
    {
        tmp = shortest_path( source, *it++ );
        if ( tmp < minPath )
            minPath = tmp;
    }

    return minPath;
}

int main()
{
    vector<Segment2d> segments;
    Point2d start, end;
    
    read_data( segments, start, end );
    generate_graph( segments, start, end );

    printf("%.1lf", best_path(0));
    return 0;
}