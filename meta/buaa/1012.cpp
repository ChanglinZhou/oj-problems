#include <stdio.h>
#include <string.h>

#define MAX 10000

#define N 10000

int x[MAX/4 + 1], y[MAX/4 + 1];
int result[MAX/2 + 1];

int multiply( int lenX, int lenY )
{
    int lenR = lenX + lenY;

    for ( int i = 0; i < lenY; ++i )
    {
        int c = 0;
        for ( int j = 0; j < lenX; ++j )
        {
            int product = x[lenX - j] * y[lenY - i] + c;
            result[lenR - i - j] += product;
            c = result[lenR - i - j] / N;
            result[lenR - i - j] %= N;
        }

        result[lenR - i - lenX] = c;
    }

    return lenR;
}


void print( int* data, int len )
{
    int i = 0;
    while ( !data[i] )
        ++i;

    if ( i <= len )
        printf( "%d", data[i++] );

    while ( i <= len )
        printf( "%.4d", data[i++] );

    printf("\n");
}

void init( )
{
    memset( x, 0, sizeof(x) );
    memset( y, 0, sizeof(y) );
    memset( result, 0, sizeof(result) );
}

void StringToInt( char* line, int* buffer )
{
    int total = strlen(line);
    int head = total % 4;

    int start = 1;
    for ( int i = 0; i < head; ++i )
    {
        buffer[start] *= 10;
        buffer[start] += (line[i] - '0');
    }

    start += (head > 0);
    for ( int j = head; j < total; ++start )
    {
        for ( int k = 0; k < 4; ++k, ++j )
        {        
            buffer[start] *= 10;
            buffer[start] += (line[j] - '0');
        }
        
    }
}



//procedure Divide(a,b:hp;var c,d:hp); { c:=a div b ; d:=a mod b }
//  var i,j,len:integer;
//  begin
//    fillchar(c,sizeof(c),0);
//    len:=a.len;
//    fillchar(d,sizeof(d),0);
//    d.len:=1;
//    for i:=len downto 1 do
//    begin
//      Multiply10(d);
//      d.s[1]:=a.s[i]; { d:=d*10+a.s[i] }
//      { c.s[i]:=d div b ; d:=d mod b; }
//      { while(d>=b) do begin d:=d-b;inc(c.s[i]) end }
//      while(compare(d,b)>=0) do
//      begin
//        Subtract(d,b,d);
//        inc(c.s[i]);
//      end;
//    end;
//    while(len>1)and(c.s[len]=0) do dec(len);
//    c.len:=len;
//  end;



int main()
{
    char line[MAX + 1];
    init();

    scanf( "%s", line );
    int lenX = strlen(line);
    lenX = (lenX >> 2) + static_cast<bool>(lenX & 0x00000003);
    StringToInt( line, x );

    scanf( "%s", line );
    int lenY = strlen(line);
    lenY = (lenY >> 2) + static_cast<bool>(lenY & 0x00000003);
    StringToInt( line, y );

    int lenR = multiply( lenX, lenY );

    print( result,  lenR );

    return 0;
}

