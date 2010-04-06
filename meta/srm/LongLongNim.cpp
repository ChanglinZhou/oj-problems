#include <vector>
#include <map>
using namespace std;

class LongLongNim {
public:
    int numberOfWins( int maxN, vector<int> moves )
    {
        int mask = ( 1 << 22 ) - 1;
        int res = -1;
        map<int, int> last;
        vector<int> r;
        for ( int i = 0; i <= maxN; ++i )
        {
            mask  <<= 1;
            ++res;
            vector<int>::iterator it = moves.begin();
            while ( it != moves.end() )
            {
                // Move to losing position for second player
                if ( (mask & (1 << *it)) == 0 )
                {
                    ++mask;
                    --res;
                    break;
                }
                ++it;
            }
            // circle
            if( last.find(mask) != last.end() )
            {
                int pLength = i - last[mask];
                int cnt = (maxN - i) / pLength;
                //i += cnt * pLength;
                maxN -= cnt*pLength;
                res += cnt * ( res - r[last[mask]] );
            }
            last[mask] = i;
            r.push_back(res);
        }
        return res;
    }
};