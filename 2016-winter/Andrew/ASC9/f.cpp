#include <cstdio>
#include <cstring>
#include <algorithm>
#include <list>
#include <vector>

using namespace std;

const int maxn = 405;

vector< pair<int,int> > e[maxn];
int d[maxn],s,n,m,x,y,t,D[maxn][maxn];
list<int> v;

void add(int a,int b,int c)
{
	if (c <= 0) throw 1;
	s += c;
	e[a].push_back(make_pair(b,c));
	e[b].push_back(make_pair(a,c));
}

void dfs(int x,int y)
{
	d[x] = y;
	for (unsigned i = 0;i < e[x].size();i ++)
		if (d[e[x][i].first] == -1)
			dfs(e[x][i].first,y+e[x][i].second);
}

bool ok(int n,int m)
{
	for (int i = 0;i < n;i ++)
	{
		if ((int)e[i].size() > 1) return 0;
		fill(d,d+m,-1);
		dfs(i,0);
		for (int j = 0;j < n;j ++) if (D[i][j] != d[j]) return 0;
	}
	return 1;
}

int main()
{
	while (scanf("%d",&n) != EOF)
	{
		v.clear();
		m = n;
		for (int i = 0;i < n;i ++)
		{
			e[i].clear();
			v.push_back(i);
			for (int j = 0;j < n;j ++) scanf("%d",&D[i][j]);
		}
		bool flag = 0;
		s = 0;
		while (v.size() > 2)
		{
			x = v.front();
			t = D[v.front()][v.back()];
			for (list<int>::iterator i = v.begin();i != v.end();++ i)
			{
				list<int>::iterator _j = ++ i; -- i;
				for (list<int>::iterator j = _j;j != v.end();++ j)
					if (t < D[*i][*j])
					{
						t = D[*i][*j];
						x = *i;
					}
			}
			t = 0x7fffffff;
			for (list<int>::iterator i = v.begin();i != v.end();++ i)
			{
				list<int>::iterator _j = ++ i; -- i;
				for (list<int>::iterator j = _j;j != v.end();++ j)
					if (*i != x && *j != x && t > D[*i][x] + D[*j][x] - D[*i][*j])
						t = D[*i][x] + D[*j][x] - D[*i][*j];
			}
			if (t % 2 != 0) flag = 1; else t /= 2;
			if (flag) break;
			y = m;
			for (list<int>::iterator i = v.begin();i != v.end();++i)
			{
				D[*i][m] = D[m][*i] = D[*i][x] - t;
				if (D[*i][m] == 0)
				{
					y = *i;
					break;
				}
			}
			if (y == m)
			{
				e[m].clear();
				v.push_back(m++);
			}
			add(x,y,t);
			v.erase(find(v.begin(),v.end(),x));
		}
		if (v.size() > 1) add(v.front(),v.back(),D[v.front()][v.back()]);
		if (!ok(n,m)) flag = 1;
		if (flag)
		{
			printf("-1\n\n");
			continue;
		}
		printf("%d\n",s+1);
		n = m;
		for (int i = 0;i < m;i ++)
			for (vector<pair<int,int> >::iterator j = e[i].begin();j != e[i].end();++j)
				if (i < j->first)
				{
					for (int k = 0;k < j->second;++ k)
						printf("%d %d\n",k==0?i+1:n+k,k==j->second-1?j->first+1:n+k+1);
					n += j->second - 1;
				}
		printf("\n");
	}
	return 0;
}
