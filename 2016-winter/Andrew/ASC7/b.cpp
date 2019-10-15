#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#define fo(i,a,b) for (int i = a;i <= b;i ++)
#define abs(x) ((x)>0?(x):(-(x)))

using namespace std;

const int dx[] = {0,-1,1,0,0,-1,-1,1,1};
const int dy[] = {0,0,0,-1,1,-1,1,-1,1};
int n;
set< pair<int,int> > Q,S;

int main()
{
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
	scanf("%d",&n);
	while (n != 0)
	{
		Q.clear(); S.clear();
		fo(i,1,n)
		{
			int x,y,c;
			scanf("%d%d%d",&x,&y,&c);
			c += 2;
			fo(dx,-c+1,c-1)
				fo(dy,-c+1,c-1)
					if (abs(dx) + abs(dy) <= c)
						S.insert(make_pair(x+dx,y+dy));
		}
		for (set< pair<int,int> >::iterator it = S.begin();it != S.end();it ++)
		{
			int x = it->first, y = it->second;
			fo(k,1,8)
			{
				pair<int,int> P = make_pair(x+dx[k],y+dy[k]);
				if (S.find(P) == S.end()) Q.insert(P);
			}
		}
		while (!Q.empty())
		{
			pair<int,int> P = *Q.begin(); Q.erase(P);
			bool check = 1;
			fo(x,P.first-1,P.first)
				fo(y,P.second-1,P.second)
				{
					bool cur = 0;
					fo(dx,0,1)
						fo(dy,0,1)
							cur |= S.count(make_pair(x+dx,y+dy)) > 0;
					if (!(check &= cur)) break;
				}
			if (check)
			{
				S.insert(P);
				int x = P.first, y = P.second;
				fo(k,1,8)
				{
					pair<int,int> p = make_pair(x+dx[k],y+dy[k]);
					if (S.find(p) == S.end()) Q.insert(p);
				}
			}
		}
		printf("%lu\n",S.size());
		scanf("%d",&n);
	}
	return 0;
}
